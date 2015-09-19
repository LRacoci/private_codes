#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auxTypes.h"
#include "iasDefs.h"
#include "genericDefs.h"
#include "Error.h"
#include "Data.h"


typedef struct sMemWord{
	unsigned int pos;
	bool is_word;
	union sContent{
		struct sInstr{
			unsigned int code;
			unsigned int arg;
		} i [2];
		struct sWord{
			unsigned long long int w;
		} w;
	} c;
} sMemWord, *MemWord;

void fprint_ias_format(FILE * out, unsigned long long hex);
void fprint_MemWord(FILE * out, MemWord p);
size_t ___MemWord_size(Info i);
Info ___MemWord_copy(Info i);
Hash ___MemWord_hash(Info i);
Comp ___MemWord_comp(Info a, Info b);
