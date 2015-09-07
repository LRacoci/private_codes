#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Data.h"
#include "List.h"

void __int_print(Info i){
    printf("%8d", *(int*)(i));
}
void __int_free(Info i){
    free(i);
}
Info __int_copy(Info i){
    Info resp = malloc(sizeof(int));
    *(int*)resp = *(int*)i;
    return resp;
}
void __List_print(Data d){
    print_list(d->info);
}
void __List_free(Info i){
    free_list(i);
}
Info __List_copy(Info i){
    return copy_list(i);
}
void mop_exaple(Data d){
    *(int*) d->info *= 47;
}
#define new(v, type) new_data( \
    __ ## type ## _copy(&(v)), \
    sizeof(type), \
    __ ## type ## _free, \
    __ ## type ## _copy, \
    __ ## type ## _print \
);

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

        put_list_sorted(l, d[i], __int_comp, true);

        print_list(l);
    }

    print_list(l);

    free_list(l);

    return 0;
}
