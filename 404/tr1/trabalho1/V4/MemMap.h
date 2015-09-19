#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auxTypes.h"
#include "iasDefs.h"
#include "genericDefs.h"
#include "Error.h"
#include "Data.h"

#define MAX_MEM_MAP 1024

typedef struct sMemMap{
	MemWord m[MAX_MEM_MAP];
}sMemMap, *MemMap;

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

MemMap new_MemMap(){
	short unsigned int i;
	MemMap n = malloc(sMemMap);
	for(i = 0; i < MAX_MEM_MAP; i++){
		n[i] = NULL;
	}
	return n;
}
void free_MemMap(MemMap *del){
	unsigned short int i;
	for(i = 0; i < MAX_MEM_MAP; i++){
		if((*del)->m[i]){
			free((*del)->m[i]);
			(*del)->m[i] = NULL;
		}
	}
	free(*del);
	*del = NULL;
}
void fprint_MemMap(FILE * out, MemMap m){
	short unsigned int i;
	if(!m) return;
	for(i = 0; i < MAX_MEM_MAP; i++){
		if(m->m[i]){
			fprint_MemWord(out, m->m[i]);
		}
	}
}
bool insert_instr_MemMap(
	MemMap m,
	unsigned int pos_m,
	unsigned int code;
	unsigned int arg;
	unsigned int line;
 ){
	bool resp;
	if(!m) return false;
	if(m->m[pos_m/2]){
		if(m->m[pos_m/2]->is_word){
			stderror(line, "Position %03X have already a word", pos_m/2);
			return false;
		}else{
			if(
				m->m[pos_m/2]->c.i[pos_m%2].code && m->m[pos_m/2]->c.i[pos_m%2].arg
			){
				stderror(
					line,
					"Position %03X %c have already a instruction (%02X %03X)", pos_m/2, (pos_m%2) ? 'D' : 'E',
					m->m[pos_m/2]->c.i[pos_m%2].code,
					m->m[pos_m/2]->c.i[pos_m%2].arg
				);
				return false;

			}else{
				m->m[pos_m/2]->c.i[pos_m%2].code = code;
				m->m[pos_m/2]->c.i[pos_m%2].arg = arg;
				m->m[pos_m/2]->pos = pos_m/2;
			}
		}
	}else{
		m->m[pos_m/2] = malloc(sizeof(sMemWord)){
		m->m[pos_m/2]->pos = pos_m/2;
		m->m[pos_m/2]->is_word = false;
		m->m[pos_m/2]->c.i[pos_m%2].code = code;
		m->m[pos_m/2]->c.i[pos_m%2].arg = arg;
		}
	}

	return resp;

}
bool insert_word_MemMap(
	MemMap m,
	unsigned int pos_m,
	unsigned long long int w,
	unsigned int line
){
	unsigned short int i;
	if(!m) return false;
	if(m->m[pos_m/2]){
		if(m->m[pos_m/2]->is_word){
			stderror(line, "Position %03X have already a word\n", pos_m/2);
			return false;
		}else{
			for(i = 0; i < 2; i++){
				if(
					m->m[pos_m/2]->c.i[i].code && m->m[pos_m/2]->c.i[i].arg
				){
					stderror(
						line,
						"Position %03X %c have already a instruction (%02X %03X)\n", pos_m/2, (i) ? 'D' : 'E',
						m->m[pos_m/2]->c.i[i].code,
						m->m[pos_m/2]->c.i[i].arg
					);
					return false;
				}
			}
		}
	}else{
		m->m[pos_m/2] = malloc(sizeof(sMemWord)){
		m->m[pos_m/2]->pos = pos_m/2;
		m->m[pos_m/2]->is_word = true;
		m->m[pos_m/2]->c.w = w;
		}
	}
}

void fprint_ias_format(FILE * out, unsigned long long hex);
void fprint_MemWord(FILE * out, MemWord p);
size_t ___MemWord_size(Info i);
Info ___MemWord_copy(Info i);
Hash ___MemWord_hash(Info i);
Comp ___MemWord_comp(Info a, Info b);
