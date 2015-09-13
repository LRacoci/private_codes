#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auxTypes.h"
#include "iasDefs.h"
#include "genericDefs.h"
#include "Error.h"
#include "Data.h"





bool char_in_string(char target, String s){
    if(s == NULL){
        return false;
    }
    if(target == '\0'){
        return true;
    }
    for(; *s; s++){
        if(target == *s){
            return true;
        }
    }
    return false;
}
bool element_of(
    String e,
    char vet[][MAX_INSTR],
    func_comp cmp,
    unsigned int size
){
    unsigned int i;
    if(vet == NULL || size == 0){
        return false;
    }if(e == NULL){
        return true;
    }
    for(i = 0; i < size; i++){
        if(cmp(e, vet[size]) == 0){
            return true;
        }
    }
    return false;
}

unsigned int fgetword(FILE * src, String * str){
    unsigned int resp = 0;
    int c = !EOF;
    bool comentario = false;
    *str = malloc(128*sizeof(char));
    for(c = fgetc(src); c != EOF; c = fgetc(src)){
        if(!char_in_string(c, " #\t\n") && !comentario){
            ungetc(c, src);
            fscanf(src, "%s", *str );
            return resp;
        }else if(c == '\n'){
            resp++;
            comentario = false;
        }else if(c == '#'){
            comentario = true;
        }
    }
    return c == EOF ? -1 : resp;
}

String get_part_string(String src, int ini, int fim){
    unsigned int size = strlen(src);
    String resp = malloc(size*sizeof(char));
    resp = &(resp[ini % size]);
    resp[fim % size] = '\0';
    return resp;
}
