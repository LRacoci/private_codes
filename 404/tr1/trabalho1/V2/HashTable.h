
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxTypes"

/* STRUCTS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/
#define TAM_TABELA 50

/* Define a struct KVPair */
typedef struct sKVPair{
	int val;
	char *nome;
}sKVPair, *KVPair;
/* Define o nó de uma lista ligada simples sem nó cabeça */
typedef struct No{
	KVPair a;
	struct No *prox;
} No, *Lista;
/* Define a estrutura geral da tabela hash */
typedef struct sHashT{
	/* Vetor de listas alocado dinamicamente */
	Lista l[TAM_TABELA];
} sHashT;


/* TAD: Tabela Hash */
/*******************/

/* Cria, aloca e inicializa uma nova tabela hash */
HashT CriaTabela();
/* Remove e desaloca a tabela hash passada como argumento */
void LiberaTabela(HashT t);
/* Insere apropriadamente o struct pair a na tabela t */
bool InsereTabela(HashT t, KVPair a);
/* Consulta se o nome em buf está em t e devolve em a o pair correspondente */
bool ConsultaTabela(HashT t, String key, KVPair a);
/* Remove o pair que tem o nome em buf */
bool RemoveTabela(HashT t, String key);
/* Imprime de acordo com o enunciado */
void ImprimeTabela(HashT t);
/* Devolve o numero de pairs na tabela */
int NumerosKVPairsTabela(HashT t);


/* Calcula o hash como indicado no enunciado */
short int hash(char* nome){
	short int i;
	/* Para garantir que o resultado seja positivo */
	unsigned char resp = 0;
	/* Acumula em resp o o resultaddo das operações xor bit a bit */
	for(i = 0; nome[i]; i++){
		resp ^= nome[i];
	}
	return (short int)resp%TAM_TABELA;
}

/* IMPLEMENTAÇÃO DAS FUNÇÕES DE MINHA TAD */
/*****************************************/
/****************************************/

/* TAD: Tabela Hash */
/*******************/

/* Cria vetor de listas e inicializa todas as posições com NULL */
HashT CriaTabela(){
	short int i;
	HashT nova_tabela;
	nova_tabela = malloc(sizeof(sHashT));
	for(i = 0; i < TAM_TABELA; i++){
		nova_tabela->l[i] = NULL;
	}
	return nova_tabela;
}
/* Libera todos os possíveis campos alocados pra uma tabela */
void LiberaTabela(HashT t){
	short int i;
	Lista temp, p;
	for(i = 0; i < TAM_TABELA; i++){
	p = t->l[i];
		while(p){
			temp = p;
			p = p->prox;
			free(temp->a->nome);
			free(temp->a);
			free(temp);
		}
	}
	free(t);
}
/* Insere na lista de índice calculado pelo hash em ordem lexicográfica */
bool InsereTabela(HashT t, KVPair pair){
	short int h = hash(pair->nome);
	Lista nova, *aux = &(t->l[h]);

	/* Avança aux até achar a posição correta de inserir */
	while(*aux && strcmp((*aux)->a->nome, pair->nome) < 0){
		aux = &((*aux)->prox);
	}
	/* Verifica se esse nome já está na Tabela */
	/* Não verifico se o val é igual senão não passa no teste 10 */
	if(*aux && strcmp(pair->nome, (*aux)->a->nome) == 0){
		return false;
	}

	/* Insere na lista t->l[h] o pair*/
	nova = malloc(sizeof(No));
	nova->a = malloc(sizeof(sKVPair));
	nova->a->nome = malloc((strlen(pair->nome) + 1) * sizeof(char));
	strcpy(nova->a->nome, pair->nome);
	nova->a->val = pair->val;
	nova->prox = *aux;
	*aux = nova;


	return true;
}
/* Retorna se o nome está na tabela ou não e o pair encontrado */
bool ConsultaTabela(HashT t, String key, KVPair pair){
	short int h = hash(buf);
	Lista ini = t->l[h], p = ini;
	while(p && strcmp(p->a->nome, buf)){
		p = p->prox;
	}
	if(p == NULL){
		return false;
	}

	pair->nome = p->a->nome;
	pair->val = p->a->val;
	return true;
}
/* Remove da lista de índice calculado pelo hash */
bool RemoveTabela(HashT t, String key){
	short int h = hash(buf);
	Lista *p = &(t->l[h]), temp;

	if(!(*p)){
		return false;
	}
	/* Procura o nome em buf na lista de índice h */
	while(*p != NULL && strcmp((*p)->a->nome, buf)){
		p = &((*p)->prox);
	}
	/* Se chegou ao final da lista e não achou nada, retorna falso */
	if(!(*p)){
		return false;
	}
	temp = *p;
	*p = (*p)->prox;
	free(temp->a->nome);
	free(temp->a);
	free(temp);
	return true;
}
/* Imprime a tabela conforme especificado no enunciado */
void ImprimeTabela(HashT t){
	short int i;
	Lista aux;
	for(i = 0; i < TAM_TABELA; i++){
		aux = t->l[i];
		while(aux){
			printf("(%d) %d \"%s\"\n", i, aux->a->val, aux->a->nome);
			aux = aux->prox;
		}

	}
}
/* 		Retorna o número de pairs na tabela,
 * contando o número de nós em cada uma das 13 listas */
int NumerosKVPairsTabela(HashT t){
	short int i;
	int r = 0;
	Lista aux;
	/* Percorre todas as listas */
	for(i = 0; i < TAM_TABELA; i++){
		aux = t->l[i];
		/* Percorre os nós de cada lista */
		while(aux){
			r++;
			aux = aux->prox;
		}
	}
	return r;
}
