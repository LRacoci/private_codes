#include <stdio.h>
#include <stdlib.h>
#include "auxTypes.h"
#include "genericDefs.h"
#include "Error.h"

#define MAX_LINE 128
#define MAX_EXPRESSIONS 3
#define EXPRESSIONS_PER_LINE 2
#define MAX_KEY_WORD 66
#define MAX_ARGUMENTS 2
#define position(type_expression) (type_expression/2)


typedef enum TypeExpr{
	ROTULO = 1,
	DIRETIVA = 2,
	INSTRUCAO = 3,
	COMENTARIO,
	NAOSEI,
	ARG,
}TypeExpr;

typedef enum TypeArg{
	HEX,
	DEC,
	SYM,
	ROT
}TypeArg;

typedef struct sArg sArg, * Arg;
typedef struct sExpr sExpr, * Expr;

typedef struct sLine{
	struct sExpr{
		TypeExpr type;
		String keyword;
		struct sArg{
			TypeArg type;
			String str;
		} * argument[MAX_ARGUMENTS];
	} * expr[EXPRESSIONS_PER_LINE];
	unsigned int lnumber;
} sLine, * Line;


Expr new_expr();
void free_expr(Expr del);

Line new_line();
void free_line(Line del);
void fprintLine(Line this, FILE * f);
void set_expr(Line l, TypeExpr _type, String _keyword);

Expr new_expr();
void free_expr(Expr del);


Line read_next_line(FILE * src, Exception e);
Line read_first_line(FILE * src);
