#include "bico.h" /* Robot control API */

#define LIMITE 1024
#define AVG_LIMITE_PAREDE 512
#define STDEV_LIMITE_PAREDE 256
#define TURN_VEL 1
#define FOLLOW_VEL 5
#define VEL 15
#define UNIDADE_DE_TEMPO 1
#define UNIDADE_DE_DISTANCIA 1
#define MAX_ESPIRAL 50


#define ABSOLUTE(x) ((x) > 0) ? (x): (-(x))

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
	search_wall(VEL);
	
	/* Inicializa o tempo do sistema */
	set_time(0);
	/* Loop principal */
	do{
		/* Realiza a ronda de 50 passos indefinidamente */
		follow_wall();
	}while(1);
}


void search_wall(unsigned int vel){
	estate = F;
	/* Seta as callbacks de seguranca */
	register_proximity_callback(3, LIMITE, swerve);
	register_proximity_callback(4, LIMITE, swerve);
	do{
		set_motors_speed(vel, vel);
	}while(estate != S);
	stop();
	follow_wall();
}
void follow_wall(){
	short s0, sf;
	read_sonar( 0, &s0);
	read_sonar(15, &sf);
	if(s0 > sf){
		set_motor_speed(0, (63*(s0 - sf))/512);
	}else{
		set_motor_speed(1, (63*(sf - s0))/512);
	}


}

/* Funcao para desviar de algum obstaculo */
void swerve(){
	unsigned short s3, s4;
	/* Para, antes de mais nada */
	stop();	
	/* Tenta desviar do obstaculo */
	do{
		set_motors_speed(0, 1);
		/* Atualiza os sonares frontais */
		read_sonar(4, &s4);
	}while(s4 < LIMITE);
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