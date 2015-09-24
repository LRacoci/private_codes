#include "Word.h"

/* Verifica se o caracter target esta na string s */
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
/* Copia uma palavra */
String copy_word(String src, unsigned int * len_resp){
    unsigned int j, len = 0;
    String copy;

    if(!src){
        if(len_resp) *len_resp = 0;
        return NULL;
    }
    for(len = 0; src[len]; len++);
    len++;
    copy = malloc(len*sizeof(char));
    /* Copia o argumento original pra uma string copy*/
    for(j = 0; j < len; j++){
        copy[j] = src[j];
    }
    if(len_resp) *len_resp = len;
    return copy;
}
/* Extrai alguma parte de uma string */
bool filter_Word(String src, const String f){
    String resp;
    unsigned int i, j, len_resp;
    if(!src){
        return false;
    }
    len_resp = 1;
    for(i = 0; f[i]; i++){
        if(f[i] == '%' && f[i+1] == 's'){
            for(j = i; src[j] != f[i+2]; j++){
                len_resp++;
            }
            i++;
        }
    }
    resp = malloc(sizeof(char)*(len_resp));
    resp[len_resp-1] = '\0';

    len_resp = 0;
    for(i = 0; f[i]; i++){
        if(f[i] == '%' && f[i+1] == 's'){
            for(j = i; src[j] != f[i+2]; j++){
                resp[len_resp++] = src[j];
            }
            i++;
        }
    }
    strcpy(src, resp);
    free(resp);
    return true;
}
/* Retorna uma palavra para o arquivo em src */
bool ungetword(FILE * src, String str){
    unsigned int i, len = strlen(str);
    for(i = len - 1; i >= 0; i--){
        if(ungetc(str[i], src) == EOF){
            return false;
        }
    }
    return true;
}

/* Le a proxima palavra do arquivo de entrada e retorna o
 * numero de quebras de linha em lines */
String fgetword(FILE * src, unsigned int * lines, bool * ok){
    String resp;
    unsigned int tam = 0;
    int c = !EOF;
    fpos_t pos;
    *ok = true;
    *lines = 0;
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
            ){
            }
        }
        /* Conta quebras de linha */
        if(char_in_string(c, "\n")){
            if(lines){
                (*lines)++;
            }
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
        if(lines){
            *lines = -1;
        }
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
