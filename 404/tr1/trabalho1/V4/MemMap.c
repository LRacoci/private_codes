#include "MemMap.h"

void fprint_ias_format(FILE * out, unsigned long long hex){
	char aux[20];
	unsigned short int i, j, k, f[] = {2, 3, 2, 3};
	sprintf(aux, "%020llX", hex);
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
	fprintf(out, "%03X ", p->pos);
	if(p->is_word){
		fprint_ias_format(out, p->c.w.w);
	}else{
		fprintf(out, "%02X %03X %02X %03X\n", p->c.i[0].code, p->c.i[0].arg, p->c.i[1].code, p->c.i[1].arg);
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
    return numcomp(((MemWord)a)->pos, ((MemWord)b)->pos);
}
