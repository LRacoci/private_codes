#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"

Data new_data(
    Info i , size_t s,
    func_free free_i,
    func_copy cpy,
    func_print p,
    func_hash h
){
    Data d = malloc(sizeof(sData));
    d->info = i;
    d->size = s;
    d->del = free_i;
    d->copy = cpy;
    d->print = p;
    d->hash = h;

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

    d = new_data(i, src->size, src->del, src->copy, src->print, src->hash);

    return d;
}
Hash h(Data d){
    return d->hash(d->info);
}
Info get_info_data(Data d){
    return d->info;
}
short int comp_data(Data a, Data b, func_comp infocmp){
    return infocmp(a->info, b->info);
}
void print_data(Data d){
    if(!d) return;
    d->print(d->info);
}
void free_data(Data d){
    if(!d)
        return;

    if(d->del){
        d->del(d->info);
    }else{
        free(d->info);
    }
    free(d);
}



void __int_print(Info i){
    printf("%8d", *(int*)(i));
}
void __int_free(Info i){
    free(i);
}
Info __int_copy(Info i){
    Info resp = malloc(sizeof(int));
    *(int*)resp = *(int*)i;
    return resp;
}
Hash __int_hash(Info i){
    return (Hash)*(int*)(i);
}


void __String_print(Info i){
    printf("%s", *(String*)(i));
}
void __String_free(Info i){
    free(i);
}
Info __String_copy(Info i){
    Info resp = malloc((strlen((String)i) + 1)* sizeof(char));
    strcpy(*(String*)resp, *(String*)i);
    return resp;
}
/* djb2 by Dan Bernstein */
Hash __String_hash(Info i){
    unsigned char* str = *(unsigned char* *) i;
    Hash h = 5381;
    int c;
    while (c = *str++)
        h = ((h << 5) + h) + c;
    return h;
}

void __List_print(Data d){
    print_list(d->info);
}
void __List_free(Info i){
    free_list(i);
}
Info __List_copy(Info i){
    return copy_list(i);
}
Hash __List_hash(Info i){
    return hash_list(i);
}
