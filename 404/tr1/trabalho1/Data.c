#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Data.h"

Data new_data(Info i,size_t s,func_free free_i, func_copy cpy, func_print p){
    Data d = malloc(sizeof(sData));
    d->info = i;
    d->size = s;
    d->del = free_i;
    d->copy = cpy;
    d->print = p;

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

    d = new_data(i, src->size, src->del, src->copy, src->print);

    return d;
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
