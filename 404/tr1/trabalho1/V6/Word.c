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
            cfprintf(stdout, 93, "%c", c); /* Debuging5 */
            /* Ignora comentário */
            for(
                c = fgetc(src);
                c != EOF && !char_in_string(c, "\n\r");
                c = fgetc(src)
            ){
                cfprintf(stdout, 96, "%c", c); /* Debuging5 */
            }
        }
        /* Conta quebras de linha */
        if(char_in_string(c, "\n")){
            if(lines){
                (*lines)++;
                cfprintf(stdout, 94, "[\\%c(%d)]%c", c=='\r'? 'r':'n', *lines, c); /* Debuging5 */
            }
        }
        else{
            cfprintf(stdout, 97, "%c", c); /* Debuging5 */
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

String get_part_string(String src, int ini, int fim){
    unsigned int size = strlen(src);
    String resp = malloc(size*sizeof(char));
    resp = &(resp[ini % size]);
    resp[fim % size] = '\0';
    return resp;
}
