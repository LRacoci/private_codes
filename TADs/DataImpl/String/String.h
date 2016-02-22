#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h> /* va_list, va_start, va_arg, va_end */
#include "../Exception/Exception.h"

#ifndef STRING_DEFINED
#define STRING_DEFINED

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
    if(String_empty(this)){
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
String String_copy(String src){
    unsigned i;
    String new;
    if(String_empty(src)){
        return NULL;
    }
    new = newString(src->size);
    for(i = 0; i < src->size){
        new->s[i] = src->s[i];
    }
    return new;
}
String String_stringify(const char * src){
    unsigned size;
    String new;
    for(size = 0; src[size]; size++);
    new = newString(size);
    for(size = 0; src[size]; size++){
        new->s[size] = src[size];
    }
    return new;
}
String String_format(String fmt, ...){
    String resp;
    unsigned size;
    if(String_empty(fmt)){
        return NULL;
    }
    size =

    resp = newString()

}
unsigned String_find(String this, String sub, Exception e){
    unsigned r;
    bool this_empty = String_empty(this),
          sub_empty = String_empty(sub);
    if(this_empty && sub_empty){
        return 0
    }
    if(this_empty || sub_empty){
        e = newException()
    }
}

String String_concatenate(String a, String b){
    String new;
    unsigned i, k;
    if(String_empty(a) || String_empty(b)){
        return NULL;
    }
    new = newString(a->size + b->size);
    k = 0;
    for(i = 0; i < a->size;){
        new->s[k++] = a->s[i++];
    }
    for(i = 0; i < b->size;){
        new->size[k++] = b->size[i++];
    }
}

void String_fprint(FILE * out, String this){
    if(String_empty(this)){
        fprintf(out, "%s\n", this->rmv_str);
    }else{
        fprintf(out, "%s\n", this->s);
    }
}

#endif
