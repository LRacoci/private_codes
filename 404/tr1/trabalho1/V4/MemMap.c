#include "MemMap.h"

MemMap new_MemMap(){
	short unsigned int i;
	MemMap n = malloc(sizeof(sMemMap));
	for(i = 0; i < MAX_MEM_MAP; i++){
		n->m[i] = NULL;
	}
	n->pos = 0;
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
	unsigned int code,
	unsigned int arg,
	unsigned int line
 ){
	if(!m) return false;
	if(m->m[(m->pos)/2]){
		if(m->m[(m->pos)/2]->is_word){
			stderror(line, "Position %03X have already a word", (m->pos)/2);
			return false;
		}else{
			if(
				m->m[(m->pos)/2]->c.i[(m->pos)%2].code && m->m[(m->pos)/2]->c.i[(m->pos)%2].arg
			){
				stderror(
					line,
					"Position %03X %c have already a instruction (%02X %03X)", (m->pos)/2, ((m->pos)%2) ? 'D' : 'E',
					m->m[(m->pos)/2]->c.i[(m->pos)%2].code,
					m->m[(m->pos)/2]->c.i[(m->pos)%2].arg
				);
				return false;

			}else{
				m->m[(m->pos)/2]->c.i[(m->pos)%2].code = code;
				m->m[(m->pos)/2]->c.i[(m->pos)%2].arg = arg;
				m->m[(m->pos)/2]->pos = m->pos/2;
				m->pos++;
			}
		}
	}else{
		m->m[(m->pos)/2] = malloc(sizeof(sMemWord));
		m->m[(m->pos)/2]->is_word = false;
		m->m[(m->pos)/2]->c.i[(m->pos)%2].code = code;
		m->m[(m->pos)/2]->c.i[(m->pos)%2].arg = arg;
		m->m[(m->pos)/2]->pos = m->pos/2;
		m->pos++;
	}

	return true;

}
bool insert_word_MemMap(
	MemMap m,
	unsigned long long int w,
	unsigned int line
){
	unsigned short int i;
	if(!m) return false;
	if(m->m[m->pos/2]){
		if(m->m[m->pos/2]->is_word){
			stderror(line, "Position %03X have already a word\n", m->pos/2);
			return false;
		}else{
			for(i = 0; i < 2; i++){
				if(
					m->m[m->pos/2]->c.i[i].code &&
					m->m[m->pos/2]->c.i[i].arg
				){
					stderror(
						line,
						"Position %03X %c have already a instruction (%02X %03X)\n",
						m->pos/2,
						(i) ? 'D' : 'E',
						m->m[m->pos/2]->c.i[i].code,
						m->m[m->pos/2]->c.i[i].arg
					);
					return false;
				}
			}
		}
	}else{
		m->m[m->pos/2] = malloc(sizeof(sMemWord));
		m->m[m->pos/2]->is_word = true;
		m->m[m->pos/2]->c.w.w = w;
		m->m[m->pos/2]->pos = m->pos/2;
		m->pos += 2;
	}
	return true;
}

void fprint_ias_format(FILE * out, unsigned long long hex){
	char aux[20];
	unsigned short int i, j, k, f[] = {2, 3, 2, 3};
	sprintf(aux, "%010llX", hex);
	for(k = 0, i = 0; i < 4; i++){
		for(j = 0; j < f[i]; j++, k++){
			fprintf(out, "%c",aux[k]);
		}
		fprintf(out, " ");
	}
	fprintf(out, "\n");
}
void fprint_MemWord(FILE * out, MemWord p){
	if(p == NULL){
		return;
	}
	if(p->is_word){
		fprint_ias_format(out, p->c.w.w);
	}else{
		fprintf(
			out,
			"%02X %03X %02X %03X\n",
			p->c.i[0].code,
			p->c.i[0].arg,
			p->c.i[1].code,
			p->c.i[1].arg
		);
	}
}

size_t ___MemWord_size(Info i){
    return sizeof(sMemWord);
}
void ___MemWord_print(Info i){
	fprint_MemWord(stdout, *(MemWord*)(i));
}
void ___MemWord_free(Info *i){
    free(*(MemWord*)(*i));
    free(*i);
    *i = NULL;
}
Info ___MemWord_copy(Info i){
    MemWord* resp;
    if(!i){
        return i;
    }
    resp = malloc(sizeof(MemWord));
    *resp = malloc(___MemWord_size(i));
	**(MemWord*)resp = **(MemWord*)i;
	if((*(MemWord*)i)->is_word == false){
		(*(MemWord*)i)->c.i[0] = (*(MemWord*)i)->c.i[0];
		(*(MemWord*)i)->c.i[1] = (*(MemWord*)i)->c.i[1];
	}
    return resp;
}
/* Unused */
Hash ___MemWord_hash(Info i){
    return 0;
}
Comp ___MemWord_comp(Info a, Info b){
    return numcmp(((MemWord)a)->pos, ((MemWord)b)->pos);
}
