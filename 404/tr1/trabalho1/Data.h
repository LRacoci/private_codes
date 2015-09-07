#include "auxTypes.h"
#ifndef DATA_DEFINED
#define DATA_DEFINED

typedef void * Info;
typedef void (*func_free)(Info );
typedef Info (*func_copy)(Info );
typedef Comp (*func_comp)(Info , Info );
typedef void (*func_print)(Info );
typedef Hash (*func_hash)(Info );

#define new(v, type) new_data( \
    ___ ## type ## _copy(&(v)), \
    ___ ## type ## _size(&(v)), \
    ___ ## type ## _free, \
    ___ ## type ## _copy, \
    ___ ## type ## _print, \
    ___ ## type ## _hash, \
    ___ ## type ## _comp \
);


typedef struct sD{
    Info info;
    size_t size;
    func_free del;
    func_copy copy;
    func_print print;
    func_hash hash;
    func_comp cmp;
}sData, *Data;


Data new_data(
    Info i, size_t s,
    func_free free_i,
    func_copy cp,
    func_print p,
    func_hash h,
    func_comp compare
);
Data copy_data(Data src);
void free_data(Data d);
Info get_info_data(Data d);
Hash h(Data d);
Comp comp_data(Data a, Data b);
bool eq_data(Data a, Data b);
void print_data(Data d);

size_t ___int_size(Info i);
void ___int_print(Info i);
void ___int_free(Info i);
Info ___int_copy(Info i);
Hash ___int_hash(Info i);
Comp ___int_comp(Info a, Info b);

size_t ___String_size(Info i);
void ___String_print(Info i);
void ___String_free(Info i);
Info ___String_copy(Info i);
Hash ___String_hash(Info i);
Comp ___String_comp(Info a, Info b);



#endif
