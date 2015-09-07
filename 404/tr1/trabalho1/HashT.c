#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "List.h"
#include "Error.h"
#include "HashT.h"

HashT new_table(unsigned int size0){
    HashT new = malloc(sizeof(sHashT));
    new->s0 = size0;
    new->t = malloc(size0 * sizeof(sList));
    memset(new->t, 0, size0 * sizeof(sList));

    return new;
}
void free_table(HashT del){
    unsigned int i;
    for (i = 0; i < del->s0; i++){
        if(del->t[i]){
            free(del->t[i]);
        }
    }
    free(del);
}
bool is_in_table(HashT this, Data d){
    List p = this->t[h(d)%(this->s0)];
    if(!p){
        return false;
    }
    return is_in_list(p, d);
}
void put_in_table(HashT this, Data key, Data value){
    Data pair;
    List l, p = new_list();
    append_list(p, key);
    append_list(p, value);
    pair = new(p, List);
    l = this->t[h(pair)%(this->s0)];
    append_list(l, pair);

}
