/* Nome: Lucas Alves Racoci
 * RA: 156331 
 * Laboratório 10 - Hash */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* STRUCTS, DEFINIÇÕES E CABEÇALHOS DAS MINHAS FUNÇÕES DA TAD */
/*************************************************************/


/* Tamanho máximo de nome de aluno */
#define TAMMAXNOME 100 
#define TAM_TABELA 13

typedef enum bool{false, true} bool;

/* Define a struct Data */
typedef struct Data{
	int ra;
	char *nome;
} Data;
/* Define o nó de uma lista ligada simples sem nó cabeça */
typedef struct No{
	Data *a;
	struct No *prox;
} sNo, *No;
/* Define a estrutura geral da tabela hash */
typedef struct HashT{
	/* Vetor de listas alocado dinamicamente */
	No l[TAM_TABELA];
} sHashT, * HashT;


/* TAD: Tabela Hash */
/*******************/

/* Cria, aloca e inicializa uma nova tabela hash */
HashT new_HashT();
/* Remove e desaloca a tabela hash passada como argumento */
void free_HashT(HashT *t);
/* Insere apropriadamente o struct aluno a na tabela t */
bool put_HashT(HashT *t, Data *a);
/* Consulta se o nome em key está em t e devolve em a o aluno correspondente */
bool get_HashT(HashT *t, String key, Data *a);
/* Remove o aluno que tem o nome em key */
bool drop_HashT(HashT *t, String key);
/* Imprime de acordo com o enunciado */
void print_HashT(HashT *t);
/* Devolve o numero de alunos na tabela */
int size_HashT(HashT *t);


/* Calcula o hash de uma string */
Hash hash(char* nome){
	Hash i;
	/* Para garantir que o resultado seja positivo */
	unsigned char resp = 0;
	/* Acumula em resp o o resultaddo das operações xor bit a bit */
	for(i = 0; nome[i]; i++){
		resp ^= nome[i];
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
			free(temp->a->nome);
			free(temp->a);
			free(temp);
		}
	}
	free(t);
}
/* Insere na lista de índice calculado pelo hash em ordem lexicográfica */
bool put_HashT(HashT *t, Data *aluno){
	Hash h = hash(aluno->nome);
	No nova, *aux = &(t->l[h]);

	/* Avança aux até achar a posição correta de inserir */
	while(*aux && strcmp((*aux)->a->nome, aluno->nome) < 0){
		aux = &((*aux)->prox);
	}	
	/* Verifica se esse nome já está na Tabela */
	/* Não verifico se o ra é igual senão não passa no teste 10 */
	if(*aux && strcmp(aluno->nome, (*aux)->a->nome) == 0){
		return false;
	}
	
	/* Insere na lista t->l[h] o aluno*/
	nova = (No)malloc(sizeof(sNo));
	/* Copia o aluno */
	nova->a = (Data*)malloc(sizeof(Data));
	nova->a->nome = (char*)malloc((strlen(aluno->nome) + 1) * sizeof(char));
	strcpy(nova->a->nome, aluno->nome);
	nova->a->ra = aluno->ra;
	
	nova->prox = *aux;
	*aux = nova;
	

	return true;
}
/* Retorna se o nome está na tabela ou não e o aluno encontrado */
bool get_HashT(HashT *t, String key, Data *aluno){
	Hash h = hash(key);
	No ini = t->l[h], p = ini;
	while(p && strcmp(p->a->nome, key)){
		p = p->prox;
	}
	if(p == NULL){
		return false;
	}
		
	aluno->nome = p->a->nome;
	aluno->ra = p->a->ra;
	return true;
}
/* Remove da lista de índice calculado pelo hash */
bool drop_HashT(HashT *t, String key){
	Hash h = hash(key);
	No *p = &(t->l[h]), temp;
	
	if(!(*p)){
		return false;
	}
	/* Procura o nome em key na lista de índice h */
	while(*p != NULL && strcmp((*p)->a->nome, key)){
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
void print_HashT(HashT *t){
	Hash i;
	No aux;
	for(i = 0; i < TAM_TABELA; i++){
		aux = t->l[i];
		while(aux){
			printf("(%d) %d \"%s\"\n", i, aux->a->ra, aux->a->nome);
			aux = aux->prox;
		}

	}
}

int size_HashT(HashT *t){
	Hash i;
	int r = 0;
	No aux;
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