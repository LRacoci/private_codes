#include <stdio.h>
#include "../../Helpers/Debug/Debug.h"
#include "../String.h"

#ifndef EXCEPTION_DEFINED
#define EXCEPTION_DEFINED


typedef struct sExcept{
    bool isError;
    String msg;
} sException, *Excpetion;

#define Exception_empty(e) (!e)

Exception newException(const String msg){
    Exception new = malloc(sizeof(sException));
    new->msg = String_copy(msg);
    return new;
}
void freeException(Exception rmv){
    if()
}

#endif
