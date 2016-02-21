#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auxTypes.h"
#include "iasDefs.h"
#include "genericDefs.h"
#include "Error.h"
#include "Data.h"

#define MAX_MEM_MAP 1024
/* Declara o sruct responsável por guardar uma palavra de memoria */
typedef struct sMemWord{
	unsigned int pos;
	bool is_word;
	union sContent{
		struct sI{
			unsigned int code;
			unsigned int arg;
		} i [2];
		struct sW{
			unsigned long long int w;
		} w;
	} c;
} sMemWord, *MemWord;
/* Declara um Mapa de Memoria, vetor de palavras de memoria
 * juntamente com um indicador da posição atual de montagem */
typedef struct sMemMap{
	unsigned int pos;
	MemWord m[MAX_MEM_MAP];
}sMemMap, *MemMap;



MemMap new_MemMap();
void free_MemMap(MemMap *del);
void fprint_MemMap(FILE * out, MemMap m);
bool insert_instr_MemMap(
	MemMap m,
	unsigned int code,
	unsigned int arg,
	unsigned int line
);
bool insert_word_MemMap(
	MemMap m,
	unsigned long long int w,
	unsigned int line
);

void fprint_ias_format(FILE * out, unsigned long long hex);
void fprint_MemWord(FILE * out, MemWord p);
size_t ___MemWord_size(Info i);
Info ___MemWord_copy(Info i);
Hash ___MemWord_hash(Info i);
Comp ___MemWord_comp(Info a, Info b);
