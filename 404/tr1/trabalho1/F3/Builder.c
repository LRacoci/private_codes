#include "Builder.h"

/* Define um tipo generico para o argumento de uma diretiva */
typedef union DirArg {
    char s[128];
    short int sd;
    long long int lld;
    unsigned long long int llu;
} DirArg;
/* Declaração de um vetor contendo as principais
 * definições de cada instrução */
static struct m{
    char id[10];
    unsigned short int opcode;
    __extension__ bool n_arg:1;
    __extension__ bool option:1;
}
mne[MAX_INSTR] =
{
    {     "LD" , 0x01 , true  , false },
    {     "LD-", 0x02 , true  , false },
    {     "LD|", 0x03 , true  , false },
    {    "LDmq", 0x0A , false , false },
    { "LDmq_mx", 0x09 , true  , false },
    {      "ST", 0x21 , true  , false },
    {     "JMP", 0x0D , true  , true  },
    {   "JUMP+", 0x0F , true  , true  },
    {     "ADD", 0x05 , true  , false },
    {    "ADD|", 0x07 , true  , false },
    {     "SUB", 0x06 , true  , false },
    {    "SUB|", 0x08 , true  , false },
    {     "MUL", 0x0B , true  , false },
    {     "DIV", 0x0C , true  , false },
    {     "LSH", 0x14 , false , false },
    {     "RSH", 0x15 , false , false },
    {  "STaddr", 0x12 , true  , true  }
};

/* Declaração de um vetor contendo as principais
 * definições de cada diretiva */
static struct d{
    TypeDir dirType;
    char id[10];
    __extension__ unsigned short int n_arg:2;
    struct Arg{
        TypeArg type[4];
        long long int lowest;
        long long int highest;
    }arg[2];
}
dir[MAX_DIR] =
{
    {   SET ,  "set", 2, {
        {{SYM}                                         },
        {{HEX, DEC}         , 0           , 2147483647 }
    }},
    {   ORG ,  "org", 1, {
        {{HEX, DEC}          , 0           , 0x3FF     }
    }},
    { ALIGN ,"align", 1, {
        {{DEC}              , 0           , 0x3FF      }
    }},
    { WFILL ,"wfill", 2, {
        {{     DEC          }, 1          , 0x3FF      },
        {{HEX, DEC, ROT, SYM}, -2147483648, 2147483647 }
    }},
    {  WORD , "word", 1, {
        {{HEX, DEC, ROT, SYM}, 0          , 2147483647 }
    }}
};
/* Confere se não há coisas inválidas depois de uma
 * instrução ou diretiva, a ideia eh soh verificar,
 * sem mudar o arquivo de entrada */
