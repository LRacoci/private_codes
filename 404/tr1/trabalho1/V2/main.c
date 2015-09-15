#include <stdio.h>
#include <string.h>
/*
#include <stdlib.h>
#include "auxTypes.h"
#include "iasDefs.h"
#include "genericDefs.h"
#include "Error.h"
#include "Data.h"
*/
#include "Builder.h"
/*

void build(FILE * src, FILE * out) {
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

            switch(type_dir){
                case NONE:

                    break;
                case set:
                    printf("Argument of set");
                    break;
                case org:
                    out_line = arg[narg]*2;
                    break;
                case align:
                    out_line /= 2;
                    out_line *= 2;
                    break;
                case wfill:
                    switch (narg) {
                        case 0:
                        break;
                        case 1:
                        out_line += arg[narg]*2;
                        break;
                    }
                    break;
                case word:
                    out_line += 2;
                    break;
            }

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
            }else{
                printf(" Erro, provavelmente um rotulo ou um simbolo");
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
*/
int main(int argc, char *argv[]) {
	FILE *src = NULL, *out = NULL;
	String out_name;
	switch (argc){
		case 2:
			src = fopen(argv[1], "r");
			out_name = strcat(argv[1], ".aux");
			out = fopen(out_name, "w");
			break;
		case 3:
			src = fopen(argv[1], "r");
			out = fopen(argv[2], "w");
			break;
	}

	if( src == NULL ){
		throw(
			new_error_exception(
				"Error while opening the source file.\n", -1
			)
		);
		exit(EXIT_FAIL);
	}

	if( out == NULL ){
		throw(
			new_error_exception(
				"Error while opening the output file.\n", -1
			)
		);
		exit(EXIT_FAIL);
	}
    build(src, out);

    if(src)
        fclose(src);
    if(out)
        fclose(out);

    return EXIT_SUCESS;
}
