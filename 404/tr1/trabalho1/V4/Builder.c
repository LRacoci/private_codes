#include "Builder.h"



static struct m{
    char id[10];
    unsigned short int opcode;
    __extension__ bool arg:1;
    __extension__ bool option:1;
} mne[MAX_INSTR] = {
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
    {     "DIF", 0x0C , true  , false },
    {     "LSH", 0x14 , false , false },
    {     "RSH", 0x15 , false , false },
    {  "STaddr", 0x12 , true  , true  }
};


static struct d{
    TypeDir dirType;
    char id[10];
    unsigned int n_args;
    struct Arg{
        TypeArg name[4];
        long int lowest;
        long int highest;
    }arg[2];
} dir[MAX_DIR] = {
    {   set ,  "set", 2, {
        {{SYM}                                         },
        {{HEX, DEC}         , 0           , 0x7FFFFFFF }
    }},
    {   org ,  "org", 1, {
        {{HEX, DEC}          , 0           , 0x3FF     }
    }},
    { align ,"align", 1, {
        {{DEC}              , 0           , 0x3FF      }
    }},
    { wfill ,"wfill", 2, {
        {{     DEC          }, 1          , 0x3FF      },
        {{HEX, DEC, ROT, SYM}, -0x80000000, 0x7FFFFFFF }
    }},
    {  word , "word", 1, {
        {{HEX, DEC, ROT, SYM}, 0          , 0x7FFFFFFF }
    }}
};

bool second_pass(FILE * src, FILE * out, HashT dict){
    bool ok = true;
    return ok;
}

void dir_set(String name, String arg1, long int arg, HashT dict){
    Data key = new(arg1, String), val = new(arg, LongInt);
    put_copy_HashT(dict, key, val);
    free_data(&key); free_data(&val);
}

bool validate_label(String str, unsigned int line, HashT ht){
    Data key;
    bool resp = true;
    unsigned int i;
    if(decimal(str[0])){
        stderror(line, "Erro, rotulo nao deve começar com número\n");
        return false;
    }
    for(i = 0; str[i] == ':'; i++){
        if(!(alphanumeric(str[i]) || str[i] == '_')){
            stderror(line, " %c is not a valid Label character\n", str[i]);
        }
    }
    key = new(str, String);
    if(is_in_HashT(ht, key)){
        resp = false;
    }
    free_data(&key);
    return resp;
}

bool validate_dir(String str, TypeDir * t, unsigned int line){
    unsigned short int i;
    sscanf(str, ".%s", str);
    for(i = 0; i < MAX_DIR && strcmp(str, dir[i].id); i++);
    if(i == MAX_DIR){
        stderror(line, "[.%s] is not a valid directive", str);
        return false;
    }
    *t = i;
    return true;
}

bool validate_argument(String str, TypeArg * t, bool  *instr, unsigned int line){
    unsigned short int i;

    if(str[0] == '"' && str[strlen(str) -1] == '"'){
        *instr = true;
        sscanf(str, "\"%[^\"]\"", str);

    }
    *instr = false;
    if(str[0] == '0' && str[1] == 'x'){
        *t = HEX;
        for(i = 2; str[i]; i++){
            if(!hexadecimal(str[i])){
                stderror(line, "%c is not a valid hexadecimal character\n", str[i]);
                return false;
            }
        }
    }else if(between('0', str[0], '9') || str[0] == '-'){
        for(i = 1; str[i]; i++){
            if(!decimal(str[i])){
                stderror(line,"%c is not a valid decimal character",  str[i]);
                return false;
            }
        }
    }
    return true;
}

bool validate_instruction(String str, TypeInstr *t, unsigned int line){
    unsigned short int i;
    for(i = 0; i < MAX_INSTR && strcmp(str, mne[i].id); i++);
    if(i == MAX_DIR){
        stderror(line, "[.%s] is not a valid directive", str);
        return false;
    }
    *t = i;
    return true;
}

bool first_pass(FILE * src, FILE * out, HashT dict){
    /* Retorno da função */
    bool ok = true;
    unsigned int
    m_pos = 0,  /* posição de montagem */
    line = 0,  /* linha de entrada */
    len, /* tamanho da string */
    wpl, /*palavras por linha*/
    el = 0; /* Conta \n's */
    bool instr, /* checar se eh uma instrução */
    nef = false; /* indica se o arquivo de entrada ja chegou ao fim */
    String w;

    union Type{
        TypeDir   d;
        TypeInstr i;
        TypeArg   a;
    }t;

    for(
        nef = false, el = 0, w = NULL;
        ok && nef;
        w = fgetword(src, &el, &nef), line += el
    ){
        if(!w) {
            continue;
        }
        wpl = (el == 0)? (wpl + 1) : 0;

        len = strlen(w);

        if(seems_directive(w)){
            ok = validate_dir(w, &t.d, line);
        }else if(seems_label(w)){
            ok = validate_label(w, line, dict);
        }else if(seems_argument(w)){
            ok = validate_argument(w, &t.a, &instr, line);
        /* Ainda pode ser argumento de diretiva ou instrução */
        }else{
            ok = validate_instruction(w, &t.i, line);
            ok = ok? interpret_instruction(w, t.i, line) : ok
            if (ok){
                m_pos++;
            }
        }
        free(w);
    }
    return ok;
}

bool build(FILE * src, FILE * out) {
    bool ok = true;
    HashT dict = new_HashT();
    ok = first_pass(src, out, dict);
    print_HashT(dict);
    ok = ok? second_pass(src, out, dict) : ok;
    free_HashT(&dict);
    return ok;
}