bool end_line(FILE * src, String expr, unsigned int line){
    bool ok;
    fpos_t pos;
    String aux = NULL;
    unsigned int el = 0;
    /* Salva a posição antes de fazer qualquer coisa */
    fgetpos(src, &pos);
    /* Tenta pegar a proxima palavra */
    aux = fgetword(src, &el ,&ok);
    /* Verifica se há quebras de linha, se não houver é
     * porque há alguma coisa extra que não deveria estar lá */
    if(el == 0){
        /* Printa o erro indicando que há argumentos extras */
        stderror(
            line,
            "Extra argument \"%s\" for %s\n",
            aux,
            expr
        );
        /* Indica que houve um erro */
        ok = false;
    }
    /* Libera a string auxiliar se existir */
    if(aux){
        free(aux);
    }
    /* Retorna o arquivo a posição de leitura anterior */
    fsetpos(src, &pos);
    /* Retorna falso se el == 0, ou seja se alguma
     * palavra foi pega na mesma linha */
    return el != 0;
}
/* Valida o formato de um argumento genérico */
bool validate_arg_format(
    String str,
    TypeArg * t,
    bool * instr,
    unsigned int line,
    HashT dict,
    bool maybe_sym,
    bool second_time
){
    unsigned short int i;
    char th;
    unsigned int len;
    String aux;
    bool ok = true;

    /* Copia o argumento original pra uma string auxiliar, pq modificações são feitas */
    aux = copy_word(str, &len);
    /* inicializa o tipo do argumento a ser retornado como nulo*/
    if(t) *t = 0;
    /* Se o argument estiver entre aspas ...*/
    if(aux[0] == '"' && aux[strlen(aux) -1] == '"'){
        /* Nesse caso deve ser um argumento de instrução */
        if(instr) *instr = true;
        /*sscanf(aux, "\"%[^\"]\"", aux);*/
        /* Extrai o que esta entre aspas */
        filter_Word(aux, "\"%s\"");
        /* Verifica se há um ':' no final do argumento */
        if(aux[strlen(aux) -1] == ':'){
            stderror(line, "Arguments of instructions do not have ':' in the end\n");
            ok = false;
            /* Retorna que não é o argumento de uma instrução */
            if(instr) *instr = false;
        }
    /* Se não estiver entre aspas não deve ser argumento de uma instrução */
    }else{
        if(instr) *instr = false;

    }
    /* Verifica se não parece um argumento hexadecimal */
    if(aux[0] == '0' && aux[1] == 'x'){
        *t = HEX;
        /* Verifica se não há nenhum caracter invalido */
        for(i = 2; aux[i] && ok; i++){
            if(!hexadecimal(aux[i])){
                stderror(line, "%c is not a valid hexadecimal character\n", aux[i]);
                ok = false;
            }
        }
        /* Se não há exatamente 10 digitos hexadecimais + o prefixo 0x, erro */
        if(i != 12){
            stderror(line, "%s have not ten characters \n", aux);
            ok = false;
        }
    /* Verifica se não parece um argumento decimal*/
    }else if(between('0', aux[0], '9') || aux[0] == '-'){
        *t = DEC;
        for(i = 1; aux[i] && ok; i++){
            if(!decimal(aux[i])){
                stderror(line,"%c is not a valid decimal character\n",  aux[i]);
                ok = false;
            }
        }
    /* Verifica se não está na hash table */
    }else if(is_in_HashT(dict, aux, &th)){
        /* Classifica o que esta na hash table de acordo com como foi enviado para esta */
        switch (th) {
            case 'S':
                if(t) *t = SYM;
                break;
            case 'L':
                if(t) *t = ROT;
                break;
            default:
                /* Se não for nenhum dos caracteres válidos seta o tipo do argumento para 0(inválido) */
                if(t) *t = 0;
                ok =  false;
                break;
        }
    /* Se o argumento em questão parece um Rotulo */
    }else if(aux[strlen(aux) -1] == ':'){
        /* Caso o tipo seja invalido, passa a ser um rotulo*/
        if( t && *t == 0){
            *t = ROT;
        /* Caso contrário o argumento é desconhecido */
        }else{
            stderror(
                line,
                "%s cannot be %s and ROT\n",
                aux,
                (*t == HEX) ? "HEX" :
                (*t == DEC) ? "DEC" : "WTF"
            );
        }
    }else{
        /* Esta flag é passada da função de interpretação de
         * diretivas se a diretiva em questão for um set */
        if(maybe_sym){
            *t = SYM;
        /* Caso contrario e estiver na segunda montagem
         * (quando os rotulos já estarao na hash-table) */
        }else if(second_time){
            stderror(
                line,
                "Unknown argument: %s\n",
                aux
            );
            ok = false;
        /* Se não estiver na segunda montagem e não for um
         * simbolo nem hex nem dec entao pode-se considerar um rotulo*/
        }else{
            *t = ROT;
        }
    }
    free(aux);
    return ok;
}
/* Se é uma instrução válida */
bool is_instr(String str, TypeInstr *t){
    unsigned short int i;
    bool resp = true;
    for(i = 0; i < MAX_INSTR && strcmp(str, mne[i].id); i++);
    if(i == MAX_INSTR){
        resp = false;
    }
    if(t){
        *t = i;
    }
    return resp;
}
/* Se é uma diretiva válida */
bool is_dir(String str, TypeDir * t){
    unsigned short int i;
    bool resp = true;
    /* Copia porque a string original eh modificada */
    String aux = copy_word(str, NULL);
    filter_Word(aux, ".%s");
    for(i = 0; i < MAX_DIR && strcmp(aux, dir[i].id); i++);
    if(i == MAX_DIR){
        resp = false;
    }
    if(t){
        *t = i;
    }
    free(aux);
    return resp;
}
/* Interpreta uma instrução e seu argumento (se houver) e verifica
 * se não há argumentos extras */
