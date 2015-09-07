#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "List.h"
#include "Error.h"

#ifndef min
#define min(x, y) ((x < y) ? (x) : (y))
#endif

#ifndef sign
#define sign(x) ((x >= 0) ? (1) : (-1))
#endif

#ifndef abs
#define abs(x) ( sign(x) * x)
#endif


NoL new_node(bool head, Data dat, NoL e, NoL d){
    NoL r = malloc(sizeof(sNoL));
    r->head = head;
    r->data = dat;
    r->esq  = e;
    r->dir  = d;
    if(head){
        r->esq = r->dir = r;
    }
    return r;
}
void free_node(NoL del){
    if(del->data)
        free_data(del->data);
    free(del);
}
NoL get_relative_node(int relative_index, NoL axis){
    int i;
    NoL n;
    if(relative_index >= 0){
        for(
            i = 0, n = axis;
            i < relative_index;
            i++, n = n->dir
        );
    }else{
        for(
            i = 0, n = axis;
            i > relative_index;
            i--, n = n->esq
        );
    }
    return n;
}
void insert_node(int relative_index, NoL new, NoL node){
    NoL n = get_relative_node(relative_index, node);
    new->dir = n->dir;
    new->esq = n;
    new->dir->esq = new->esq->dir = new;

}
NoL drop_node(NoL r){
    if(r->dir)
        r->dir->esq = r->esq;
    if(r->esq)
        r->esq->dir = r->dir;
    r->esq = r->dir = r;
    return r;
}

NoL drop_list(List l, int index){
    NoL r = get_node_list(l, index);
    drop_node(r);
    l->size--;
    return r;
}
NoL copy_node(NoL l, func_copy_data copy){
    return new_node(l->head, copy(l->data), l->esq, l->dir);
}

List new_list(){
    List  new = malloc(sizeof(sList));
    new->size = 0;
    new->head = new_node(true, NULL, NULL, NULL);
    return new;
}

void put_node_list(List l, int index, NoL new){
    if(!l){
        l = new_list();
    }
    insert_node(index, new, l->head);
    l->size++;
}

NoL get_node_list(List l, int index){
    return get_relative_node(index, l->head);
}

void switch_node_list(List l, NoL a, NoL b){
    NoL aux;
    a->dir->esq = a->esq->dir = b;
    b->dir->esq = b->esq->dir = a;
    aux = a->dir; a->dir = b->dir; b->dir = aux;
    aux = a->esq; a->esq = b->esq; b->esq = aux;

}

void put_list(List l, int index, Data d){
    put_node_list(l, index, new_node(false, d, NULL, NULL));
}

void put_list_sorted(List l, Data d, func_comp infocmp, bool inc){
    NoL n;
    short int factor = inc ? -1 : 1;
    for(
        n = list_get_first(l);
        !list_end(n) && ( (factor * comp_data(d, n->data, infocmp) ) < 0);
        n = list_get_next(n)
    );
    insert_node(-1, new_node(false, d, NULL, NULL), n);
}


Data get_list(List l, int index){
    NoL n = get_relative_node(index, l->head);
    return n->data;
}

void free_list(List l) {
    NoL temp, n;
    for(
        temp = NULL, n = list_get_first(l);
        n != l->head || !list_end(n);
        temp = n, n = list_get_next(n)
    ){
        if(temp) free_node(temp);
    }
    free_node(l->head);
    free(l);
}
NoL list_get_first(List l){
    return l->head->dir;
}
NoL list_get_next(NoL n){
    return n->dir;
}
bool list_end(NoL n){
    return n->head;
}

List copy_list(List src){
    List resp = new_list();
    NoL n;

    for (
        n = list_get_first(src);
        !list_end(n);
        n = list_get_next(n)
    ){
        insert_node(-1, copy_node(n, copy_data), resp->head);
    }
    return resp;
}

bool is_in_list(List l, Data d, func_comp infocmp){
    NoL n;
    bool flag = false;
    for_in(l, n, !flag,
        flag |= (data_comp(n->data, d) == 0);
    )
    /*
    for (
        n = list_get_first(l);
        !list_end(n) && !flag;
        n = list_get_next(n)
    ){
        flag |= data_comp(n->data, d) == 0;
    }
    */
    return flag;
}

bool for_in_list(List l, func_filter have_propertie){
    bool flag = false;

    NoL n;
    for_in(l, n, !flag,
        flag |= have_propertie(n->data);
    )
    /*
    for (
        n = list_get_first(l);
        !list_end(n) && !flag;
        n = list_get_next(n)
    ){
        flag |= have_propertie(n->data);
    }
    */
    return flag;
}

void mod_list(List src, func_mod mod){

    for_in(src, n, true,
        mod(n->data);
    )
    /*
    for (
        n = list_get_first(src);
        !list_end(n);
        n = list_get_next(n)
    ){
        mod(n->data);
    }
    */
}
void refine_list(List l, func_filter refine){
    NoL n;
    for_in(l, n, true,
        if(!refine(n->data))
            free_node(drop_node(n));
    )
    /*
    for (
        n = list_get_first(l);
        !list_end(n);
        n = list_get_next(n)
    ){
        if(!refine(n->data))
            free_node(drop_node(n));
    }
    */
}
void print_list(List l){
    NoL n;
    for_in(l, n, true,
        if(n->data->info != l){
            print_data(n->data);
        }else{
            printf("[...]");
        }
        printf(" ");
    )
    /*
    for (
        n = list_get_first(l);
        !list_end(n);
        n = list_get_next(n)
    ){
        if(n->data->info != l){
            print_data(n->data);
        }else{
            printf("[...]");
        }
        printf(" ");
    }
    */
    printf("\n");
}
unsigned int size_list(List list) {
    return list->size;
}

Hash hash_list(List l){
    Hash resp = 523

    for_in(l, rt, true,
        resp ^= data_hash(rt->data);
    )


    return resp;
}
