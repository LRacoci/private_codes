@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
@																		@
@  Name: Lucas Alves Racoci												@
@  RA: 156331															@
@																		@
@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @

	@ Global symbols

		.global set_motor_speed
		.global set_motors_speed
		.global read_sonar
		.global read_sonars
		.global register_proximity_callback
		.global add_alarm
		.global get_time
		.global set_time

	.align 4

set_motor_speed: 					@ 	(r0) : unsigned char 	id, 
@										(r1) : unsigned char 	speed


		stmfd sp!, {r7, lr}			@ Salva os registradores callee-save 
@										e o endereço de retorno

	mov 	r7, 	#18				@ Identifica a syscall 
	svc 	0x0

		ldmfd sp!, {r7, pc} 		@ Restaura os registradores e retorna


set_motors_speed:					@ 	(r0) : unsigned char 	spd_m0, 
@										(r1) : unsigned char 	spd_m1


		stmfd sp!, {r7, lr}			@ Salva os registradores callee-save 
@									 e o endereço de retorno

	mov 	r7, 	#19				@ Identifica a syscall 
	svc 	0x0

		ldmfd sp!, {r7, pc} 		@ Restaura os registradores e retorna


read_sonar: 						@ 	(r0) : unsigned char 	sonar_id, 
@										(r1) : unsigned short* 	dist


		stmfd sp!, {r4, r7, lr}		@ Salva os registradores callee-save 
@										e o endereço de retorno
	mov 	r4, 	r1				@ Salva dist em um registrador callee-save
	mov 	r7, 	#16
	svc 	0x0
	strh	r0, 	[r4]			@  Grava o retorno da sys-call em dist

		ldmfd sp!, {r4, r7, pc} 	@ Restaura os registradores e retorna


read_sonars: 						@ (r0) : unsigned int* 	distances


		stmfd sp!, {r4, r5, lr}		@ Salva os registradores callee-save 
@										 e o endereço de retorno
	@ Guarda o endereço do vetor
	mov r4, r0

	@ Initialization
			mov r5, #0 				@ Incializa o contador
	for_1:
			cmp r5, #16 			@ Compara o contador com 16
			bhs end_for_1			@ Se for maior ou igual, o for acaba
	@ Body
		mov r0, r5					@ Passa o primeiro argumento para a funcao
		mov r1, r4 					@ Passa o segundo  argumento para a funcao
		bl 	read_sonar 				@ Chama a função implementada acima
	
		add r4, r4, #4 				@ Atualiza o ponteiro

		@ Step
			add r5, r5, #1 			@ Atualiza o Contador
			b for_1					@ Salta para a comparacao do for
	end_for_1:


		ldmfd sp!, {r4, r5, pc} 	@ Restaura os registradores e retorna

register_proximity_callback: 		@ 	(r0) : unsigned char 	sensor_id, 
@										(r1) : unsigned short 	dist_threshold, 
@										(r2) : void (*f)()


		stmfd sp!, {r7, lr}			@ Salva os registradores callee-save 
@										 e o endereço de retorno
	mov r7, #17						@ Identifica a syscall 
	svc 0x0
		ldmfd sp!, {r7, pc}			@ Restaura os registradores e retorna

add_alarm:							@	(r0) : void (*f)(), 
@										(r1) : unsigned int time



		stmfd sp!, {r7, lr}			@ Salva os registradores callee-save 
@										 e o endereço de retorno
	mov r7, #22						@ Identifica a syscall 
	svc 0x0
		ldmfd sp!, {r7, pc}			@ Restaura os registradores e retorna

get_time:							@ Nao tem parametros



		stmfd sp!, {r7, lr}			@ Salva os registradores callee-save 
@										 e o endereço de retorno
	mov r7, #20						@ Identifica a syscall 
	svc 0x0
		ldmfd sp!, {r7, pc}			@ Restaura os registradores e retorna

set_time:							@ 	(r0) : unsigned int 	t



		stmfd sp!, {r7, lr}			@ Salva os registradores callee-save 
@										 e o endereço de retorno
	mov r7, #21						@ Identifica a syscall 
	svc 0x0
		ldmfd sp!, {r7, pc}			@ Restaura os registradores e retorna

