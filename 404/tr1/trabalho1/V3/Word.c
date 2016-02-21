#include "Word.h"

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

 String fgetword(FILE * src, unsigned int * lines, bool * ok){
    String resp;
    unsigned int tam = 0;
    int c = !EOF;
    fpos_t pos;
    *ok = true;
    /* Ignora caracteres inúteis e comentarios*/
    for(
        c = fgetc(src);
        c != EOF && char_in_string(c, " #\t\n\r");
        c = fgetc(src)
    ){
        /* Verifica se eh comentário */
        if(c == '#'){
            /* Ignora comentário */
            for(
                c = fgetc(src);
                c != EOF && !char_in_string(c, "\n\r");
                c = fgetc(src)
            );
        }
        /* Conta quebras de linha */
        if(char_in_string(c, "\n\r")){
            (*lines)++;
        }
    }
    ungetc(c, src);
    /* Salva o começo da palavra */
    fgetpos(src, &pos);
    /* Conta quantos caracteres tem a palabra */
    for(
        tam = 0;
        c != EOF && !char_in_string(c, " #\t\n\r");
        c = fgetc(src), tam++
    );
    /* Caso o arquivo já esteja no final, nada é alocado */
    if(tam == 0){
        *lines = -1;
        *ok = false;
        return NULL;
    }

    tam += 1;
    /* Volta o arquivo ao começo da palavra */
    fsetpos(src, &pos);

    resp = malloc(tam*sizeof(char));
    fscanf(src, "%s", resp);
    return resp;
}

String get_part_string(String src, int ini, int fim){
    unsigned int size = strlen(src);
    String resp = malloc(size*sizeof(char));
    resp = &(resp[ini % size]);
    resp[fim % size] = '\0';
    return resp;
}