bool interpret_instr(
    FILE * src,
    TypeInstr t,
    unsigned int line,
    MemMap map,
    HashT dict,
    bool second_time
){
    bool ok = true, instr = true;
    unsigned int el;
    unsigned long long arg = 0;
    unsigned short int opcode;
    char c;
    String strarg;
    TypeArg ta;
    /*String aux;*/
    /* Se é possível identificar a instrução */
    if(!between(LD, t, STaddr)){
        stderror(
            line,
            "Could not identify the instruction\n"
        );
    }
    /* Salva o opcode generico, porque este valor será modificado
     * caso seja um mnemonico que tenha  a opção de ser a esquerda ou a direita */
    opcode = mne[t].opcode;
    /* Se a instrução precisa de argumento */
    if(mne[t].n_arg){
        el = 0;
        ok = true;
        /* Pega a proxima palavra da memoria */
        strarg = fgetword(src, &el ,&ok);
        if(el > 0 || !ok){
            stderror(
                line,
                "Could not get a necessary argument to %s instruction\n",
                mne[t].id
            );
            return false;
        }
        /* Valida o argumento */
        ok = validate_arg_format(strarg, &ta, &instr, line, dict, false, second_time);
        /* Se não estiver formatado como argumento de uma instrução */
        if(!instr){
            stderror(
                line,
                "[%s] is not formated as the argument of a instruction\n",
                strarg
            );
            return false;
        }
        /* Se estiver formatado entre aspas, extrai-se o que está entre aspas */
        filter_Word(strarg, "\"%s\"");
        /* Se a validação retorna que o tipo de argumento é decimal */
        if(ta == DEC){
            /* Passa-se o argumento para valor numerico */
            sscanf(strarg, "%llu", &arg);
            /* Compara pra ver se o numero esta nos limites de 12 bits */
            if(!between(0, arg, 0xFFF)){
                stderror(line, "Argument %lld out of bounds\n", arg);
                ok = false;
            }
        /* Simetrico ao caso decimal */
        }else if(ta == HEX){
            sscanf(strarg, "0x%llX", &arg);
            if(!between(0, arg, 0xFFF)){
                stderror(line, "Argument 0x%03llX out of bounds\n", arg);
                ok = false;
            }
        /* Se o argumento foi classificado como ROTULO ou SYMBOL */
        }else if(ta == ROT || ta == SYM){
            /* Tenta recuperar da hash-table usando como key o strarg */
            if(get_HashT(dict, strarg, &arg, &c)){
                /* Se o tipo recuperado da hash-table não for nem Label nem Symbol*/
                if(!char_in_string(c, "LS")){
                    stderror(
                        line,
                        "Invalid instruction argument: %s\n",
                        strarg
                    );
                }
                /* Incrementa a posição de montagem se houver opção na
                 * instrução de poder ser a esquerda ou a direita */
                opcode += ((arg % 2) && mne[t].option) ? 1 : 0;
                arg /= 2;
            }else{
                /* Se estiver na segunda passagem e o argumento não puder ser interpretado, erro */
                if(second_time){
                    stderror(
                        line,
                        "Invalid instruction argument: %s\n",
                        strarg
                    );
                }
            }
        }

        free(strarg);
    }
    /* Verificar se não há argumentos extras */
    ok = ok ? end_line(src, mne[t].id, line) : false;
    /* Se nenhum erro foi dado, tenta inserir a instrução no mapa de memoria */
    ok = ok ? insert_instr_MemMap(map, opcode, arg, line) : false;
    return ok;
}
/* Valida um simbolo de acordo com as especificações do enunciado */
bool validate_symbol(String str, unsigned int line, HashT ht){
    bool ok = true;
    char c = ' ';
    unsigned int i, len = strlen(str);
    /* Verifica se o argumento não é uma instrução, que seria uma palavra reservada */
    if(is_instr(str, NULL)){
        stderror(line, "Menemonics cannot be used as Symbols for .set\n");
        ok = false;
    }
    /* Verifica se o argumento não é uma diretiva, que seria uma palavra reservada */
    if(ok && is_dir(str, NULL)){
        stderror(line, "Directives cannot be used as Symbols for .set\n");
        ok = false;
    }
    /* Verifica se no primeiro caracter não há um numero */
    if(ok && decimal(str[0])){
        stderror(line, "Symbols shoudn't start with a number\n");
        ok = false;
    }
    /* Verifica se todos os caracteres são válidos (alphanumericos ou '_') */
    for(i = 0;ok && i < len-1; i++){
        if(!(alphanumeric(str[i]) || str[i] == '_')){
            stderror(line, "'%c' is not a valid Label character\n", str[i]);
            ok = false;
        }
    }
    /* Se esta palavra já esta na hash-table, mas como simbolo */
    if(ok && is_in_HashT(ht, str, &c) && c != 'S'){
        stderror(line, "\"%s\" already declared as a Symbol\n", str);
        ok = false;

    }
    return ok;
}
/* Valida um rotulo com base nas especificações do enunciado */
bool validate_label(String str, unsigned int line, HashT ht){
    bool ok = true;
    char c = ' ';
    unsigned int i, len = strlen(str);
    /* Verifica se no primeiro caracter não há um numero */
    if(decimal(str[0])){
        stderror(line, "Labels shoudn't start with a number\n");
        return false;
    }
    /* Verifica se todos os caracteres são válidos (alphanumericos ou '_') */
    for(i = 0; ok && i < len-1; i++){
        if(!(alphanumeric(str[i]) || str[i] == '_')){
            stderror(line, "'%c' is not a valid Label character\n", str[i]);
            ok =  false;
        }
    }
    /* Se esta palavra já esta na hash-table, mas como rótulo */
    if(ok && is_in_HashT(ht, str, &c) && c != 'L'){
        stderror(line, "\"%s\" already declared as a Label\n", str);
        ok = false;
    }
    return ok;
}
/* Validate a directive */
bool validate_dir(String str, TypeDir * t, unsigned int line){
    if(!is_dir(str, t)){
        stderror(line, "[%s] is not a valid directive\n", str);
        return false;
    }
    return true;
}
/* Trata a diretiva dados seus argumentos no vetor arg[] e seu tipo em t*/
bool chose_dir(
    TypeDir t,
    DirArg arg[],
    unsigned int line,
    HashT ht,
    MemMap m,
    bool second_time
){
    /* Inicializa com nenhum erro */
    bool ok = true;
    unsigned int i;
    /* Analisa cada caso de t */
    switch(t){
        /* Para o caso de ser set.. */
        case SET:
            ok = validate_symbol(arg[0].s, line, ht);
            if(ok && second_time){
                if(is_in_HashT(ht, arg[0].s, NULL)){
                    stderror(line, "\"%s\" already declared\n", arg[0].s);
                }
                put_HashT(ht, arg[0].s, arg[1].llu, 'S');
            }
            break;
        /* Para o caso de ser org.. */
        case ORG:
            /* Seta a posição do Memort Map*/
            m->pos = arg[0].llu*2;
            break;
        /* Para o caso de ser align.. */
        case ALIGN:
            /* Ajusta a posição do Memory Map se já não estiver certo*/
            if(m->pos%2){
                m->pos++;
            }
            while((m->pos/2) % arg[0].lld){
                m->pos+=2;
            }
            break;
        /* Para o caso de ser word.. */
        case WORD:
            /* Se for a primeira montagem não importa o que vai
             * estar no mapa de memória */
            if(!second_time){
                arg[0].llu = 0;
            }
            /* Se a posção estiver a direita */
            if(m->pos % 2 == 1){
                stderror(line, "Trying to put a word in the right\n");
                ok = false;
            /* Se a palavra não puder ser colocada no mapa de memoria */
            }else if(m->pos/2 + 1 > IAS_MAX_LINE_NUMBER){
                stderror(line, "Trying to insert a word out of memory\n");
                ok = false;
            }
            /* Se não ocorreu nnhum erro a palavra é inserida no mapa de memoria */
            ok = ok ? insert_word_MemMap(m, arg[0].llu, line) : false;
            break;
        /* Para o caso de ser wfill.. */
        case WFILL:
            /* Simetrico ao word */
            if(!second_time){
                arg[1].llu = 0;
            }
            /* Simetrico ao word */
            if(m->pos % 2 == 1){
                stderror(line, "Trying to wfill from the right");
                ok = false;
            /* Simetrico ao word */
            }if(m->pos/2 + arg[0].llu > IAS_MAX_LINE_NUMBER){
                stderror(line, "Wfill need unavailable memory\n");
                ok = false;
            }
            /* Adiciona-se uma palavra em cada posição de memoria */
            for(i = 0; i < arg[0].llu; i++){
                ok = ok ? insert_word_MemMap(m, arg[1].lld, line) : false;
            }
            break;

        case NONE:
            return false;
            break;
    }
    return ok;
}
/* Interpreta uma diretiva e seus argumento e verifica
 * se não há argumentos extras */
