#include "auxTypes.h"
#ifndef DATA_DEFINED
#define DATA_DEFINED

typedef void * Info;

typedef void (*func_free)(Info );
typedef Info (*func_copy)(Info );
typedef short int (*func_comp)(Info , Info );
typedef void (*func_print)(Info );
typedef Hash (*func_hash)(Info );

#define new(v, type) new_data( \
    __ ## type ## _copy(&(v)), \
    sizeof(type), \
    __ ## type ## _free, \
    __ ## type ## _copy, \
    __ ## type ## _print, \
    __ ## type ## _hash \
);


typedef struct sD{
    Info info;
    size_t size;
    func_free del;
    func_copy copy;
    func_print print;
    func_hash hash;
}sData, *Data;


Data new_data(
    Info i, size_t s,
    func_free free_i,
    func_copy cp,
    func_print p,
    func_hash h
);
Data copy_data(Data src);
void free_data(Data d);
Info get_info_data(Data d);
Hash h(Data d);
short int comp_data(Data a, Data b, func_comp infocmp);
void print_data(Data d);

void __int_print(Info i);
void __int_free(Info i);
Info __int_copy(Info i);
Hash __int_hash(Info i);

void __String_print(Info i);
void __String_free(Info i);
Info __String_copy(Info i);
Hash __String_hash(Info i);

void __List_print(Data d);
void __List_free(Info i);
Info __List_copy(Info i);
Hash __List_hash(Info i);



#endif
