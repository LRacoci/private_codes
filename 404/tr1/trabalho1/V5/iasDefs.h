#include "auxTypes.h"
#ifndef IAS_DEFS
#define IAS_DEFS

#define IAS_MAX_LINE_NUMBER 1024

#define MAX_DIR 5

typedef enum TypeInstr{
	LD = 0, LDm = 1, LD_abs = 2, LDmq = 3,
	LDmq_mx = 4, ST = 5, JMP = 6, JUMP_plus = 7, ADD = 8,
	ADD_abs = 9, SUB = 10, SUB_abs = 11, MUL = 12,
	DIF = 13, LSH = 14, RSH = 15, STaddr = 16, MAX_INSTR = 17
} TypeInstr;
typedef enum TypeDir{
	SET = 0,
	ORG = 1,
	ALIGN = 2,
	WFILL = 3,
    WORD = 4,
    NONE = 5
} TypeDir;


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
