#include "Builder.h"


typedef union DirArg {
    char s[128];
    short int sd;
    long long int lld;
    unsigned long long int llu;
} DirArg;

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
        {{HEX, DEC}         , 0           , 0x7FFFFFFF }
    }},
    {   ORG ,  "org", 1, {
        {{HEX, DEC}          , 0           , 0x3FF     }
    }},
    { ALIGN ,"align", 1, {
        {{DEC}              , 0           , 0x3FF      }
    }},
    { WFILL ,"wfill", 2, {
        {{     DEC          }, 1          , 0x3FF      },
        {{HEX, DEC, ROT, SYM}, -4294967296, 0x7FFFFFFF }
    }},
    {  WORD , "word", 1, {
        {{HEX, DEC, ROT, SYM}, 0          , 0x7FFFFFFF }
    }}
};

bool end_line(FILE * src, String expr, unsigned int line){
    bool ok;
    fpos_t pos;
    String strarg = NULL;
    unsigned int el = 0;

    fgetpos(src, &pos);
    strarg = fgetword(src, &el ,&ok);
    /* Conseguiu pegar argumentos extras */
    if(el == 0){
        stderror(
            line,
            "Extra argument \"%s\" for %s\n",
            strarg,
            expr
        );
    }
    if(strarg){
        free(strarg);
    }
    fsetpos(src, &pos);
    return el > 0;
}
bool validate_arg_format(
    String str,
    TypeArg * t,
    bool  *instr,
    unsigned int line,
    HashT dict,
    bool maybe_sym,
    bool second_time
){
    unsigned short int i;
    char th;
    unsigned int j, len;
    String aux;
    bool ok = true;
    for(len = 0; str[len]; len++);
    len++;
    aux = malloc(len*sizeof(char));
    for(j = 0; j < len; j++){
        aux[j] = str[j];
    }
    *t = 0;

    if(aux[0] == '"' && aux[strlen(aux) -1] == '"'){
        *instr = true;
        /*sscanf(aux, "\"%[^\"]\"", aux);*/
        filter_Word(aux, "\"%s\"");

        if(aux[strlen(aux) -1] == ':'){
            stderror(line, "Arguments of instructions do not have ':' in the end\n");
            ok = false;
            *instr = false;
        }

    }else{
        *instr = false;

    }
    *t = 0;
    if(aux[0] == '0' && aux[1] == 'x'){
        *t = HEX;
        for(i = 2; aux[i] && ok; i++){
            if(!hexadecimal(aux[i])){
                stderror(line, "%c is not a valid hexadecimal character\n", aux[i]);
                ok = false;
            }
        }
    }else if(between('0', aux[0], '9') || aux[0] == '-'){
        *t = DEC;
        for(i = 1; aux[i] && ok; i++){
            if(!decimal(aux[i])){
                stderror(line,"%c is not a valid decimal character\n",  aux[i]);
                ok = false;
            }
        }
    }else if(is_in_HashT(dict, aux, &th)){
        switch (th) {
            case 'S':
                *t = SYM;
                break;
            case 'L':
                *t = ROT;
                break;
            default:
                *t = 0;
                ok =  false;
                break;
        }
    }else if(aux[strlen(aux) -1] == ':'){
        if(*t == 0){
            *t = ROT;
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
        if(maybe_sym){
            *t = SYM;
        }else if(second_time){
            stderror(
                line,
                "Invalid argument: %s\n",
                aux
            );
            ok = false;
        }else{
            *t = ROT;
        }
    }
    free(aux);
    return ok;
}

bool validate_instr(String str, TypeInstr *t, unsigned int line){
    unsigned short int i;
    for(i = 0; i < MAX_INSTR && strcmp(str, mne[i].id); i++);
    if(i == MAX_INSTR){
        return false;
    }
    *t = i;
    return true;
}

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
    /* Se a instrução precisa de argumento */
    if(!between(LD, t, STaddr)){
        stderror(
            line,
            "Could not identify the instruction\n"
        );
    }
    opcode = mne[t].opcode;
    if(mne[t].n_arg){
        el = 0;
        ok = true;
        strarg = fgetword(src, &el ,&ok);
                if(el > 0 || !ok){
            stderror(
                line,
                "Could not get a necessary argument to %s instruction\n",
                mne[t].id
            );
            return false;
        }
        ok = validate_arg_format(strarg, &ta, &instr, line, dict, false, second_time);
        if(!instr){
            stderror(
                line,
                "[%s] is not formated as the argument of a instruction\n",
                strarg
            );
            return false;
        }
        sscanf(strarg, "\"%[^\"]\"", strarg);
        if(ta == DEC){
            sscanf(strarg, "%llu", &arg);
            if(!between(0, arg, MAX_MEM_MAP)){
                stderror(line, "Argument %lld out of bounds\n", arg);
                ok = false;
            }
        }else if(ta == HEX){
            sscanf(strarg, "0x%llX", &arg);
            if(!between(0, arg, MAX_MEM_MAP)){
                stderror(line, "Argument 0x%03llX out of bounds\n", arg);
                ok = false;
            }
        }else if(ta == ROT || ta == SYM){
            if(get_HashT(dict, strarg, &arg, &c)){
                if(ta == SYM && c != 'S'){
                    stderror(
                        line,
                        "Argument %s shoud be a SYM but it is a %c\n",
                        strarg, c
                    );
                }else if(ta == ROT && c != 'L'){
                    stderror(
                        line,
                        "Argument %s shoud be a ROT but it is a %c\n",
                        strarg, c
                    );
                }else if(!char_in_string(c, "LS")){
                    stderror(
                        line,
                        "Invalid instruction argument: %s\n",
                        strarg
                    );
                }
            opcode += ((arg % 2) && mne[t].option) ? 1 : 0;
            arg /= 2;
            }else{
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

    ok = ok ? insert_instr_MemMap(map, opcode, arg, line) : false;
    return ok;
}

bool validate_label(String str, unsigned int line, HashT ht){
    bool resp = true;
    char c = ' ';
    unsigned int i, len = strlen(str);
    if(decimal(str[0])){
        stderror(line, "Erro, rotulo nao deve começar com número\n");
        return false;
    }
    for(i = 0; i < len-1; i++){
        if(!(alphanumeric(str[i]) || str[i] == '_')){
            stderror(line, " %c is not a valid Label character\n", str[i]);
        }
    }
    if(is_in_HashT(ht, str, &c) && c != 'L'){
        resp = false;
    }
    return resp;
}

bool validate_dir(String str, TypeDir * t, unsigned int line){
    unsigned short int i;
    sscanf(str, ".%s", str);
    for(i = 0; i < MAX_DIR && strcmp(str, dir[i].id); i++);
    if(i == MAX_DIR){
        stderror(line, "[.%s] is not a valid directive\n", str);
        return false;
    }
    *t = i;
    return true;
}
bool chose_dir(
    TypeDir t,
    DirArg arg[],
    unsigned int line,
    HashT ht,
    MemMap m,
    bool second_time
){
    bool ok = true;
    unsigned int i;
    switch(t){
        case SET:
            if(second_time){
                put_HashT(ht, arg[0].s, arg[1].llu, 'S');
            }
            break;

        case ORG:
            m->pos = arg[0].llu*2;
            break;

        case ALIGN:
            if(m->pos%2){
                m->pos++;
            }
            while((m->pos/2) % arg[0].lld){
                m->pos+=2;
            }


            break;

        case WORD:
            if(!second_time){
                arg[0].llu = 0;
            }
            if(m->pos % 2 == 1){
                stderror(line, "Trying to put a word in the right\n");
                ok = false;
            }else if(m->pos/2 + 1 >= IAS_MAX_LINE_NUMBER){
                stderror(line, "Wfill overflows the available memory\n");
                ok = false;
            }
            ok = ok ? insert_word_MemMap(m, arg[0].llu, line) : false;
            break;

        case WFILL:
            if(!second_time){
                arg[1].llu = 0;
            }
            if(m->pos % 2 == 1){
                stderror(line, "Trying to wfill from the right");
            }if(m->pos/2 + arg[0].llu >= IAS_MAX_LINE_NUMBER){
                stderror(line, "Wfill overflows the available memory\n");
            }
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
bool interpret_dir(
    FILE * src,
    TypeDir t,
    unsigned int line,
    MemMap map,
    HashT dict,
    bool second_time
){
    unsigned short int i, j;
    bool ok, instr = true, arg_flag;
    unsigned int el;
    DirArg arg[2];
    char c;
    String strarg;
    TypeArg ta = NONE;
    /*String aux;*/
    /* Se a instrução precisa de argumento */
    if(!between(SET ,t, WORD)){
        stderror(
            line,
            "Could not identify the directive\n"
        );
    }
    for(i = 0, el = 0, ok = true; i < dir[t].n_arg && ok; i++){
        strarg = fgetword(src, &el ,&ok);
        if(el > 0 || !ok){
            stderror(
                line,
                "Could not get a necessary argument to %s directive\n",
                dir[t].id
            );
            return false;
        }
        ok = validate_arg_format(
            strarg,
            &ta,
            &instr,
            line,
            dict,
            t == SET && i == 0,
            second_time
        );
        if(instr){
            stderror(
                line,
                "It is formated as the argument of a instruction, but %s is a directive\n",
                dir[t].id
            );
            return false;
        }
        arg_flag = false;
        /* arg_flag = ta in dir[t].arg[i].type*/
        for(j = 0; j < 4 && !arg_flag && ok; j++){
            if(ta == dir[t].arg[i].type[j]){
                arg_flag = true;
                if(ta == DEC){
                    sscanf(strarg, "%lld", &arg[i].lld);
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
                if(ta == ROT || ta == SYM){
                    if(ta == ROT && strarg[strlen(strarg) - 1] == ':'){
                        sscanf(strarg, "%[^:]:", strarg); /* Take ':' out */
                    }
                    if(get_HashT(dict, strarg, &arg[i].llu, &c)){
                        if(c == 'L'){
                            arg[i].llu /= 2;
                        }
                        if(ta == SYM && c != 'S'){
                            stderror(
                                line,
                                "Argument %s shoud be a SYM but it is a %c\n",
                                strarg, c
                            );
                        }else if(ta == ROT && c != 'L'){
                            stderror(
                                line,
                                "Argument %s shoud be a ROT but it is a %c\n",
                                strarg, c
                            );
                        }else if(c == 'L' && t == SET && i == 0){
                            stderror(
                                line,
                                "Redeclaration of %s\n",
                                strarg
                            );
                        }else if(!char_in_string(c, "LS")){
                            stderror(
                                line,
                                "Invalid argument: %s\n",
                                strarg
                            );
                        }
                    }else if(t == SET && i == 0){
                        strcpy(arg[i].s, strarg);
                    }else{
                        if(second_time){
                            stderror(
                                line,
                                "Invalid argument: %s\n",
                                strarg
                            );
                        }
                        arg[i].llu = 0;
                    }
                }
            }
        }
        free(strarg);
    }
    /* Verificar se não há argumentos extras */
    ok = ok ? end_line(src, dir[t].id, line) : false;
    ok = ok ? chose_dir(t, arg, line, dict, map, second_time) : false;
    return ok;
}



bool pass(FILE * src, FILE * out, HashT dict, MemMap map, bool first){
    /* Retorno da função */
    bool ok = true;
    unsigned int
    m_pos = 0,  /* posição de montagem */
    line = 1,  /* linha de entrada */
    len, /* tamanho da string */
    wpl = 1, /*palavras por linha*/
    el = 0; /* Conta \n's */
    bool instr,
    nef = true; /* indica se o arquivo de entrada ja chegou ao fim */
    String w;

    GenericType t;

    rewind(src);
    for(
        nef = true, el = 0, w = NULL;
        ok && nef;
        w = ok? fgetword(src, &el, &nef) : NULL, line += el
    ){
        if(!w) {
            continue;
        }
        wpl = (el == 0)? (wpl + 1) : 1;
        /* printf("pos: %03X%c; %d[%d]: %s\n",(map->pos)/2, ((map->pos)%2) ? 'd' : 'e', line, wpl, w); Debuging1 */

        len = strlen(w);
        if(seems_directive(w)){
            ok = validate_dir(w, &t.d, line);
            ok = ok ? interpret_dir(src, t.i, line, map, dict, !first) : false;
        }else if(seems_label(w)){
            ok = validate_label(w, line, dict);
            if(first){
                sscanf(w, "%[^:]:", w); /* Take ':' out */
                put_HashT(dict, w, map->pos, 'L');
                /*print_HashT(dict);  Debuging0 */
                /*printf("\n");  Debuging0 */
            }
        }else if(seems_argument(w)){
            ok = validate_arg_format(
                w,
                &t.a,
                &instr,
                line,
                dict,
                false,
                !first
            );
        /* Ainda pode ser argumento de diretiva ou instrução */
        }else{
            ok = validate_instr(w, &t.i, line);
            ok = ok ? interpret_instr(src, t.i, line, map, dict, !first) : false;
            if (ok){
                m_pos++;
            }
        }

        free(w);
        w = NULL;
    }
    return ok;

}


bool build(FILE * src, FILE * out) {
    bool ok = true;
    MemMap map = new_MemMap();
    HashT dict = new_HashT();
    /*cfprintf(stdout, 92,"Começando Primeira Montagem\n");  Debuging0 */
    ok = pass(src, out, dict, map, true);
    /*cfprintf(stdout, 92, "Terminada primeira montagem\n");  Debuging0 */
    /*print_HashT(dict);  Debuging0 */
    /*fprint_MemMap(stdout, map);  Debuging0 */
    /*printf("\n");  Debuging0 */

    free_MemMap(&map);
    map = new_MemMap();
    /*cfprintf(stdout, 92, "Começando Segunda Montagem\n");  Debuging0 */
    ok = ok? pass(src, out, dict, map, false): ok;
    /*printf("\n");  Debuging0 */
    /*cfprintf(stdout, 92, "Saída do programa\n");  Debuging0 */
    if(ok){
        /*print_HashT(dict);  Debuging0 */
        fprint_MemMap(stdout, map); /* Debuging2 */
        fprint_MemMap(out, map);
        /*printf("\n");  Debuging0 */
    }
    /*cfprintf(stdout, 92, "Liberando Memória\n");  Debuging0 */
    free_MemMap(&map);
    free_HashT(&dict);
    return ok;
}
