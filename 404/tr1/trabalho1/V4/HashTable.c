/* Nome: Lucas Alves Racoci
 * RA: 156331
 * Laboratório 10 - Hash */

#include "HashTable.h"

/* Calcula o hash de uma Data */
Hash hash(Data key){
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

bool put_HashVal_HashT(HashT t, String k, HashVal v){
	bool resp;
	Data dk = new(k, String);
	Data dv = new(v, HashVal);
	resp = put_copy_HashT(t, dk, dv);
	free_data(&dk);
	free_data(&dv);
	return resp;
}
bool put_HashT(HashT t, String k, unsigned int val, char c){
	HashVal hv;
	hv.v = val;
	hv.t = c;
	return put_HashVal_HashT(t, k, hv);
}
bool is_in_HashT(HashT t, String key, char * c){
	bool resp;
	unsigned int lixo;
	resp = get_HashT(t, key, &lixo,c);
	return resp;
}

bool get_HashT(HashT t, String key, unsigned int * val, char * c){
	bool resp;
	Data dk = new(key, String), dv;
	resp = get_Data_HashT(t, dk, &dv);
	free_data(&dk);
	if(resp){
		*val = ((HashVal*)dv->info)->v;
		*c = ((HashVal*)dv->info)->t;
	}
	return resp;
}
DataPair new_DataPair(Data a, Data b){
	DataPair neo = malloc(sizeof(sDataPair));
	neo->key = a;
	neo->val = b;
	return neo;
}

DataPair copy_DataPair(DataPair src){
	DataPair copy;
	if(!src) {
		return NULL;
	}
	copy = malloc(sizeof(sDataPair));
	copy->key = copy_data(src->key);
	copy->val = copy_data(src->val);
	return copy;


}
bool free_DataPair(DataPair *del){
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
			free_DataPair(&(temp->dataP));
			free(temp);
		}
	}
	free(*t);
	*t = NULL;
}

/* Insere na lista de índice calculado pelo hash */
bool put_DataPair_HashT(HashT t, DataPair dataPair){
	Hash h = hash(dataPair->key);
	Lista nova, *aux = &(t->l[h]);

	/* Avança aux até achar a posição correta de inserir */
	while(*aux && comp_data((*aux)->dataP->key, dataPair->key) < 0){
		aux = &((*aux)->prox);
	}
	/* Verifica se esse key já está na Tabela */
	if(*aux && comp_data(dataPair->key, (*aux)->dataP->key) == 0){
		return false;
	}

	/* Insere na lista t->l[h] o dataPair*/
	nova = malloc(sizeof(No));
	/* Copia o dataPair */
	nova->dataP = dataPair;

	nova->prox = *aux;
	*aux = nova;

	t->size++;

	return true;
}
bool put_Data_HashT(HashT t, Data k, Data v){
	return put_DataPair_HashT(t, new_DataPair(k, v));
}
bool put_copy_HashT(HashT t, Data k, Data v){
	return put_DataPair_HashT(t, copy_DataPair(new_DataPair(k, v)));
}
bool is_Data_in_HashT(HashT t, Data key){
	DataPair lixo = NULL;
	return get_DataPair_HashT(t, key, &lixo);
}
bool get_Data_HashT(HashT t, Data key, Data * val){
	DataPair d_pair = NULL;
	bool resp = get_DataPair_HashT(t, key, &d_pair);

	if(resp){
		*val = copy_data(d_pair->val);
		free_DataPair(&d_pair);
	}
	return resp;
}
/* Retorna se o key está na tabela ou não e o dataPair encontrado */
bool get_DataPair_HashT(HashT t, Data key, DataPair * dataPair){
	Hash h = hash(key);
	Lista ini = t->l[h], p = ini;
	while(p && comp_data(p->dataP->key, key)){
		p = p->prox;
	}
	if(p == NULL){
		return false;
	}

	*dataPair = copy_DataPair(p->dataP);
	return true;
}
/* Remove da lista de índice calculado pelo hash */
bool drop_Data_HashT(HashT t, Data key){
	Hash h = hash(key);
	Lista *p = &(t->l[h]), temp;

	if(!(*p)){
		return false;
	}
	/* Procura o key em key na lista de índice h */
	while(*p != NULL && comp_data((*p)->dataP->key, key)){
		p = &((*p)->prox);
	}
	/* Se chegou ao final da lista e não achou nada, retorna falso */
	if(!(*p)){
		return false;
	}
	temp = *p;
	*p = (*p)->prox;
	free(temp->dataP->key);
	free(temp->dataP);
	free(temp);
	t->size--;
	return true;
}
/* Imprime a tabela conforme especificado no enunciado */
void print_HashT(HashT t){
	unsigned int i;
	Lista aux;
	String k;
	HashVal v;
	for(i = 0; i < TAM_TABELA; i++){
		for(aux = t->l[i]; aux; aux = aux->prox){
			k = *(String*)(aux->dataP->key)->info;
			v = *(HashVal*)(aux->dataP->val)->info;
			cfprintf(stdout, 94 ,"(%02u) ", i);
			cfprintf(stdout, 93 ,"%s", k);
			cfprintf(stdout, 96 ,"(%c)", v.t);
			cfprintf(stdout, 97 ," \"");
			cfprintf(stdout, 97 ,"%03X[%c]", v.v/2, v.v%2?'d':'e');
			cfprintf(stdout, 97 ,"\"");
			printf("\n");

		}

	}
}

int size_HashT(HashT t){
	return t->size;
}


size_t ___HashVal_size(Info i){
    return sizeof(HashVal);
}
void ___HashVal_print(Info i){
	HashVal p = *(HashVal*)(i);
	printf("%c %03X", p.t, p.v);
}
void ___HashVal_free(Info *i){
    free(*i);
    *i = NULL;
}
Info ___HashVal_copy(Info i){
    HashVal* resp;
    if(!i){
        return i;
    }
    resp = malloc(sizeof(HashVal));
	*resp = *(HashVal*)i;
    return resp;
}
Hash ___HashVal_hash(Info i){
    return (*(HashVal*)i).v;
}
Comp ___HashVal_comp(Info a, Info b){
    return numcmp((*(HashVal*)a).v, (*(HashVal*)b).v);
}