bool interpret_dir(
    FILE * src,
    TypeDir t,
    unsigned int line,
    MemMap map,
    HashT dict,
    bool second_time
){
    unsigned short int i, j;
    bool ok = true, instr = true, arg_flag;
    unsigned int el;
    DirArg arg[2];
    char c;
    String strarg;
    TypeArg ta = NONE;
    /* Verifica se o tipo de diretiva passado como parâmetro é válido */
    if(!between(SET ,t, WORD)){
        stderror(
            line,
            "Could not identify the directive\n"
        );
    }
    /* Percorre os argumentos da diretiva */
    for(i = 0, el = 0, ok = true; i < dir[t].n_arg && ok; i++){
        /* Tenta pegar a próxima palavra na memória, supostamente um argumento */
        strarg = fgetword(src, &el ,&ok);
        /* Se não foi possível pegar, printa um erro */
        if(el > 0 || !ok){
            stderror(
                line,
                "Could not get a necessary argument to %s directive\n",
                dir[t].id
            );
            ok = false;
        }
        /* Tenta validar o argumento */
        ok = ok ? validate_arg_format(
            strarg,
            &ta,
            &instr,
            line,
            dict,
            t == SET && i == 0,
            second_time
        ) : false;
        /* Se a validação retornou válido, mas o argumento esta
         * formatado como o de uma instrução, isto é, entre aspas,
         * isso também é um erro */
        if(ok && instr){
            stderror(
                line,
                "It is formated as the argument of a instruction, but %s is a directive\n",
                dir[t].id
            );
            return false;
        }

        arg_flag = false;
        /* Verifica o tipo do argumento ta está no vetor de
         * tipos possiveis pra diretiva de tipo t */
        /* arg_flag = ta in dir[t].arg[i].type*/
        for(j = 0; j < 4 && !arg_flag && ok; j++){
            if(ta == dir[t].arg[i].type[j]){
                arg_flag = true;
                /* Se o tipo do argumento foi identficado como decimal... */
                if(ta == DEC){
                    /* Transforma a string em numero */
                    sscanf(strarg, "%lld", &arg[i].lld);
                    /* Verifica se está nos limites corretos */
                    if(!between(
                        dir[t].arg[i].lowest,
                        arg[i].lld,
                        dir[t].arg[i].highest
                    )){
                        stderror(
                            line,
                            "Argument %lld out of bounds\n",
                            arg[i].lld
                        );
                        ok = false;
                    }
                /* Simetrico aos comentarios do decimal */
                }else if(ta == HEX){
                    sscanf(strarg, "0x%llX", &arg[i].llu);
                    if(!between(
                        dir[t].arg[i].lowest,
                        arg[i].lld,
                        dir[t].arg[i].highest
                    )){
                        stderror(
                            line,
                            "Argument 0x%010llX out of bounds\n",
                            arg[i].llu
                        );
                        ok = false;
                    }
                }else
                /* Se o tipo identificado foi Rotulo ou simbolo */
                if(ta == ROT || ta == SYM){
                    /* Se houver o ':' no final, da palavra, retira-se ele*/
                    if(ta == ROT && strarg[strlen(strarg) - 1] == ':'){
                        filter_Word(strarg, "%s:");
                    }
                    /* Se a palavra estier na hash-table ...*/
                    if(get_HashT(dict, strarg, &arg[i].llu, &c)){
                        /* ... e for um Rótulo, o argumento passa a
                         * ser uma posição e portanto eh dividido por 2 */
                        if(c == 'L'){
                            arg[i].llu /= 2;
                        /* ... e não for de um tipo conhecido, erro  */
                        }else if(!char_in_string(c, "LS")){
                            stderror(
                                line,
                                "Invalid argument: %s\n",
                                strarg
                            );
                        }
                    /* Se o tipo da diretiva eh set, trata-se o
                     * argumento como simbolo e copia-se a string
                     * para o argumento */
                    }else if(t == SET && i == 0){
                        strcpy(arg[i].s, strarg);
                    }else{
                        /* Como no caso das instruções, se nada foi
                         * identificado e já for a segunda passagem, erro*/
                        if(second_time){
                            stderror(
                                line,
                                "Unknown argument: %s\n",
                                strarg
                            );
                        }else{
                            /* Isso é para o caso de não haver ainda definido
                             * um rotulo que esta sendo usado como argumento,
                             * mas o programa estar na primeira montagem  */
                            arg[i].llu = 0;
                        }
                    }
                }
            }
        }
        /* Se nenhum erro ocorreu, mas o tipo do argumento
         * não bate com nenhum esperado */
        if(ok && !arg_flag){
            stderror(line, "%s is not a valid argument in this position\n", strarg);
            ok = false;
        }
        free(strarg);
    }
    /* Verificar se não há argumentos extras */
    ok = ok ? end_line(src, dir[t].id, line) : false;
    /* Trata cada diretiva individualmente */
    ok = ok ? chose_dir(t, arg, line, dict, map, second_time) : false;
    return ok;
}

