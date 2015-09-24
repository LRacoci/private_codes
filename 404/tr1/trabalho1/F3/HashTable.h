#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxTypes.h"
#include "Data.h"
#include "genericDefs.h"


#define TAM_TABELA 50

/* Define no da tabela */
typedef struct No{
	char k[100];
	char t;
	unsigned long long int v;
	struct No *prox;
} No, *Lista;
/* Define a estrutura geral da tabela hash */
typedef struct sHashT{
	/* Vetor de listas alocado dinamicamente */
	Lista l[TAM_TABELA];
	unsigned int size;
} sHashT, * HashT;


HashT new_HashT();

void free_HashT(HashT *t);

/* Coloca um nó na hash-table contendo a key, um valor
 * e um caracter de identificação */
bool put_HashT(HashT t, String k, unsigned long long int val, char c);
/* Retorna se foi possivel encontrar a chave na hash-table*/
bool is_in_HashT(HashT t, String key, char * c);
/* Retorna se foi possível encontrar a chave e
 * os valores guardados associados a essa chave */
bool get_HashT(HashT t, String key, unsigned long long int * val, char * c);
/* Printa a HAsh-Table de uma forma boa pra depurar */
void print_HashT(HashT t);
