/* Nome: Lucas Alves Racoci
 * RA: 156331
 * Laboratório 10 - Hash */

#include "HashTable.h"


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
StrPair new_StrPair(String a, String b){
	StrPair neo = malloc(sizeof(sStrPair));
	neo->key = a;
	neo->val = b;
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
bool free_StrPair(StrPair *del){
	if(!(*del)) false;
	free((*del)->key);
	free((*del)->val);
	free(*del);
	*del = NULL;
	return true;
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
	No temp, p;
	for(i = 0; i < TAM_TABELA; i++){
	p = t->l[i];
		while(p){
			temp = p;
			p = p->prox;
			free_StrPair(&(temp->strP));
			free(temp);
		}
	}
	free(*t);
	*t = NULL;
}

/* Insere na lista de índice calculado pelo hash em ordem lexicográfica */
bool put_StrPair_HashT(HashT t, StrPair strPair){
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
bool put_HashT(HashT t, String k, String v){
	return put_StrPair_HashT(t, new_StrPair(k, v));
}
bool put_copy_HashT(HashT t, String k, String v){
	return put_StrPair_HashT(t, copy_StrPair(new_StrPair(k, v)));
}
bool is_in_HashT(HashT t, String key){
	StrPair lixo;
	return get_HashT(t, key, lixo);
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

	*strPair = *p->strP;
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