/* Generaliza as montagens 1 e 2 com base na flag first */
bool pass(FILE * src, FILE * out, HashT dict, MemMap map, bool first){
    /* Retorno da função */
    bool ok = true;
    unsigned int
    m_pos = 0,  /* posição de montagem */
    line = 1,  /* linha de entrada */
    len, /* tamanho da string */
    wpl = 0, /*palavras por linha*/
    el = 0; /* Conta \n's */
    bool
    label = false, /* flag for determine if the word is a label */
    nef = true; /* indica se o arquivo de entrada ja chegou ao fim */
    String w;

    GenericType t;
    rewind(src);
    /* Loop principal do programa, itera sobre palavras do arquivo de entrada*/
    for(
        /* Inicializa as principais flags o ponteiro pra palavra a ser iterado */
        nef = true, el = 0, w = NULL;
        /* Verifica se tudo continua ok e se ainda não chegou no fim do arquivo */
        ok && nef;
        /* Pega a próima palavra se nenhum erro foi detectado e incrementa o numero
         * de linhas de acordo com o que foi devlvido de fgetword */
        w = ok? fgetword(src, &el, &nef) : NULL, line += el
    ){
        if(!w) {
            continue;
        }
        if(el != 0){
            wpl = 0;
            label = false;
        }
        /* Conta a palavra atual */
        wpl++;



        len = strlen(w);
        if(seems_directive(w)){
            ok = validate_dir(w, &t.d, line);
            ok = ok ? interpret_dir(src, t.i, line, map, dict, !first) : false;
        }else if(seems_label(w)){
            ok = validate_label(w, line, dict);
            if(ok && label == true){
                stderror(line, "Only one label is available per line\n");
                ok = false;
            }else if (ok){
                label = true;
            }
            if(first){
                filter_Word(w, "%s:");
                if(is_in_HashT(dict, w, NULL)){
                    stderror(line, "\"%s\" already declared\n", w);
                    ok = false;
                }
                if(ok){
                    put_HashT(dict, w, map->pos, 'L');
                }
            }
        /* Checa se é uma instrução */
        }else if(is_instr(w, &t.i)){
            /* interpreta a instrução */
            ok = interpret_instr(src, t.i, line, map, dict, !first);
            if (ok){
                m_pos++;
            }
        /* Ainda pode ser um falso mnemonico ou um falso rótulo */
        }else{
            /* De qualquer forma já não eh mais uma palavra válida */
            ok = false;
            /* Verifica se parece remotamente rótulo */
            if(char_in_string(':', w)){
                stderror(line, "%s is not a valid label\n", w);
            /* Se não for um rótulo inválido suponho que seja uma instrução inválida */
            }else{
                stderror(line, "%s is not a valid mnemonic\n", w);
            }
        }

        free(w);
        w = NULL;
    }
    return ok;

}

/* Função que realiza toda a montagem */
bool build(FILE * src, FILE * out) {
    /* Retorna para a main se deu tudo certo */
    bool ok = true;
    /* Cria um novo mapa de memória */
    MemMap map = new_MemMap();
    /* Cria uma nova hash table para guardar os rotulos e os simbolos do .set */
    HashT dict = new_HashT();
    /* Faz a primeira passagem, que se preocupa apenas em rotular as posições de memória */
    ok = pass(src, out, dict, map, true);

    /* Libera a tudo que foi alocado pra primeira montagem */
    free_MemMap(&map);
    /* Reinicializa o mapa de memória */
    map = new_MemMap();
    /* Realiza a segunda montagem, que faz tudo que a primeira nao faz*/
    ok = ok? pass(src, out, dict, map, false): ok;
    if(ok){
        fprint_MemMap(out, map);
    }
    /* Libera toda a memoria alocada dinamicamente pelas duas estruturas de dados */
    free_MemMap(&map);
    free_HashT(&dict);
    return ok;
}
