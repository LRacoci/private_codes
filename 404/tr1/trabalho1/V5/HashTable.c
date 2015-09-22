/* Nome: Lucas Alves Racoci
 * RA: 156331
 * Laboratório 10 - Hash */

#include "HashTable.h"

/* Calcula o hash de uma Data */
Hash hash(String key){
	unsigned int j;
    Hash h = 5381;
    int c;
    for(h = 5381, j = 0; key[j]; j++){
        c = key[j];
        h = ((h << 5) + h) + c;

    }
	return (Hash)h%TAM_TABELA;
}

/* Cria vetor de listas e inicializa todas as posições com NULL */
HashT new_HashT(){
	unsigned short int i;
	HashT neo = malloc(sizeof(sHashT));
	for(i = 0; i < TAM_TABELA; i++){
		neo->l[i] = NULL;
	}
	neo->size = 0;
	return neo;
}
/* Libera todos os possíveis campos alocados pra uma tabela */
void free_HashT(HashT *t){
	short unsigned int i;
	Lista temp, p;
	for(i = 0; i < TAM_TABELA; i++){
		p = (*t)->l[i];
		while(p){
			temp = p;
			p = p->prox;
			if(p->k){
				free(p->k);
			}
			free(temp);
		}
	}
	free(*t);
	*t = NULL;
}

/* Insere na lista de índice calculado pelo hash */
bool put_HashT(HashT t, String key, unsigned long long int v, char c){
	Hash h = hash(key);
	Lista nova, *aux = &(t->l[h]);

	/* Avança aux até achar a posição correta de inserir */
	while(*aux && strcmp(key, (*aux)->k) < 0){
		aux = &((*aux)->prox);
	}
	/* Verifica se esse key já está na Tabela */
	if(*aux && strcmp(key, (*aux)->k) == 0){
		return false;
	}

	/* Insere na lista t->l[h] o no*/
	nova = malloc(sizeof(No));
	/* Copia o no */
	strcpy(nova->k, key);
	nova->v = v;
	nova->t = c;

	nova->prox = *aux;
	*aux = nova;

	t->size++;

	return true;
}
bool is_in_HashT(HashT t, String key, char * c){
	unsigned long long int lixo;
	return get_HashT(t, key, &lixo, c);
}

/* Retorna se o key está na tabela ou não e o no encontrado */
bool get_HashT(HashT t, String key, unsigned long long int * v, char *c){
	Hash h = hash(key);
	Lista ini = t->l[h], p = ini;
	while(p && strcmp(key, p->k)){
		p = p->prox;
	}
	if(p == NULL){
		return false;
	}
	*v = p->v;
	*c = p->t;
	return true;
}
/* Remove da lista de índice calculado pelo hash */
bool drop_Data_HashT(HashT t, String key){
	Hash h = hash(key);
	Lista *p = &(t->l[h]), temp;

	if(!(*p)){
		return false;
	}
	/* Procura o key em key na lista de índice h */
	while(*p != NULL && strcmp((*p)->k, key)){
		p = &((*p)->prox);
	}
	/* Se chegou ao final da lista e não achou nada, retorna falso */
	if(!(*p)){
		return false;
	}
	temp = *p;
	*p = (*p)->prox;
	free(temp);
	t->size--;
	return true;
}
/* Imprime a tabela conforme melhor pra depurar */
void print_HashT(HashT t){
	unsigned int i;
	unsigned long long int v;
	char c;
	Lista aux;
	String k;
	for(i = 0; i < TAM_TABELA; i++){
		for(aux = t->l[i]; aux; aux = aux->prox){
			k = aux->k;
			v = aux->v;
			c = aux->t;
			cfprintf(stdout, 94, "(%02u) ", i);
			cfprintf(stdout, 93, "%s", k);
			cfprintf(stdout, 96, "(%c)", c);
			cfprintf(stdout, 97, " \"");
			if(c == 'L'){
				cfprintf(
					stdout, 99 ,
					"%03llX[%c]",
					v/2,
					v%2?'d':'e'
				);
			}else if(c == 'S'){
				cfprintf(
					stdout, 99 ,
					"%03lld",
					v
				);
			}else if(c == 'I'){
				cfprintf(
					stdout, 99 ,
					"%02llX",
					v
				);
			}

			cfprintf(stdout, 97 ,"\"");
			printf("\n");

		}

	}
}

int size_HashT(HashT t){
	return t->size;
}
