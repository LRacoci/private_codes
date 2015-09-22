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
MemWord new_MemWord(unsigned int pos, bool is_word){
	unsigned short int i;
	MemWord new = malloc(sizeof(sMemWord));
	new->pos = pos;
	new->is_word = is_word;
	if(is_word){
		new->c.w.w = 0;
	}else{
		for(i = 0; i < 2; i++){
			new->c.i[i].code = 0;
			new->c.i[i].arg  = 0;
		}
	}
	return new;

}
bool insert_instr_MemMap(
	MemMap m,
	unsigned int code,
	unsigned int arg,
	unsigned int line
 ){
	if(!m) return false;
	if(!between(0, m->pos, 1023)) return false;
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
		m->m[(m->pos)/2] = new_MemWord(m->pos/2, false);
		m->m[(m->pos)/2]->c.i[(m->pos)%2].code = code;
		m->m[(m->pos)/2]->c.i[(m->pos)%2].arg = arg;
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
	if(!between(0, m->pos, 2*1023)){
		stderror(line, "Position %03X is not int he memory\n",
		m->pos/2
	);
		return false;
	}
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
		m->m[m->pos/2] = new_MemWord(m->pos/2, true);
		m->m[m->pos/2]->c.w.w = w;
		m->pos += 2;
	}
	return true;
}

void fprint_ias_format(FILE * out, unsigned long long int hex){
	char aux[65];
	unsigned int i, j, k, len, f[] = {2, 3, 2, 3};
	sprintf(aux, "%064llX", hex);
	len = strlen(aux);
	for(k = len -10, i = 0; i < 4; i++){
		fprintf(out, " ");
		for(j = 0; j < f[i]; j++, k++){
			fprintf(out, "%c", aux[k]);
		}
	}
	fprintf(out, "\n");
}
void fprint_MemWord(FILE * out, MemWord p){
	if(p == NULL){
		return;
	}
	fprintf(out, "%03X", p->pos);
	if(p->is_word){
		fprint_ias_format(out, p->c.w.w);
	}else{
		fprintf(
			out,
			" %02X %03X %02X %03X\n",
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
