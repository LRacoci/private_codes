#include "bico.h" /* Robot control API */

#define LIMITE 1024
#define AVG_LIMITE_PAREDE 512
#define STDEV_LIMITE_PAREDE 256
#define TURN_VEL 10
#define VEL 15

#define ABSOLUTE(x) ((x) > 0) ? (x): (-(x))
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

void get_mins(unsigned short * l, unsigned short * r);

void get_mins_reading_all(unsigned short * l, unsigned short * r);

void stop();

void test_all_movements();


void swerve(unsigned short s3, unsigned short s4);

void folow_wall();

void search_wall();

void nana();

/* Função principal */
void _start(void) {
	int a;

	set_motors_speed(10, 10);

	do {
		read_sonar(3, &a);
		delay();
	} while (1);

}
/* Spend some time doing nothing. */
void delay()
{
	int i;
	/* Not the best way to delay */
	for(i = 0; i < 10000; i++ );  
}



void search_wall(){
	unsigned short s3, s4;
	go_front(VEL);
	do{
		read_sonar(3, &s3);
		read_sonar(4, &s4);
	}while(s3 >= LIMITE && s4 >= LIMITE);
	stop();
}
void folow_wall(){
	unsigned short s0, ds0;
	ds0 = s0;
	read_sonar(0, &s0);
	

	if(s0 < AVG_LIMITE_PAREDE - STDEV_LIMITE_PAREDE){
		turn_left(TURN_VEL);
	}else if(
		AVG_LIMITE_PAREDE < s0 && 
		s0 < AVG_LIMITE_PAREDE + STDEV_LIMITE_PAREDE
	){
		turn_right(TURN_VEL);
	}else{
		go_front(VEL);
	}

}
/* Função para desviar de algum obstáculo */
void swerve(unsigned short s3, unsigned short s4){
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
			read_sonar(3, &s3);
			read_sonar(4, &s4);
		}while(s3 < LIMITE || s4 < LIMITE);
		stop();
	}
	else{
		/* Vira pra esquerda até sair de perigo */
		do{
			turn_left(TURN_VEL);
			/* Atualiza os sonares frontais */
			read_sonar(3, &s3);
			read_sonar(4, &s4);
		}while(s3 < LIMITE || s4 < LIMITE);
		stop();
	}
}
/* Percorre os sonares frontais procurando o mínimo de ambos 
 * os lados */
void get_mins(unsigned short * l, unsigned short * r){
	unsigned char i;
	unsigned short aux;
	/* (*l) get the minimum of {s0-s3} */
	for (i = 0; i < 3; i++){
		read_sonar(i, &aux);
		if(aux < (*l)){
			(*l) = aux;
		}
	}	
	/* (*r) get the minimum of {s4-s7} */
	for(i = 5; i < 8; i++){
		read_sonar(i, &aux);
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
	set_motors_speed(vel, vel);
	estate = F;
}
/* Função para virar para a esquerda */
void turn_left(unsigned char vel){
	/* m1 = 0 */
	switch(estate){
		case F:
			set_motor_speed(1, 0);
		break;
		case L:
		break;
		/* Stop de left motor (m1) to turn left */
		case R:
			set_motors_speed(vel, 0);
		break;
		case S:
			set_motor_speed(0, vel);
		break;
	}
	estate = L;
}
/* Função para virar para a direita */
void turn_right(unsigned char vel){
	/* m0 = 0; */
	switch(estate){
		case F:
			set_motor_speed(0, 0);
		break;
		case L:
			/* Stop de right motor (m0) to turn right */
			set_motors_speed(0, vel);
		break;
		case R:
		break;
		case S:
			set_motor_speed(1, vel);
		break;
	}
	estate = R;
}

/* Função para parar */
void stop(){
	set_motors_speed(0, 0);
	estate = S;
}

void test_all_movements(){
	go_front(VEL);
	delay();
	turn_left(VEL);
	delay();
	stop();
	delay();
	turn_right(VEL);
	delay();
	stop();
	delay();
	turn_left(VEL);
	delay();
	turn_right(VEL);
	delay();
	turn_left(VEL);
	delay();
	turn_right(VEL);
	delay();
	go_front(VEL);
	delay();
	stop();
	delay();
	go_front(VEL);
	delay();
}

void nana() {

}