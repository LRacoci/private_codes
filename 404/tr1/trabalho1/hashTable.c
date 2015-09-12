/* Nome: Lucas Alves Racoci
 * RA: 156331
 * Laboratório 10 - Hash */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"


/* Cria, aloca e inicializa uma nova tabela hash */
HashT new_HashT();
/* Remove e desaloca a tabela hash passada como argumento */
void free_HashT(HashT t);
/* Insere apropriadamente o struct strPair a na tabela t */
bool put_HashT(HashT t, StrPair a);
/* Consulta se o key em key está em t e devolve em a o strPair correspondente */
bool get_HashT(HashT t, String key, StrPair a);
/* Remove o strPair que tem o key em key */
bool drop_HashT(HashT t, String key);
/* Imprime de acordo com o enunciado */
void print_HashT(HashT t);
/* Devolve o numero de strPairs na tabela */
int size_HashT(HashT t);


/* Calcula o hash de uma string */
Hash hash(char* key){
	Hash i;
	/* Para garantir que o resultado seja positivo */
	unsigned char resp = 0;
	/* Acumula em resp o o resultaddo das operações xor bit a bit */
	for(i = 0; key[i]; i++){
		resp ^= key[i];
	}
	return (Hash)resp%TAM_TABELA;
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */
/*****************************************/
/****************************************/

/* TAD: Tabela Hash */
/*******************/

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
void free_HashT(HashT t){
	short unsigned int i;
	No temp, p;
	for(i = 0; i < TAM_TABELA; i++){
	p = t->l[i];
		while(p){
			temp = p;
			p = p->prox;
			free(temp->strP->key);
			free(temp->strP->val);
			free(temp->strP);
			free(temp);
		}
	}
	free(t);
}
StrPair copy_StrPair(StrPair src){
	SrcPair copy;
	if(!src) {
		return NULL;
	}
	copy = malloc(sizeof(sStrPair));
	copy->key = malloc((strlen(src->key) + 1) * sizeof(char));
	copy->key = malloc((strlen(src->key) + 1) * sizeof(char));
	strcpy(copy->key, src->key);
	strcpy(copy->val, src->val);
	return copy;


}
/* Insere na lista de índice calculado pelo hash em ordem lexicográfica */
bool put_HashT(HashT t, StrPair strPair){
	Hash h = hash(strPair->key);
	No nova, *aux = &(t->l[h]);

	/* Avança aux até achar a posição correta de inserir */
	while(*aux && strcmp((*aux)->strP->key, strPair->key) < 0){
		aux = &((*aux)->prox);
	}
	/* Verifica se esse key já está na Tabela */
	if(*aux && strcmp(strPair->key, (*aux)->strP->key) == 0){
		return false;
	}

	/* Insere na lista t->l[h] o strPair*/
	nova = malloc(sizeof(sNo));
	/* Copia o strPair */
	nova->strP = copy_StrPair(strPair);

	nova->prox = *aux;
	*aux = nova;

	t->size++;

	return true;
}
/* Retorna se o key está na tabela ou não e o strPair encontrado */
bool get_HashT(HashT t, String key, StrPair strPair){
	Hash h = hash(key);
	No ini = t->l[h], p = ini;
	while(p && strcmp(p->strP->key, key)){
		p = p->prox;
	}
	if(p == NULL){
		return false;
	}

	strPair = p->strP;
	return true;
}
/* Remove da lista de índice calculado pelo hash */
bool drop_HashT(HashT t, String key){
	Hash h = hash(key);
	No *p = &(t->l[h]), temp;
	
	if(!(*p)){
		return false;
	}
	/* Procura o key em key na lista de índice h */
	while(*p != NULL && strcmp((*p)->strP->key, key)){
		p = &((*p)->prox);
	}
	/* Se chegou ao final da lista e não achou nada, retorna falso */
	if(!(*p)){
		return false;
	}
	temp = *p;
	*p = (*p)->prox;
	free(temp->strP->key);
	free(temp->strP);
	free(temp);
	t->size--;
	return true;
}
/* Imprime a tabela conforme especificado no enunciado */
void print_HashT(HashT t){
	Hash i;
	No aux;
	for(i = 0; i < TAM_TABELA; i++){
		aux = t->l[i];
		while(aux){
			printf("(%d) %s \"%s\"\n", i, aux->strP->val, aux->strP->key);
			aux = aux->prox;
		}

	}
}

int size_HashT(HashT t){
	return t->size;
}
