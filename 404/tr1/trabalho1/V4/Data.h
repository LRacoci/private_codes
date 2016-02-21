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
    ___LongInt,
    ___OutLine,
    ___String,
    ___HashVal
} DataType;

#define numcmp(a, b) (((a) == (b)) ? 0 : ((a) < (b))? -1 : 1)

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

#define HeadDefinition(staticType) \
    size_t ___ ## staticType ## _size(Info i);\
    void ___ ## staticType ## _print(Info i);\
    void ___ ## staticType ## _free(Info * i);\
    Info ___ ## staticType ## _copy(Info i);\
    Hash ___ ## staticType ## _hash(Info i);\
    Comp ___ ## staticType ## _comp(Info a, Info b)

#define val(i) *(staticType*)(i)
#define BodyDefinition(staticType, ...) \
    size_t ___ ## staticType ## _size(Info i){ \
        return sizeof(staticType); \
    } \
    void ___ ## staticType ## _print(Info i){ \
        staticType st = *(staticType*)(i); \
        printf(__VA_ARGS__); \
    } \
    void ___ ## staticType ## _free(Info *i){ \
        free(*i); \
        *i = NULL; \
    } \
    Info ___ ## staticType ## _copy(Info i){ \
        Info resp = malloc(___ ## staticType ## _size(i)); \
        *(staticType*)resp = *(staticType*)i; \
        return resp; \
    } \
    Hash ___ ## staticType ## _hash(Info i){ \
        return (Hash)*(staticType*)(i); \
    } \
    Comp ___ ## staticType ## _comp(Info a, Info b){ \
        return *(staticType*)a == *(staticType*)b ? 0: *(staticType*)a > *(staticType*)b ? 1 : -1; \
    }


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

size_t ___String_size(Info i);
void ___String_print(Info i);
void ___String_free(pInfo i);
Info ___String_copy(Info i);
Hash ___String_hash(Info i);
Comp ___String_comp(Info a, Info b);

HeadDefinition(int);
HeadDefinition(LongInt);


#endif
