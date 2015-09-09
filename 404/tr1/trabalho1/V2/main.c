#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auxTypes.h"
#include "iasDefs.h"
#include "genericDefs.h"
#include "Error.h"


static char mne[][17] = { "LD",
    "LD-", "LD|", "LDmq", "LDmq_mx",
    "ST", "JMP", "JUMP+", "ADD",
    "ADD|", "SUB", "SUB|", "MUL",
    "DIF", "LSH", "RSH", "STaddr"};

Hash h(String s){
    Hash h = 5381;

    for(;*s;s++){
        h = ((h << 5) + h) + *s;
    }
    return h;
}

bool char_in_string(char target, String s){
    if(s == NULL){
        return false;
    }
    if(target == '\0'){
        return true;
    }
    for(; *s; s++){
        if(target == *s){
            return true;
        }
    }
    return false;
}

unsigned int fgetword(FILE * src, String word){
    unsigned int resp = 0;
    int c;
    for(;c != EOF &&  char_in_string(c, " \t\n"); c = fgetc(src)){
        if(c == '\n'){
            resp++;
        }
    }
    for(;c != EOF && !char_in_string(c, " \t\n"); c = fgetc(src)){
        *word = c;
        word++;
    }
    if(c == '\n'){
        resp++;
    }
    return c == EOF ? -1 : resp;

}

void build(FILE * src, FILE * out) {
    unsigned int line, aux;
    char word[66];
	for (
			rewind(src), line = 0;
            aux != -1;
			aux = fgetword(src, word), line += aux
		)
	{

	}
}
int main(int argc, char *argv[]) {
	FILE *src = NULL, *out = NULL;
	String out_name;
	switch (argc){
		case 2:
			src = fopen(argv[1], "r");
			out_name = strcat(argv[1], ".hex");
			out = fopen(out_name, "w");
			break;
		case 3:
			src = fopen(argv[1], "r");
			out = fopen(argv[2], "w");
			break;
	}

	if( src == NULL ){
		stderror(
			new_error_exception(
				"Error while opening the source file.\n", -1
			)
		);
		exit(EXIT_FAIL);
	}

	if( out == NULL ){
		stderror(
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
