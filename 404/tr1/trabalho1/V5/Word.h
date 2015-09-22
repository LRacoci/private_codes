#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auxTypes.h"
#include "iasDefs.h"
#include "genericDefs.h"
#include "Error.h"
#include "Data.h"

bool char_in_string(char target, String s);
String extract_Word(String str, const String f);
typedef enum TypeWord{
	LABEL,
	DIRECTIVE,
	INSTRUCTION,
	ARG_INSTR,
    ARG_DIR,
    TYPE_WORD_NONE
}TypeWord;
typedef enum TypeArg{
	HEX = 1,
	DEC = 2,
	SYM = 3,
	ROT = 4
} TypeArg;
typedef struct sArg{
    TypeArg t;
    union ContentArg{
        String * sym;
        unsigned long int hex;
        long int dec;
    }c;
}sArg, *Arg;
typedef struct Instr{
    TypeInstr t;
    Arg a;
} sInstr, *Instr;

typedef struct Dir{
    TypeInstr t;
    Arg a1;
    Arg a2;
} sDir, *Dir;

typedef struct sWord {
    unsigned int pos;
    TypeWord t;
    union ContentWord{
        Arg a;
        Dir d;
        Instr i;
    }c;
} sWord, *Word;

bool ungetword(FILE * src, String str);
String fgetword(FILE * src, unsigned int * lines, bool * ok);

String get_part_string(String src, int ini, int fim);

bool element_of(
    String e,
    char vet[][MAX_INSTR],
    func_comp cmp,
    unsigned int size
);
