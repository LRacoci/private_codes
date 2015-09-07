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
    List l;
    Data d[10];
    int v[] = {9, 5, 2, 4, 7, 1, 3, 6, 10, 8};
    int i;
    l = new_list();
    for(i = 0; i < 10; i++){
        d[i] = new(v[i], int);

        put_list_sorted(l, d[i], true);

        print_list(l);
    }

    prepend_list(l, new(l, List));

    print_list(l);

    free_list(l);

    return 0;
}
