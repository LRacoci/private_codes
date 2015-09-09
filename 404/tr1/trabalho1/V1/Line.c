#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auxTypes.h"
#include "Line.h"
#include "Error.h"


void fprintLine(Line this, FILE * f){
	unsigned int i, j;
	fprintf(f, "%d", this->lnumber);
	for(i = 0; i < EXPRESSIONS_PER_LINE; i++){
		if(this->expr[i]){
			fprintf(f, " %s", this->expr[i]->keyword);
			for(j = 0; j < MAX_ARGUMENTS; j++){
				if(this->expr[i]->argument[j])
					fprintf(f, " %s", this->expr[i]->argument[j]->str);
			}
		}
	}
	fprintf(f, "\n");
}
void printLine(Line this){
	unsigned int i, j;
	printf("%d", this->lnumber);
	for(i = 0; i < EXPRESSIONS_PER_LINE; i++){
		if(this->expr[i]){
			printf(" %s", this->expr[i]->keyword);
			for(j = 0; j < MAX_ARGUMENTS; j++){
				if(this->expr[i]->argument[j])
					printf(" %s", this->expr[i]->argument[j]->str);
			}
		}
	}
	printf("\n");
}

Line new_line(){
	Line resp = malloc(sizeof (sLine));
	return resp;
}
void free_line(Line del){
	for(TypeExpr t = ROTULO; t < MAX_EXPRESSIONS; t++){
		if(del->expr[position(t)] != NULL){
			free_expr(del->expr[position(t)]);
		}
	}
	free(del);
}
void set_expr(Line l, TypeExpr _type, String _keyword){
	l->expr[position(_type)] = new_expr();
	l->expr[position(_type)]->type = _type;
	l->expr[position(_type)]->keyword = malloc(strlen(_keyword) * sizeof(char));
	strcpy(l->expr[position(_type)]->keyword, _keyword);
}
Expr new_expr(){
	unsigned short int i;
	Expr resp = malloc(sizeof(sExpr));
	resp->type = NAOSEI;
	resp->keyword = NULL;
	for(i = 0; i < MAX_ARGUMENTS; i++){
		resp->argument[i] = NULL;
	}
	return resp;
}
void set_arg(Line l, TypeExpr _type, String _name){

}
void free_expr(Expr del){
	int i;
	free(del->keyword);
	for(i = 0; i < MAX_ARGUMENTS; i++){
		if(del->argument[i] != NULL){
			free(del->argument[i]);
		}
	}
	free(del);
}
Line read_next_line(FILE * src, Exception e){
	Line resp = NULL;
	char c;
	char temp[MAX_KEY_WORD];
	unsigned short int k = 0;
	TypeExpr estado= NAOSEI;
	e = NULL;
	if(src == NULL){
		return resp;
	}
	c = fgetc(src);
	if(c != '\0' && c != '\n' && c != COMENT_CHAR && c != EOF){
		resp = new_line();
	}
	ungetc(c, src);

	while(fscanf(src, "%c", &c) != EOF){
		switch (c){
			case '\0': case '\n':
				return resp;
			case COMENT_CHAR: /* Código de comentário*/
				estado = COMENTARIO;
				break;
			case '.':
				estado = DIRETIVA;
				break;
			case ' ': case '\t':
				if(estado == DIRETIVA){
					set_expr(resp, DIRETIVA, temp);
					estado = ARG;
					k = 0;
				}

				break;
			case ':':
				set_expr(resp, ROTULO, temp);
				estado = NAOSEI;
				k = 0;
				break;
			case '"':
				switch (estado) {
					case COMENTARIO:
						e = start_warning_exception("Caractere '\"' nos comentários");
						break;
					case NAOSEI:
						set_expr(resp, INSTRUCAO, temp);
						k = 0;
						break;
					case INSTRUCAO:
						set_arg (resp, INSTRUCAO, temp);
						break;
					case ARG:

						break;
					case DIRETIVA:

						break;
					case ROTULO:

						break;
				}
				break;
			default:
				if(estado != COMENTARIO){
					temp[k++] = c;
				}
		}
	}
	return resp;
}
Line read_first_line(FILE * src){
	sException e = {true, "Não foi pssível ler a linha 0", -1}
	if(src == NULL){
		stderror(&e);
	}
	rewind(src);
	return read_next_line(src);
}
