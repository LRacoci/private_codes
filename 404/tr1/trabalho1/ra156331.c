#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 128
#define MAX_EXPRESSIONS 3
#define MAX_TYPE MAX_LINE/(MAX_EXPRESSIONS-1)
#define MAX_KEY_WORD 66
#define EXIT_FAIL -1

typedef char* String;

typedef enum bool{true, false} bool;

typedef enum te{
	ROTULO,
	DIRETIVA,
	INSTRUCAO,
	COMENTARIO,
	LINE
} Type_Expr;

typedef enum ta{
	HEX,
	DEC,
	SYM,
	ROT
} Type_Arg;

typedef struct a{
	Type_Arg type;
	char * str_representation;
}sArg, * Arg;

typedef struct e{
	Type_Expr type;
	char keyword[MAX_KEY_WORD];
	Arg argument[2];
}sExpr, * Expr;


typedef struct l{
	Expr expr[MAX_EXPRESSIONS-1];
	unsigned int lnumber;
}sLine, * Line;

Line new_line(){
	Line resp = malloc(sizeof (sLine));
	for(int i = 0; i < MAX_EXPRESSIONS-1; i++){
		resp->expr[i] = NULL;
	}
	
}
Line next_line(FILE * src){
	Line resp = NULL;
	char c;
	bool create[(int) sizeof Type_Expr] = {false};
	Type_Expr = estado;

	if(src == NULL){
		return resp;
	}
	while(fscanf(src, "%c", &c) != EOF){
		if(create[LINE]){
			resp = new_line();
			create[LINE] = false;
		}
		switch (c){
			case '\0': case '\n':
				return resp;
			case '#': /* Código de comentário*/
				estado = COMENTARIO
				break;
			case: '.':
				estado = DIRETIVA;
				create[DIRETIVA] = true;

				break;
			default:
				if(estado != COMENTARIO){
					if(('A' <= c && c <= 'Z') || c == ''){

					}
				}
		}
	}
	return resp;
}
Line first_line(FILE * src){
	if(src != NULL){
		rewind(src);
		return next_line(src);
	}
}

void stderror(const char * msg, unsigned int line){
	fprintf(stderr, "ERROR on line %d\n", line);
	fprintf(stderr, msg);
	fprintf(stderr, "\n");
	exit(EXIT_FAIL);
}

FILE * build(FILE * src){
	FILE *out;
	char c;
	Line l;
	unsigned int i;
	for (l = first_line(src), i= 0; 
		 l != NULL; 
		 l = next_line(src), i++)
	{
		l->lnumber = i;


	}

	while(fscanf(src, "%c", &c) != EOF){
		switch (c){
			case '#': /* Código de comentário*/
				estado = COMENTARIO
			case '\0': case '\n':

			case: '.':
				estado = DIRETIVA;
				
			default:
				if(estado != COMENTARIO){
					if(('A' <= c && c <= 'Z') || c == ''){

					}
				}
		}
		printf("%c", c);
		fprintf(out, "%c", c);
	}
	return out
}
int main(int argc, char *argv[]) {
	FILE *src, *out;
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
		perror("Error while opening the source file.\n");
		exit(EXIT_FAIL);
	}
	
	if( out == NULL ){
		perror("Error while opening the output file.\n");
		exit(EXIT_FAIL);
	}
	out = build(src);
	
	fclose(src);
	fclose(out);
   	return EXIT_SUCESS;
}