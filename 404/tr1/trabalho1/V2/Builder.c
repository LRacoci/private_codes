#include "Builder.h"

void print_map_line(FILE * out, unsigned int out_line, long int arg) {

}
void dir_set(String name, String arg1, long int arg, HashT dict){
    char[MAX_ARG] arg
    put_copy_HashT(dict, )
}

void first_pass(FILE * src, FILE * out, HashT dict){
    unsigned int i = 0, in_line, aux, out_line, w = 0, aux_read;
    unsigned short int narg;
    long int arg[2];
    bool error;
    TypeExpr estate = NAOSEI;
    TypeDir type_dir = NONE;
    String str[3] = {NULL};
	for (
			rewind(src),
            in_line = 1,
            out_line = 0,
            aux = fgetword(src, &str[2]),
            in_line += aux;

            aux != -1;

            aux = fgetword(src, &str[2]),
            in_line += aux
		)
	{
        w = aux > 0 ? 0 : w + 1;
        if (
            estate == DIRETIVA &&
            type_dir != NONE &&
            narg+1 == dir[type_dir].n_args
        ){
            switch(type_dir){
                case set:
                    dir_set(str[0], str[1], arg[1], dict);
                    break;
                case org:
                    out_line = arg[narg]*2;
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
                    if(narg == 0){
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
                    if(out_line == 1){
                        stderror(in_line, "Trying to put a word in the right");
                    }
                    print_map_line(out, out_line/2, arg[0]);
                    out_line += 2;
                    break;
            }
        }

        printf("Line in %2d, Line out %X %c, Word %d: %s ",
                in_line, out_line/2, out_line % 2 ? 'D' : 'E', w, str[2]);
        printf("# ");
        if(str[2][0] == '.' ){
            printf("Diretiva");
            estate = DIRETIVA;
            narg = 0;
            sscanf(str[2], ".%s", str[2]);
            for(i = 0; i < MAX_DIR && strcmp(str[2], dir[i].id); i++);
            type_dir = i;
        }else
        if(str[2][0] == '"' && str[2][strlen(str[2]) -1] == '"'){
            if(estate == INSTRUCAO){
                printf(" Argument of a instruction");
            }else{
                printf(" Error, Not a argument of a instruction");
            }

            narg = 0;
            sscanf(str[2], "\"%[^\"]\"", str[2]);
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

        }else
        if(str[2][strlen(str[2]) - 1] == ':'){
            error = false;
            if(decimal(str[2][0])){
                printf(" Erro, rotulo nao deve começar com número");
            }
            for(i = 0; str[2][i] == ':' && !error; i++){
                error |= !(alphanumeric(str[2][i]) || str[2][i] == '_');
            }
            if(!error){
                printf(" Rotulo");
                estate = ROTULO;
            }else{
                printf(" Erro, rotulo nao alphanumerico ou  '_'");
            }
        }else
        if(str[2][0] == '0' && str[2][1] == 'x'){
            error = false;
            for(i = 0; str[2][i] && !error; i++){
                if(!hexadecimal(str[2][i])){
                    error = true;
                    printf(" %c is not a valid hexadecimal character\n", str[2][i]);
                }
            }if(!error){
                printf(" Hexadecimal Number");
            }
            sscanf(str[2], "%x", &aux_read);
            if(narg < 2){
                arg[narg] = aux_read;
            }else{
                printf(" Error, more then two arguments");
            }

            narg++;
        }else
        if(between('0', str[2][0], '9')){
            error = false;
            for(i = 0; str[2][i] && !error; i++){
                if(!decimal(str[2][i])){
                    printf(" %c is not a valid decimal character",  str[2][i]);
                    error = true;
                }
            }if(!error){
                printf(" Decimal Number");
            }
            sscanf(str[2], "%u", &aux_read);
            if(narg < 2){
                arg[narg] = aux_read;
            }else{
                printf(" Error, more then two arguments");
            }
        }else{
            for(i = 0; i < MAX_INSTR && strcmp(str[2], mne[i].id); i++);
            if(i != MAX_INSTR){
                printf(" Instrucao: %s", mne[i].id);
                estate = INSTRUCAO;
                out_line += 1;
            }else if(s_in_HashT(dict, str[2])){
                printf(" Rot or Sym");
            }else{
                printf(" Word not identified");
            }
        }
        printf("\n");
        free(str[0]);
        for(i = 0; i < 1; i++){
            str[i] = str[i+1];
        }
	}
    for(i = 0; i < 3; i++){
        free(str[i]);
    }
}

void build(FILE * src, FILE * out) {
    HashT dict = new_HashT();
    first_pass(src, out, dict);
    print_HashT(dict);
    second_pass(src, out, dict);
    free_HashT(dict);
}
