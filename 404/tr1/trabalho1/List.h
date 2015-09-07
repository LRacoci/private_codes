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

#define  append_list(list, data)   put_node_list(list,  1, data)
#define prepend_list(list, data)   put_node_list(list, -1, data)
#define     map_list(list, function)   mod_list(copy_list(list), function)
#define  filter_list(list, function) clean_list(copy_list(list), function)


NoL new_node(bool head, Data dat, NoL e, NoL d);
void free_node(NoL del);
NoL get_relative_node(int relative_index, NoL axis);
void insert_node(int relative_index, NoL new, NoL node);

NoL drop_list(List l, int index);
NoL copy_node(NoL l, func_copy_data copy);

List new_list();

void put_node_list(List l, int index, NoL new);
NoL get_node_list(List l, int index);

void put_list(List l, int index, Data d);
void put_list_sorted(List l, Data d, func_comp infocmp, bool inc);
Data get_list(List l, int index);

void free_list(List l);

NoL list_get_first(List l);
NoL list_get_next(NoL n);
bool list_end(NoL n);

List copy_list(List src);

void mod_list(List l, func_mod mod);
void clean_list(List l, func_filter filter);

void print_list(List l);
unsigned int size_list(List list);
#endif
