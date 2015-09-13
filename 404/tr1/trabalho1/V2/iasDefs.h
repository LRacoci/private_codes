#include "auxTypes.h"
#ifndef IAS_DEFS
#define IAS_DEFS

#define IAS_MAX_LINE_NUMBER 1024

#define MAX_INSTR 17
#define MAX_DIR 5


typedef enum TypeArg{
	HEX,
	DEC,
	SYM,
	ROT
} TypeArg;

typedef enum TypeDir{
	set = 0,
	org = 1,
	align = 2,
	wfill = 3,
    word = 4,
    NONE = 5
} TypeDir;

typedef enum TypeExpr{
	ROTULO,
	DIRETIVA,
	INSTRUCAO,
	ARG_INSTR,
    ARG_DIR1,
    ARG_DIR2,
    NAOSEI
}TypeExpr;


#define between(a, b, c) ((a) <= (b) && (b) <= (c))

#define alphanumeric(a) ( \
    between('a', (a), 'z') || \
    between('A', (a), 'Z') || \
    between('0', (a), '9') \
)
#define hexadecimal(a) ( \
    decimal(a) || \
    between('A', (a), 'F') || \
    between('a', (a), 'f') \
)
#define decimal(a) ( \
    between('0', (a), '9') \
)
#endif
