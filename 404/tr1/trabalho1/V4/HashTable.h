
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxTypes.h"
#include "Data.h"
#include "genericDefs.h"


#define TAM_TABELA 50

typedef struct HashVal{
	char t;
	unsigned int v;
} HashVal;


/* Define a struct DataPair */
typedef struct sDataPair{
	Data key;
	Data val;
}sDataPair, *DataPair;
/* Define o nó de uma lista ligada simples sem nó cabeça */
typedef struct No{
	DataPair dataP;
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

bool put_HashVal_HashT(HashT t, String k, HashVal v);
bool put_HashT(HashT t, String k, unsigned int val, char c);
bool is_in_HashT(HashT t, String key, char * c);

bool get_HashT(HashT t, String key, unsigned int * val, char * c);
DataPair new_DataPair(Data a, Data b);

DataPair copy_DataPair(DataPair src);
bool free_DataPair(DataPair *del);
/* TAD: Tabela Hash */
/*******************/

/* Cria vetor de listas e inicializa todas as posições com NULL */
HashT new_HashT();
/* Libera todos os possíveis campos alocados pra uma tabela */
void free_HashT(HashT *t);

/* Insere na lista de índice calculado pelo hash */
bool put_DataPair_HashT(HashT t, DataPair dataPair);
bool put_Data_HashT(HashT t, Data k, Data v);
bool put_copy_HashT(HashT t, Data k, Data v);
bool is_Data_in_HashT(HashT t, Data key);
bool get_Data_HashT(HashT t, Data key, Data * val);
/* Retorna se o key está na tabela ou não e o dataPair encontrado */
bool get_DataPair_HashT(HashT t, Data key, DataPair * dataPair);
/* Remove da lista de índice calculado pelo hash */
bool drop_Data_HashT(HashT t, Data key);
/* Imprime a tabela conforme especificado no enunciado */
void print_HashT(HashT t);

int size_HashT(HashT t);
HeadDefinition(HashVal);
