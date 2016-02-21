/* Nome: Lucas Alves Racoci
 * RA: 156331
 * Laboratório 10 - Hash */

#include "HashTable.h"


/* Calcula o hash de uma KeyType */
Hash hash(KeyType key){
	/*unsigned int i;*/
	/* Para garantir que o resultado seja positivo */
	Hash resp = h(key);
	/* Acumula em resp o o resultaddo das operações xor bit a bit */
	/*
	for(i = 0; key[i]; i++){
		resp ^= key[i];
	}
	*/
	return (Hash)resp%TAM_TABELA;
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */
/*****************************************/
/****************************************/


KVPair new_KVPair(KeyType a, ValType b){
	KVPair neo = malloc(sizeof(sKVPair));
	neo->key = a;
	neo->val = b;
	return neo;
}

KVPair copy_KVPair(KVPair src){
	KVPair copy;
	if(!src) {
		return NULL;
	}
	copy = malloc(sizeof(sKVPair));
	copy->key = copy_data(src->key);
	copy->val = copy_data(src->val);
	return copy;


}
bool free_KVPair(KVPair *del){
	if(!(*del)) return false;
	free_data(&(*del)->key);
	free_data(&(*del)->val);
	free(*del);
	*del = NULL;
	return true;
}
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
void free_HashT(HashT *t){
	short unsigned int i;
	Lista temp, p;
	for(i = 0; i < TAM_TABELA; i++){
	p = (*t)->l[i];
		while(p){
			temp = p;
			p = p->prox;
			free_KVPair(&(temp->kvP));
			free(temp);
		}
	}
	free(*t);
	*t = NULL;
}

/* Insere na lista de índice calculado pelo hash */
bool put_KVPair_HashT(HashT t, KVPair kvPair){
	Hash h = hash(kvPair->key);
	Lista nova, *aux = &(t->l[h]);

	/* Avança aux até achar a posição correta de inserir */
	while(*aux && comp_data((*aux)->kvP->key, kvPair->key) < 0){
		aux = &((*aux)->prox);
	}
	/* Verifica se esse key já está na Tabela */
	if(*aux && comp_data(kvPair->key, (*aux)->kvP->key) == 0){
		return false;
	}

	/* Insere na lista t->l[h] o kvPair*/
	nova = malloc(sizeof(Lista));
	/* Copia o kvPair */
	nova->kvP = kvPair;

	nova->prox = *aux;
	*aux = nova;

	t->size++;

	return true;
}
bool put_HashT(HashT t, KeyType k, ValType v){
	return put_KVPair_HashT(t, new_KVPair(k, v));
}
bool put_copy_HashT(HashT t, KeyType k, ValType v){
	return put_KVPair_HashT(t, copy_KVPair(new_KVPair(k, v)));
}
bool is_in_HashT(HashT t, KeyType key){
	KVPair lixo = NULL;
	return get_HashT(t, key, lixo);
}
/* Retorna se o key está na tabela ou não e o kvPair encontrado */
bool get_HashT(HashT t, KeyType key, KVPair kvPair){
	Hash h = hash(key);
	Lista ini = t->l[h], p = ini;
	while(p && comp_data(p->kvP->key, key)){
		p = p->prox;
	}
	if(p == NULL){
		return false;
	}

	*kvPair = *p->kvP;
	return true;
}
/* Remove da lista de índice calculado pelo hash */
bool drop_HashT(HashT t, KeyType key){
	Hash h = hash(key);
	Lista *p = &(t->l[h]), temp;

	if(!(*p)){
		return false;
	}
	/* Procura o key em key na lista de índice h */
	while(*p != NULL && comp_data((*p)->kvP->key, key)){
		p = &((*p)->prox);
	}
	/* Se chegou ao final da lista e não achou nada, retorna falso */
	if(!(*p)){
		return false;
	}
	temp = *p;
	*p = (*p)->prox;
	free(temp->kvP->key);
	free(temp->kvP);
	free(temp);
	t->size--;
	return true;
}
/* Imprime a tabela conforme especificado no enunciado */
void print_HashT(HashT t){
	unsigned int i;
	Lista aux;
	String k;
	unsigned int v;
	for(i = 0; i < TAM_TABELA; i++){
		for(aux = t->l[i]; aux; aux = aux->prox){
			k = *(String*)(aux->kvP->key)->info;
			v = *(unsigned int*)(aux->kvP->val)->info;
			printf("(%u) ", i);
			printf("%s", k);
			printf("\"");
			printf("%u[%c]", v/2, v%2?'d':'e');
			printf("\"");
			printf("\n");

		}

	}
}

int size_HashT(HashT t){
	return t->size;
}
