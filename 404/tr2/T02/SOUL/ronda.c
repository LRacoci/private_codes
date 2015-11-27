#include "bico.h" /* Robot control API */

#define LIMITE 1024
#define AVG_LIMITE_PAREDE 512
#define STDEV_LIMITE_PAREDE 256
#define TURN_VEL 10
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

void turn(unsigned int vel, int angulo);
void walk(unsigned int vel, unsigned int distancia);
void espiral();

void swerve();

/* Funcao principal */
void _start(void) {
	/* Seta as callbacks de seguranca */
	register_proximity_callback(3, LIMITE, swerve);
	register_proximity_callback(4, LIMITE, swerve);
	set_time(0);
	/* Inicializa o tempo do sistema */
	do{
		espiral();
		/* Realiza a ronda de 50 passos indefinidamente */
	}while(1);
	espiral();
	/* Loop principal */
	do{
		/* Realiza a ronda de 50 passos indefinidamente */
	}while(1);
}

void delay(){
	int i;
	for(i = 0; i < 6000; i++);
}

void espiral(){
	int i;
	for (i = 1; i <= MAX_ESPIRAL; i++){
		walk(VEL, i);
		turn(TURN_VEL, 3);
	}
	
}
void walk(unsigned int vel, unsigned int distancia){
	estate = F;
	add_alarm(stop, get_time() + (15*distancia*UNIDADE_DE_DISTANCIA)/vel);
	do{
		set_motors_speed(vel, vel);
	}while(estate != S);
	stop();


}
/* Funcao para virar em qualquer angulo */
void turn(unsigned int vel, int angulo){
	stop();
	if (angulo > 0){
		estate = R;
		add_alarm(stop, get_time() + angulo);
		do{
			set_motor_speed(1, vel);
			delay();
		}while(estate != S);
		stop();
	}else{
		estate = L;
		add_alarm(stop, get_time() + angulo);
		do{
			set_motor_speed(0, vel);
			delay();
		}while(estate != S);
		stop();
	}
}

/* Funcao para desviar de algum obstaculo */
void swerve(){
	unsigned short s3, s4;
	/* Para, antes de mais nada */
	stop();	
	/* Tenta desviar do obstaculo */
	do{
		set_motors_speed(0, 5);
		/* Atualiza os sonares frontais */
		read_sonar(3, &s3);
		read_sonar(4, &s4);
		delay();
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