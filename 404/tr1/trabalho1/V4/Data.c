#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"

Data new_data(
    Info i , size_t s,
    func_free free_i,
    func_copy cpy,
    func_print p,
    func_hash h,
    func_comp compare,
    DataType dT
){
    Data d = malloc(sizeof(sData));
    d->info = i;
    d->size = s;
    d->del = free_i;
    d->copy = cpy;
    d->print = p;
    d->hash = h;
    d->cmp = compare;
    d->dType = dT;

    return d;
}

Data copy_data(Data src){
    Data d;
    Info i;
    if(!src){
        return NULL;
    }
    if(src->copy){
        i = src->copy(src->info);
    }else{
        i = malloc(src->size);
        memcpy(i, src->info, src->size);
    }

    d = new_data(
        i,
        src->size,
        src->del,
        src->copy,
        src->print,
        src->hash,
        src->cmp,
        src->dType
    );

    return d;
}
Hash h(Data d){
    return d->hash(d->info);
}
Info get_info_data(Data d){
    return d->info;
}

Comp comp_data(Data a, Data b){
    func_comp infocmp = a->cmp ? a->cmp : b->cmp ? b->cmp : NULL;
    if(infocmp){
        return infocmp(a->info, b->info);
    }else{
        return comp_info(a->info, b->info, min(a->size, b->size));
    }

}
bool eq_data(Data a, Data b){
    if(h(a) != h(b)){
        return false;
    }
    return comp_data(a, b) == 0;
}
void print_data(Data d){
    if(!d) return;
    d->print(d->info);
}
void free_data(Data * d){
    if(!(*d))
        return;

    if((*d)->del){
        (*d)->del(&((*d)->info) );
    }else{
        free((*d)->info);
    }
    free((*d));
    *d = NULL;
}

/* String Basics Definition */
/***************************/
size_t ___String_size(Info i){
    return sizeof(char) * (
        strlen((String)i) + 1
    );
}
void ___String_print(Info i){
    printf("%s", *(String*)(i));
}
void ___String_free(Info *i){
    free(*(String*)(*i));
    free(*i);
    *i = NULL;
}
Info ___String_copy(Info i){
    unsigned int len, j;
    String* resp;
    if(!i){
        return i;
    }
    for(len = 0; (*(String*)i)[len] != '\0'; len++);
    len++;
    resp = malloc(sizeof(String));
    *resp = malloc(len*sizeof(char));

    for(j = 0; j < len; j++){
        (*resp)[j] = (*(String*)i)[j];
    }
    return resp;
}
/* djb2 by Dan Bernstein */
Hash ___String_hash(Info i){
    unsigned int j;
    unsigned char* str = *(unsigned char* *) i;
    Hash h = 5381;
    int c;
    for(h = 5381, j = 0; str[j]; j++){
        c = str[j];
        h = ((h << 5) + h) + c;

    }

    return h;
}
Comp ___String_comp(Info a, Info b){
    return strcmp((String) a, (String) b);
}

BodyDefinition(int, "%2d", st)
BodyDefinition(LongInt, "%2ld", st)
