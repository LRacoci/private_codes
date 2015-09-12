#include "auxTypes.h"
#ifndef DATA_DEFINED
#define DATA_DEFINED

typedef void * Info, **pInfo;
typedef void (*func_free)(pInfo );
typedef Info (*func_copy)(Info );
typedef Comp (*func_comp)(Info , Info );
typedef void (*func_print)(Info );
typedef Hash (*func_hash)(Info );

typedef enum DataType{
    ___List,
    ___int,
    ___String
} DataType;

/* Example with type = List and v = l:
new_data(
    ___List_copy(&(l)),
    ___List_size(&(l)),
    ___List_free,
    ___List_copy,
    ___List_print,
    ___List_hash,
    ___List_comp,
    ___List
)
*/
#define new(v, type) new_data( \
    ___ ## type ## _copy(&(v)), \
    ___ ## type ## _size(&(v)), \
    ___ ## type ## _free, \
    ___ ## type ## _copy, \
    ___ ## type ## _print, \
    ___ ## type ## _hash, \
    ___ ## type ## _comp, \
    ___ ## type \
)

#define comp_info(arg1 , arg2 , size) memcmp( \
    (const Info) (arg1), \
    (const Info) (arg2), \
    (size) \
)

typedef struct sD{
    Info info;
    size_t size;
    func_free del;
    func_copy copy;
    func_print print;
    func_hash hash;
    func_comp cmp;
    DataType dType;
}sData, *Data, **pData;


Data new_data(
    Info i, size_t s,
    func_free free_i,
    func_copy cp,
    func_print p,
    func_hash h,
    func_comp compare,
    DataType dT
);
Data copy_data(Data src);
void free_data(Data* d);
Info get_info_data(Data d);
Hash h(Data d);
Comp comp_data(Data a, Data b);
bool eq_data(Data a, Data b);
void print_data(Data d);

size_t ___int_size(Info i);
void ___int_print(Info i);
void ___int_free(pInfo i);
Info ___int_copy(Info i);
Hash ___int_hash(Info i);
Comp ___int_comp(Info a, Info b);

size_t ___String_size(Info i);
void ___String_print(Info i);
void ___String_free(pInfo i);
Info ___String_copy(Info i);
Hash ___String_hash(Info i);
Comp ___String_comp(Info a, Info b);



#endif
