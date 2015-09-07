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

/* Define a struct Aluno */
typedef struct Aluno{
	int ra;
	char *nome;
} Aluno;
/* Define o nó de uma lista ligada simples sem nó cabeça */
typedef struct No{
	Aluno *a;
	struct No *prox;
} No, *Lista;
/* Define a estrutura geral da tabela hash */
typedef struct TabelaHash{
	/* Vetor de listas alocado dinamicamente */
	Lista l[TAM_TABELA];
} TabelaHash;


/* TAD: Tabela Hash */
/*******************/

/* Cria, aloca e inicializa uma nova tabela hash */
TabelaHash* CriaTabela();
/* Remove e desaloca a tabela hash passada como argumento */
void LiberaTabela(TabelaHash *t);
/* Insere apropriadamente o struct aluno a na tabela t */
bool InsereTabela(TabelaHash *t, Aluno *a);
/* Consulta se o nome em buf está em t e devolve em a o aluno correspondente */
bool ConsultaTabela(TabelaHash *t, char buf[TAMMAXNOME], Aluno *a);
/* Remove o aluno que tem o nome em buf */
bool RemoveTabela(TabelaHash *t, char buf[TAMMAXNOME]);
/* Imprime de acordo com o enunciado */
void ImprimeTabela(TabelaHash *t);
/* Devolve o numero de alunos na tabela */
int NumeroAlunosTabela(TabelaHash *t);


/* ASSINATURA DE OUTRAS FUNÇÕES */ 
/*******************************/

/* Lê RA e nome de aluno */
void LeAluno(Aluno *a);

/* Lê linha de comando */
void lelinha();


/* PROGRAMA PRINCIPAL */ 
/*********************/
int main(int argc, char *argv[]) {

	TabelaHash *t = CriaTabela();
	char comando[100], buf[TAMMAXNOME];
	Aluno a;  

	/*loop para ler entrada*/
	while (scanf("%s", comando) > 0 ){
		if(strcmp(comando,"insere") == 0){
			LeAluno(&a);
			printf("Insere: %06d \"%s\"\n", a.ra, a.nome);
			/* Insere aluno 'a' na tabela 't' */
			if (!InsereTabela(t, &a)) {	
				printf("Nome repetido: \"%s\"\n", a.nome);
			}
			free(a.nome);

		} else if ( strcmp(comando, "remove") == 0 ) {

			scanf(" \"%[^\"]\"", buf);
			printf("Remove: \"%s\"\n", buf);
			/* remove aluno de nome 'buf' da tabela 't'*/
			if (!RemoveTabela(t, buf))	
			printf("Nome inexistente: \"%s\"\n", buf);

		} else if ( strcmp(comando, "consulta") == 0 ) {

			scanf(" \"%[^\"]\"", buf);
			printf("Consulta: \"%s\"\n", buf);
			if (ConsultaTabela(t, buf, &a)) 
			/*consulta aluno de nome 'buf' na tabela 't', grava dados em 'a', retorna 0 se nao encontrou aluno*/
			printf("%06d \"%s\"\n", a.ra, a.nome);
			else
			printf("Nome inexistente: \"%s\"\n", buf);

		} else if ( strcmp(comando, "imprime") == 0 ) {
			/*Calcula numero de alunos na tabela 't'*/
			printf("\nImprime Tabela: %d aluno(s):\n", NumeroAlunosTabela(t)); 
			ImprimeTabela(t);
			printf("\n");
		/*termina programa*/
		} else if ( strcmp(comando, "sair") == 0 ) { 
			break;
		} else {
			printf("Comando desconhecido: `%sÃ‚Â´\n", comando);
		}
	}

	LiberaTabela(t); /*libera memoria*/

	return 0;
}

/* IMPLEMENTAÇÃO DE OUTRAS FUNÇÕES */ 
/***********************************/
/**********************************/

/* Lê RA e nome de aluno */
void LeAluno(Aluno *aluno) {
	char buf[TAMMAXNOME];
	scanf("%d \"%[^\"]\"", &aluno->ra, buf);

	aluno->nome = (char*)malloc((strlen(buf)+1)*sizeof(char));
	strcpy(aluno->nome, buf);
	return;
}
/* Lê linha de comando */
void lelinha() {
	int c;
	do { 
		c = getchar(); 
	} while (c != '\n');
}
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
TabelaHash* CriaTabela(){
	short int i;
	TabelaHash *nova_tabela;
	nova_tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
	for(i = 0; i < TAM_TABELA; i++){
		nova_tabela->l[i] = NULL;
	}
	return nova_tabela;
}
/* Libera todos os possíveis campos alocados pra uma tabela */
void LiberaTabela(TabelaHash *t){
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
bool InsereTabela(TabelaHash *t, Aluno *aluno){
	short int h = hash(aluno->nome);
	Lista nova, *aux = &(t->l[h]);

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
	nova = (Lista)malloc(sizeof(No));
	nova->a = (Aluno*)malloc(sizeof(Aluno));
	nova->a->nome = (char*)malloc((strlen(aluno->nome) + 1) * sizeof(char));
	strcpy(nova->a->nome, aluno->nome);
	nova->a->ra = aluno->ra;
	nova->prox = *aux;
	*aux = nova;
	

	return true;
}
/* Retorna se o nome está na tabela ou não e o aluno encontrado */
bool ConsultaTabela(TabelaHash *t, char buf[TAMMAXNOME], Aluno *aluno){
	short int h = hash(buf);
	Lista ini = t->l[h], p = ini;
	while(p && strcmp(p->a->nome, buf)){
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
bool RemoveTabela(TabelaHash *t, char buf[TAMMAXNOME]){
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
void ImprimeTabela(TabelaHash *t){
	short int i;
	Lista aux;
	for(i = 0; i < TAM_TABELA; i++){
		aux = t->l[i];
		while(aux){
			printf("(%d) %d \"%s\"\n", i, aux->a->ra, aux->a->nome);
			aux = aux->prox;
		}

	}
}
/* 		Retorna o número de alunos na tabela, 
 * contando o número de nós em cada uma das 13 listas */
int NumeroAlunosTabela(TabelaHash *t){
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