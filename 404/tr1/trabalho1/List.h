#include "Data.h"
#include "auxTypes.h"
#ifndef LIST_DEFINED
#define LIST_DEFINED

typedef Data (*func_copy_data)(Data );
typedef void (*func_mod)(Data );
typedef bool (*func_filter)(Data );

typedef struct sN{
    bool head;
    Data data;
    struct sN *esq, *dir;
}sNoL, *NoL;

typedef struct l{
    unsigned int size;
    NoL head;
} sList, *List;

#define for_in(type, list, iterator, aux, while_flag, \
    code \
) \
{ \
    for ( \
        (aux) = NULL, iterator = type ## _get_first(list); \
        ! (type ## _end(iterator)) && (while_flag); \
        (aux) = (iterator), iterator = type ## _get_next(iterator)\
    ){ \
        if((aux) && !((aux)->data)){ \
            remove_node(aux); \
        } \
        code \
    } \
}

#define  append_list(list, data)   put_list(list, -1, data)
#define prepend_list(list, data)   put_list(list,  0, data)
#define     map_list(list, function)   mod_list(copy_list(list), function)
#define  filter_list(list, function) refine_list(copy_list(list), function)




NoL new_node(bool head, Data dat, NoL e, NoL d);
void free_node(NoL* del);
NoL get_relative_node(int relative_index, NoL axis);
void insert_node(int relative_index, NoL new, NoL node);

NoL drop_list(List l, int index);
NoL copy_node(NoL l, func_copy_data copy);

List new_list();

void put_node_list(List l, int index, NoL new);
NoL get_node_list(List l, int index);

void put_list(List l, int index, Data d);
void put_list_sorted(List l, Data d, bool inc);
Data get_list(List l, int index);

void free_list(List * l);

NoL list_get_first(List l);
NoL list_get_next(NoL n);
bool list_end(NoL n);

List copy_list(List src);

bool is_in_list(List l, Data d);
bool for_in_list(List l, func_filter);

void mod_list(List l, func_mod mod);
void refine_list(List l, func_filter filter);

void print_list(List l);
unsigned int size_list(List list);

Hash hash_list(List l);




size_t ___List_size(Info i);
void ___List_print(Info i);
void ___List_free(Info * i);
Info ___List_copy(Info i);
Hash ___List_hash(Info i);
Comp ___List_comp(Info a, Info b);

#endif
