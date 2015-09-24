#include "MemMap.h"

/* Cria um novo mapa de memória */
MemMap new_MemMap(){
	short unsigned int i;
	MemMap n = malloc(sizeof(sMemMap));
	/* Inicializa todas as posições com NULL para marcação */
	for(i = 0; i < MAX_MEM_MAP; i++){
		n->m[i] = NULL;
	}
	/* Conforme especificado no enunciado,
	 * inicia a posição de montagem em zero */
	n->pos = 0;
	return n;
}
/* Libera tudo que foi alcado para um mapa de memória */
void free_MemMap(MemMap *del){
	unsigned short int i;
	for(i = 0; i < MAX_MEM_MAP; i++){
		if((*del)->m[i]){
			free((*del)->m[i]);
			(*del)->m[i] = NULL;
		}
	}
	free(*del);
	*del = NULL;
}
/* Printa um mapa de memoria em um arquivo qualquer */
void fprint_MemMap(FILE * out, MemMap m){
	short unsigned int i;
	if(!m) return;
	for(i = 0; i < MAX_MEM_MAP; i++){
		if(m->m[i]){
			fprint_MemWord(out, m->m[i]);
		}
	}
}
/* Cria uma nova palavra de memória */
MemWord new_MemWord(unsigned int pos, bool is_word){
	unsigned short int i;
	MemWord new = malloc(sizeof(sMemWord));
	new->pos = pos;
	new->is_word = is_word;
	if(is_word){
		new->c.w.w = 0;
	}else{
		for(i = 0; i < 2; i++){
			new->c.i[i].code = 0;
			new->c.i[i].arg  = 0;
		}
	}
	return new;

}
/* Teta inserir uma instrução no mapa de memoria */
bool insert_instr_MemMap(
	MemMap m,
	unsigned int code,
	unsigned int arg,
	unsigned int line
 ){
	/* Retorna falso se não houver mapa de memoria */
	if(!m) return false;
	/* Verifica se a posição está nos limites da memória */
	if(!between(0, m->pos/2, 1023)) return false;
	/* Verifica se há algo na posição de montagem */
	if(m->m[(m->pos)/2]){
		/* Verifica se o que esta na posição de montagem eh uma palavra*/
		if(m->m[(m->pos)/2]->is_word){
			stderror(line, "Position %03X have already a word", (m->pos)/2);
			return false;
		}else{
			/* Verifica se as sub-posiçoes de montagem
			 * têm já alguma instrução*/
			if(
				m->m[(m->pos)/2]->c.i[(m->pos)%2].code && m->m[(m->pos)/2]->c.i[(m->pos)%2].arg
			){
				stderror(
					line,
					"Position %03X %c have already a instruction (%02X %03X)", (m->pos)/2, ((m->pos)%2) ? 'D' : 'E',
					m->m[(m->pos)/2]->c.i[(m->pos)%2].code,
					m->m[(m->pos)/2]->c.i[(m->pos)%2].arg
				);
				return false;
			/* Caso a área estja limpa, ocupa-se ela com a instrução
			 * a ser adicioonada*/
			}else{
				m->m[(m->pos)/2]->c.i[(m->pos)%2].code = code;
				m->m[(m->pos)/2]->c.i[(m->pos)%2].arg = arg;
				m->m[(m->pos)/2]->pos = m->pos/2;
				m->pos++;
			}
		}
	/* Se não houber nada nakela palavra de memoria */
	}else{
		/* Inicia-se uma nova palavra de memoria */
		m->m[(m->pos)/2] = new_MemWord(m->pos/2, false);
		/* Inicializa-se os valores das instruções nessa posição */
		m->m[(m->pos)/2]->c.i[(m->pos)%2].code = code;
		m->m[(m->pos)/2]->c.i[(m->pos)%2].arg = arg;
		m->pos++;
	}

	return true;

}
/* Insere um dado na palavra de memoria*/
bool insert_word_MemMap(
	MemMap m,
	unsigned long long int w,
	unsigned int line
){
	unsigned short int i;
	if(!m) return false;
	/* Verifica se a posição esta nos limites da memoria do ias */
	if(!between(0, m->pos/2, 1023)){
		stderror(line, "Position %03X is not in the memory\n",
		m->pos/2
	);
		return false;
	}
	/* Verifica se a posição em que se deseja inserir
	 * o dado ja nao esta ocupada */
	if(m->m[m->pos/2]){
		/* Verifica se é uma plavra */
		if(m->m[m->pos/2]->is_word){
			stderror(line, "Position %03X have already a word\n", m->pos/2);
			return false;
		/* Verifica onde já esta ocupado para printar
		 * um erro especifico */
		}else{
			for(i = 0; i < 2; i++){
				if(
					m->m[m->pos/2]->c.i[i].code &&
					m->m[m->pos/2]->c.i[i].arg
				){
					stderror(
						line,
						"Position %03X %c have already a instruction (%02X %03X)\n",
						m->pos/2,
						(i) ? 'D' : 'E',
						m->m[m->pos/2]->c.i[i].code,
						m->m[m->pos/2]->c.i[i].arg
					);
					return false;
				}
			}
		}
	/* Caso não haja nada nesta posição de memória */
	}else{
		/* Inicializa-se uma nova palavra de memoria */
		m->m[m->pos/2] = new_MemWord(m->pos/2, true);
		/* Trasfere-se os dados pra nova palavra de memoria criada */
		m->m[m->pos/2]->c.w.w = w;
		m->pos += 2;
	}
	return true;
}
/* Printa uma palavra em um arquivo de acordo
 * com o especificado no enunciado */
void fprint_ias_format(FILE * out, unsigned long long int hex){
	char aux[65];
	/* Declara um vetor auxiliar com o numero de digitos */
	unsigned int i, j, k, len, f[] = {2, 3, 2, 3};
	/* Printa o numero em uma  string também auxiliar*/
	sprintf(aux, "%064llX", hex);
	len = strlen(aux);
	/* Printa os ultimos caracteres da string no formato
	 * especificado no enunciado */
	for(k = len -10, i = 0; i < 4; i++){
		fprintf(out, " ");
		for(j = 0; j < f[i]; j++, k++){
			fprintf(out, "%c", aux[k]);
		}
	}
	fprintf(out, "\n");
}
/* Printa uma palavra de memoria de acordo
 * com o especificado no enunciado */
void fprint_MemWord(FILE * out, MemWord p){
	if(p == NULL){
		return;
	}
	fprintf(out, "%03X", p->pos);
	if(p->is_word){
		fprint_ias_format(out, p->c.w.w);
	}else{
		fprintf(
			out,
			" %02X %03X %02X %03X\n",
			p->c.i[0].code,
			p->c.i[0].arg,
			p->c.i[1].code,
			p->c.i[1].arg
		);
	}
}
