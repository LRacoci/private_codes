
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxTypes.h"
#include "Data.h"

/* STRUCTS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/
#define TAM_TABELA 50

typedef Data ValType;
typedef Data KeyType;

/* Define a struct KVPair */
typedef struct sKVPair{
	KeyType key;
	ValType val;
}sKVPair, *KVPair;
/* Define o nó de uma lista ligada simples sem nó cabeça */
typedef struct No{
	KVPair kvP;
	struct No *prox;
} No, *Lista;
/* Define a estrutura geral da tabela hash */
typedef struct sHashT{
	/* Vetor de listas alocado dinamicamente */
	Lista l[TAM_TABELA];
	unsigned int size;
} sHashT, * HashT;


/* TAD: Tabela Hash */
/*******************/

/* Cria, aloca e inicializa uma nova tabela hash */
HashT new_HashT();
/* Remove e desaloca a tabela hash passada como argumento */
void free_HashT(HashT *t);
/* Insere apropriadamente o struct pair a na tabela t */
bool put_KVPair_HashT(HashT t, KVPair kvPair);
bool put_HashT(HashT t, KeyType k, ValType v);
bool put_copy_HashT(HashT t, KeyType k, ValType v);
/* Consulta se o nome em buf está em t e devolve em a o pair correspondente */
bool get_HashT(HashT t, KeyType key, KVPair kvPair);
bool is_in_HashT(HashT t, KeyType key);
/* Remove o pair que tem o nome em buf */
bool drop_HashT(HashT t, KeyType key);
/* Imprime de acordo com o enunciado */
void print_HashT(HashT t);
/* Devolve o numero de pairs na tabela */
int size_HashT(HashT t);
