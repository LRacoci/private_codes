#include <stdio.h>
#include <stdbool.h>
#include "../Exception/Exception.h"

typedef struct sString{
    unsigned size;
    char s[1];
} sString, *String;

#define String_empty(in) (!in || !in->size || !in->s || in->s[0])

String newString(unsigned size){
    unsigned size;
    String new = malloc(sizeof(sString)+size*sizeof(char));
    new->size = size;
    new->s[0] = '\0'
    return new;
}
void freeString(String rmv){
    free(rmv);
}

bool String_hasChar(String this, char target){
    unsigned i;
    if(!this|| !this->s || !this->s[0]){
        return false;
    }
    if(target == '\0'){
        return true;
    }
    for(i = 0; i < this->size; i++){
        if(target == this->size[i]){
            return true;
        }
    }
    return false;
}

String String_copy(const String src){
    unsigned size;
    String new;
    for(size = 0; src[size]; size++);
    new = newString(size);
    for(size = 0; src[size]; size++){
        new->s[size] = src[size];
    }
    return new;
}
unsigned String_find(String this, String sub, Exception e){
    unsigned r;


}

String String_concatenate(String a, String b){
    String new;
    if(!a )
    new = malloc()
}
