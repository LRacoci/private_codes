#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Data.h"
#include "List.h"


void mop_exaple(Data d){
    *(int*) d->info *= 47;
}


short int __int_comp(Info a, Info b){
    return *(int*)a == *(int*)b ? 0 : *(int*)a > *(int*)b ? 1 : -1;
}

int main(){
    List l1, l2;
    Data d[10], dl;
    int v[] = {9, 5, 2, 4, 7, 1, 3, 6, 10, 8};
    int i;
    l = new_list();
    for(i = 0; i < 5; i++){
        d[i] = new(v[i], int);

        put_list_sorted(l, d[i], true);

        print_list(l);
    }
    dl = new_data(
        &l,
        ___List_size(&(l)),
        ___List_free,
        ___List_copy,
        ___List_print,
        ___List_hash,
        ___List_comp
    );
    prepend_list(l, dl);

    print_list(l);

    free_list(l);

    return 0;
}
