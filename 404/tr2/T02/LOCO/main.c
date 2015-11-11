#include "api_robot.h" /* Robot control API */

#define LIMITE 1024
#define TURN_VEL 10
#define VEL 15

#define abs(x) ((x) > 0) ? (x): (-(x))
/* Define o estado do robo */
enum Estate{S, L, R, F} estate;
/*
 * S : Parado
 * L : Virando pra esquerda
 * R : Virando pra direita
 * F : Seguindo em frente 
 */

void delay();

void turn_left(unsigned char vel);

void turn_right(unsigned char vel);

void go_front(unsigned char vel);

void get_mins_reading_all(unsigned short * l, unsigned short * r);

void stop();


void swerve(unsigned short s3, unsigned short s4);

void folow_wall();

/* Função principal */
void _start(void) {
	stop();
	/* Loop principal */
	do{
		folow_wall();
	}while(1);
	
}
/* Spend some time doing nothing. */
void delay()
{
	int i;
	/* Not the best way to delay */
	for(i = 0; i < 10000; i++ );  
}
void folow_wall(){
	unsigned short s0;
	s0 = read_sonar(0);
	if(s0 < LIMITE){
		turn_left(TURN_VEL);
	}else if(s0 > LIMITE){
		turn_right(TURN_VEL);
	}else{
		go_front(VEL);
	}

}
/* Função para desviar de algum obstáculo */
void swerve(unsigned short s3, unsigned short s4){
		/* Le os dois sonares frontais */
		s3 = read_sonar(3);
		s4 = read_sonar(4);
		/* Verifica se há perigo */
		if(s3 < LIMITE || s4 < LIMITE){
			/* Para, antes de mais nada */
			stop();	
			/* Tenta desviar do obstáculo */
			/* Recebe o mínimo de ambos os lados */
			/* Pode ser usado com essa função ou com a get_mins_reading_all
			 * que é mais lenta pois le todos os sonares */
			get_mins(&s3, &s4);
			/* Compara os dois mínimos */
			if(s3<s4){
				/* Vira pra direita até sair de perigo */
				do{
					turn_right(TURN_VEL);
					/* Atualiza os sonares frontais */
					s3 = read_sonar(3);
					s4 = read_sonar(4);
				}while(s3 < LIMITE || s4 < LIMITE);
				stop();
			}
			else{
				/* Vira pra esquerda até sair de perigo */
				do{
					turn_left(TURN_VEL);
					/* Atualiza os sonares frontais */
					s3 = read_sonar(3);
					s4 = read_sonar(4);
				}while(s3 < LIMITE || s4 < LIMITE);
				stop();
			}
		}else{
			/* Caso nao haja perigo, segue em frente */
			go_front(VEL);
		}
}
/* Percorre os sonares frontais procurando o mínimo de ambos 
 * os lados */
void get_mins(unsigned short * l, unsigned short * r){
	unsigned char i;
	unsigned short aux;
	/* (*l) get the minimum of {s0-s3} */
	for (i = 0; i < 3; i++){
		aux = read_sonar(i);
		if(aux < (*l)){
			(*l) = aux;
		}
	}	
	/* (*r) get the minimum of {s4-s7} */
	for(i = 5; i < 8; i++){
		aux = read_sonar(i);
		if(aux < (*r)){
			(*r) = aux;
		}
	}
}
/* Le todos os sonares e salva apenas os mínimos 
 * frontais de cada lateral */
void get_mins_reading_all(unsigned short * l, unsigned short * r){
	unsigned char i;
	unsigned int s[16];
	/* Read all the sonars */
	read_sonars(s);
	/* Get the minimum of the set {s0-s3} */
	for (i = 0; i <= 3; i++){
		(*l) = s[i] < (*l) ? s[i] : (*l);	
	}	
	/* Get the minimum of the set {s4-s7} */
	for(i = 4; i < 8; i++){
		(*r) = s[i] < (*r) ? s[i] : (*r);
	}
}
/* Função para seguir em frente */
void go_front(unsigned char vel){
	set_speed_motors(vel, vel);
	estate = F;
}
/* Função para virar para a esquerda */
void turn_left(unsigned char vel){
	/* m1 = 0 */
	switch(estate){
		case F:
			set_speed_motor(0, 1);
		break;
		case L:
		break;
		/* Stop de left motor (m1) to turn left */
		case R:
			set_speed_motors(vel, 0);
		break;
		case S:
			set_speed_motor(vel, 0);
		break;
	}
	estate = L;
}
/* Função para virar para a direita */
void turn_right(unsigned char vel){
	/* m0 = 0; */
	switch(estate){
		case F:
			set_speed_motor(0, 0);
		break;
		case L:
			/* Stop de right motor (m0) to turn right */
			set_speed_motors(0, vel);
		break;
		case R:
		break;
		case S:
			set_speed_motor(vel, 1);
		break;
	}
	estate = R;
}
/* Função para parar */
void stop(){
	set_speed_motors(0, 0);
	estate = S;
}
