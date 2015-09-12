/* Nome: Lucas Alves Racoci
 * RA: 156331
 * Laboratório 10 - Hash */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxTypes"


/* Tamanho máximo de nome de aluno */
#define TAM_TABELA 13

/* Define a struct StrPair /
typedef struct StrPair{
	String key;
	String val;
} sStrPair, *StrPair;
/* Define o nó de uma lista ligada simples sem nó cabeça */
typedef struct No{
	StrPair strP;
	struct No *prox;
} No, *Lista;
/* Define a estrutura geral da tabela hash */
typedef struct TabelaHash{
	/* Vetor de listas alocado dinamicamente */
	unsigned int size;
	Lista l[TAM_TABELA];
} sTabelaHash, TabelaHash;


/* TAD: Tabela Hash */
/*******************/

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
