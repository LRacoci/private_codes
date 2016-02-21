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

void print_map_line(FILE * out, unsigned int out_line, long unsigned int arg) {
    short int i, j;
    long unsigned int l0[4];
    unsigned int l[4] = {0xFF, 0xFFF, 0xFF, 0xFFF};
    for(i = 0; i < 4; i++){
        l0[i] = arg;
        for(j = 0; j < i; j++){
            l0[i] /= l[j];
        }
        l[i] = l0[i]%l[i];
    }
    fprintf(out, "%03X %02X %03X %02X %03X\n", out_line, l[0], l[1], l[2], l[3]);
}
void dir_set(String name, String arg1, long int arg, HashT dict){
    Data key = new(arg1, String), val = new(arg, LongInt);
    put_copy_HashT(dict, key, val );
}

bool first_pass(FILE * src, FILE * out, HashT dict){
    unsigned int i = 0, in_line, aux, out_line, w = 0, aux_read;
    unsigned short int narg = 0;
    long int arg[2];
    /*bool ok = true;*/
    Data d_aux1 = NULL, d_aux2 = NULL;
    bool is_instruction = false, instruction_ready = false, notend;
    TypeWord estate = TYPE_WORD_NONE;
    TypeDir type_dir = NONE;
    TypeInstr type_instr = MAX_INSTR;
    String str[3] = {NULL};
	for(
		rewind(src),
        in_line = 1,
        out_line = 0,
        str[2] = fgetword(src, &aux, &notend),
        in_line += aux;

        notend &&
        aux != -1;

        str[2] = fgetword(src, &aux, &notend),
        in_line += aux
	){
        w = aux > 0 ? 0 : w + 1;
        is_instruction = false;
        if (
            estate == DIRECTIVE &&
            type_dir != NONE &&
            narg == dir[type_dir].n_args
        ){

            switch(type_dir){
                case NONE: break;
                case set:
                    break;
                case org:
                    out_line = arg[narg-1]*2;
                    break;
                case align:
                    if(out_line%2 == 1){
                        fprintf(out, "00 000\n");
                    }else{
                        out_line++;
                    }
                    break;
                case wfill:
                    if(out_line == 1){
                        stderror(in_line, "Trying to wfill from the right");
                    }
                    if(narg == 1){
                        stderror(in_line, "Missing arguments for wfill");
                    }if(out_line/2 + arg[0] >= IAS_MAX_LINE_NUMBER){
                        stderror(in_line, "Wfill overflows the available memory");
                    }
                    for(i = 0; i < arg[0]; i++){
                        print_map_line(out, out_line/2, arg[0]);
                    }
                    out_line += arg[0]*2;
                    break;
                case word:
                    if(out_line % 2 == 1){
                        stderror(in_line, "Trying to put a word in the right");
                    }
                    print_map_line(out, out_line/2, arg[0]);
                    out_line += 2;
                    break;
            }
            narg = 0;
            type_dir = NONE;
        }
        if (
            estate == INSTRUCTION &&
            type_instr < MAX_INSTR &&
            instruction_ready
        ){
            i = mne[type_instr].opcode;
            i += ((mne[type_instr].option) && (out_line % 2)) ? 1 : 0;
            fprintf(out, "%02X ", i);
            if(dir[type_instr].arg){
                fprintf(out, "%03X", (unsigned int) arg[narg-1]);
            }else{
                fprintf(out, "000");
            }

            if(out_line%2 == 0){
                fprintf(out, "\n");
            }
        }
        printf("Line in %2d, Line out %X %c, Word %d: %s ",
                in_line, out_line/2, out_line % 2 ? 'D' : 'E', w, str[2]);
        printf("# ");
        if(str[2][0] == '.' ){
            printf("Diretiva");
            estate = DIRECTIVE;
            narg = 0;
            sscanf(str[2], ".%s", str[2]);
            for(i = 0; i < MAX_DIR && strcmp(str[2], dir[i].id); i++);
            type_dir = i;
        }else

        if(str[2][strlen(str[2]) - 1] == ':'){
            if(decimal(str[2][0])){
                printf(" Erro, rotulo nao deve começar com número");
                return false;
            }
            for(i = 0; str[2][i] == ':'; i++){
                if(!(alphanumeric(str[2][i]) || str[2][i] == '_')){
                    printf(" %c is not a valid Label character\n", str[2][i]);
                }
            }
            printf(" Rotulo");
            estate = LABEL;
            d_aux1 = new(str[2], String);
            d_aux2 = new(out_line, LongInt);
            put_copy_HashT(dict, d_aux1, d_aux2);
            printf("\nHash Table: Dict\n");
            print_HashT(dict);
            free_data(&d_aux1);
            free_data(&d_aux2);
        }else{
            if(str[2][0] == '"' && str[2][strlen(str[2]) -1] == '"'){
                if(estate == INSTRUCTION){
                    printf(" Argument of a instruction");
                    is_instruction = true;
                    if(type_instr < MAX_INSTR && mne[type_instr].arg){
                        instruction_ready = true;
                    }else{
                        printf("%s dont need arguments", mne[type_instr].id);
                        return false;
                    }
                }else{
                    printf(" Error, Not a argument of a instruction");
                    return false;
                }
                /*narg = 0;*/
                sscanf(str[2], "\"%[^\"]\"", str[2]);
                /*
                if(str[2][0] == '0' && str[2][1] == 'x'){
                    sscanf(str[2], "0x%s", str[2]);
                    error = false;
                    for(i = 0; str[2][i] && !error; i++){
                        if(!hexadecimal(str[2][i])){
                            error = true;
                            printf(" %c is not a valid hexadecimal character\n", str[2][i]);
                        }
                    }if(!error){
                        printf(" Hexadecimal Number");
                    }
                    sscanf(str[2], "%x", &aux);
                    arg[narg] = aux;
                }else if(between('0', str[2][0], '9')){
                    error = false;
                    for(i = 0; str[2][i] && !error; i++){
                        if(!decimal(str[2][i])){
                            printf(" %c is not a valid decimal character",  str[2][i]);
                            error = true;
                        }
                    }if(!error){
                        printf(" Decimal Number");
                    }
                    sscanf(str[2], "%ld", &arg[narg]);
                }
                */
            }/*else*/
            if(str[2][0] == '0' && str[2][1] == 'x'){
                if(estate == DIRECTIVE){
                    printf(" Argument of a directive");
                }else if(is_instruction){
                    is_instruction = false;
                }else if(estate == INSTRUCTION){
                    printf(" Error, Not a argument of a directive");
                    return false;
                }

                for(i = 2; str[2][i]; i++){
                    if(!hexadecimal(str[2][i])){
                        printf(" %c is not a valid hexadecimal character\n", str[2][i]);
                        return false;
                    }
                }
                printf(" Hexadecimal Number");
                sscanf(str[2], "%x", &aux_read);
                if(narg <= 2){
                    arg[narg] = aux_read;
                    narg++;
                }else{
                    printf(" Error, more then two arguments");
                    return false;
                }
            }else
            if(between('0', str[2][0], '9')){
                for(i = 0; str[2][i]; i++){
                    if(!decimal(str[2][i])){
                        printf(" %c is not a valid decimal character",  str[2][i]);
                        return false;
                    }
                }
                printf(" Decimal Number");
                sscanf(str[2], "%u", &aux_read);
                if(narg <= 2){
                    arg[narg] = aux_read;
                    narg++;
                }else{
                    printf(" Error, more then two arguments");
                }
            }
            else{
                for (i = 0; i < MAX_INSTR && strcmp(str[2], mne[i].id); i++);
                type_instr = i;
                if(type_instr != MAX_INSTR){
                    printf(" Instrucao: %s", mne[i].id);
                    estate = INSTRUCTION;
                    out_line += 1;
                }else{
                    d_aux1 = new(str[2], String);
                    if(is_in_HashT(dict, d_aux1)){
                        printf(" Rot or Sym");
                    }else{
                        printf(" Word not identified");
                        return false;
                    }
                    free_data(&d_aux1);
                }

            }
        }
        printf("\n");
        if(str[0]){
            free(str[0]);
            str[0] = NULL;
        }

        for(i = 0; i < 2; i++){
            str[i] = str[i+1];
        }
	}
    for(i = 0; i < 3; i++){
        if(str[i])
            free(str[i]);
    }

    return true;
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
