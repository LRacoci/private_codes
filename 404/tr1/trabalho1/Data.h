#ifndef DATA_DEFINED
#define DATA_DEFINED

typedef void * Info;

typedef void (*func_free)(Info );
typedef Info (*func_copy)(Info );
typedef short int (*func_comp)(Info , Info );
typedef void (*func_print)(Info );




typedef struct sD{
    Info info;
    size_t size;
    func_free del;
    func_copy copy;
    func_print print;
}sData, *Data;


Data new_data(Info i, size_t s, func_free free_i, func_copy cp, func_print p);
Data copy_data(Data src);
void free_data(Data d);
Info get_info_data(Data d);
short int comp_data(Data a, Data b, func_comp infocmp);
void print_data(Data d);


#endif
