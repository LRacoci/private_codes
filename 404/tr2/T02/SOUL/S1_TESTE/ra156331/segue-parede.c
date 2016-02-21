#include "bico.h" /* Robot control API */

#define LIMITE 1024
#define UNIDADE_DE_TEMPO 1
#define UNIDADE_DE_DISTANCIA 1

/* Define o estado do robo */
enum Estate{S, L, R, F, B} estate;
/*
 * S : Parado
 * L : Virando pra esquerda
 * R : Virando pra direita
 * F : Seguindo em frente 
 * B : Buzy
 */


void delay();

void get_mins(unsigned short * l, unsigned short * r);

void stop();

void search_wall();
void follow_wall();

void swerve();

/* Funcao principal */
void _start(void) {

	/* Permanece indefinidamente  procurando, 
	 * e ao achar, seguindo aparede */
	do{
		search_wall();
	}while(1);

	/* Impede o codigo do usuario de acabar */
	do{
		delay();
	}while(1);
}


void delay(){
	int i;
	for(i = 0; i < 6000; i++);
}
/* Procura uma parede pra seguir, quando achar, começa a seguir */
void search_wall(){
	unsigned short int s3, s4;
	/* Comeca andando para frente */
	set_motors_speed(15, 15);
	do{
		/* Atualiza os sonares frontais */
		read_sonar(3, &s3);
		read_sonar(4, &s4);
		delay();
	/* Compara se os sonares continuam acima dos limites*/
	}while(s3 > LIMITE && s4 > LIMITE);
	/* Quando sairem do limite, ajusta-se a posicao do robo */
	swerve();
	/* Comeca-se a seguir a parede */
	follow_wall();
}
/* Segue uma parede mantendo-a a esquerda*/
void follow_wall(){
	unsigned short int i, s0, s1, s2, s3, s15;
	do{
		/* Le os dois sonares com mais probabilidade de bater */
		read_sonar( 3, &s3 );
		read_sonar( 2, &s2 );
		/* Compara os dois sonares em maior risco */
		if(s3 < LIMITE || s2 < LIMITE){
			/* Ajusta e continua aseguir */
			swerve();
		}
		/* Le os sonares pertinentes */
		read_sonar( 1, &s1 );
		read_sonar( 0, &s0 );
		read_sonar(15, &s15);

		/* Comeca a andar pra frente lentamente */
		set_motors_speed(3, 3);
		/* Se s1 ou s0 é maior que s15 */
		if(s1 > s15 || s0 > s15){
			/* Corrige, desviando levemente pra esquerda */
			set_motor_speed(0, 8);
			/* Da um tempo pra girar */
			for(i = 0; i < 64*(s1 - s15); i++);
			set_motor_speed(0, 3);
		/* Se s1 e s0 são menores que s15 */
		}else{
			/* Corrige, desviando levemente pra direita */
			set_motor_speed(0, 0);
			for(i = 0; i < 64*(s15 - s1); i++);
			set_motor_speed(0, 3);
		}
	}while(s15 <= LIMITE);
}

/* Funcao para desviar de algum obstaculo */
void swerve(){
	unsigned short s3, s4;
	/* Para, antes de mais nada */
	stop();	
	/* Tenta desviar do obstaculo */
	do{
		set_motors_speed(0, 2);
		/* Atualiza os sonares frontais */
		read_sonar(3, &s3);
		read_sonar(4, &s4);
	}while(s3 < LIMITE || s4 < LIMITE);
	stop();
}
/* Funcao para parar */
void stop(){
	set_motors_speed(0, 0);
	estate = S;
}

unsigned int __aeabi_uidiv(unsigned int a, unsigned int b) { 
	unsigned int denom, atual = 1, resp=0;
	
	if (b == 0) {
		return -1; /* Maior valor */
	}
	if ( b > a) {
		return 0;
	}

	if ( b == a) {
		return 1;
	}
	for(denom = b, atual = 1; denom <= a; denom <<= 1, atual <<= 1);

	for(denom >>= 1, atual >>= 1; atual!=0; atual >>= 1, denom >>= 1){
		if ( a >= denom) {
			a -= denom;
			resp |= atual;
		}
	} 
	return resp;
}