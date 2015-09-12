#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "List.h"
#include "Error.h"

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
void free_node(NoL *del){
    if((*del)->data)
        free_data(&(*del)->data);
    free(*del);
    *del = NULL;
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
    if(!r){
        return NULL;
    }
    if(r->dir)
        r->dir->esq = r->esq;
    if(r->esq)
        r->esq->dir = r->dir;
    r->esq = r->dir = r;
    return r;
}
bool remove_node(NoL n){
    NoL del = drop_node(n);
    if(!del){
        return false;
    }
    free_node(&del);
    return true;
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

void put_list_sorted(List l, Data d, bool inc){
    NoL n;
    short int factor = inc ? -1 : 1;
    for(
        n = list_get_first(l);
        !list_end(n) && ( (factor * comp_data(d, n->data) ) < 0);
        n = list_get_next(n)
    );
    insert_node(-1, new_node(false, d, NULL, NULL), n);
}


Data get_list(List l, int index){
    NoL n = get_relative_node(index, l->head);
    return n->data;
}

Data* get_vet(List l){
    unsigned int i = 0;
    NoL n, aux;
    Data* resp = malloc(l->size * sizeof(Data) );
    for_in(list, l, n, aux, true,
        resp[i++] = n->data;
    )
    return resp;
}
void free_list_aux(List * l, List top){
    NoL temp, n;
    for(
        temp = NULL, n = list_get_first((*l));
        !list_end(temp);
        temp = n, n = list_get_next(n)
    ){
        if(temp) {
            if(temp->data->dType != ___List){
                free_node(&temp);
            }else{
                if(*(List*)temp->data->info != top){
                    free_list_aux(&(*(List*)temp->data->info), top);
                }else{
                    *(List*)temp->data->info = NULL;
                }
            }
        }
    }
    free_node(&((*l)->head));
    free((*l));
    *l = NULL;

}
void free_list(List* l) {
    free_list_aux(l, *l);
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

bool is_in_list(List l, Data d){
    bool flag = false;
    NoL n, aux;
    for_in(list, l, n, aux, !flag,
        flag |= (eq_data(n->data, d) == 0);
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
    NoL n, aux;
    for_in(list, l, n, aux, !flag,
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
    NoL n, aux;
    for_in(list, src, n, aux, true,
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
    NoL n, aux;
    for_in(list, l, n, aux, true,
        if(!refine(n->data))
            remove_node(n);
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
void print_list_aux(List l, List top){
    NoL n, aux;
    List cmp;
    printf("[");
    if(l){
        for_in(list, l, n, aux, true,
            if(n->data->dType != ___List){
                print_data(n->data);
            }else {
                cmp = *(List*)(n->data->info);
                if(cmp != top){
                    print_list_aux(cmp, top);
                }else{
                    printf("[...]");
                }
            }

            printf(" ");
        )
    }
    printf("]");
}
void print_list(List l){
    print_list_aux(l, l);
    /*
    for (
        n = list_get_first(l);
        !list_end(n);
        n = list_get_next(n)
    ){
        if(*(List*)(n->data->info) != l){
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
    if(!list) return 0;
    return list->size;
}

Hash hash_list(List l){
    Hash resp = 523;
    NoL n, aux;

    for_in(list, l, n, aux, true,
        resp ^= h(n->data);
    )


    return resp;
}

Comp comp_list(List a, List b){
    NoL na, nb, auxa, auxb;
    Comp partial, resp = 0;
    bool equal = true;
    if(a == b){
        return 0;
    }else if(a && !b){
        return 1;
    }else if(!a && b){
        return -1;
    }else{
        for_in(list, a, na, auxa, true,
            for_in(list, b, nb, auxb, true,
                partial = comp_data(na->data, nb->data);
                equal &= (partial == 0);
                resp += partial;
            )
        )
    }
    return equal? 0 : resp != 0 ? resp : 1;
}




size_t ___List_size(Info i){
    return size_list(*(List*)i);
}
void ___List_print(Info i){
    print_list(*(List*)i);
}
void ___List_free(Info *i){
    free_list(&(*(List*)i));
    free(*i);
    *i = NULL;
}
Info ___List_copy(Info i){
    Info resp = malloc(sizeof(List));
    *(List*)resp = copy_list(*(List*)i);
    return resp;
}
Hash ___List_hash(Info i){
    return hash_list(*(List*)i);
}
Comp ___List_comp(Info a, Info b){
    return comp_list(*(List*)a , *(List*)b);
}
