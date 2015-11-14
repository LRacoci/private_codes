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

	.align 4

set_motor_speed: 					@ 	(r0) : unsigned char 	id, 
	@									(r1) : unsigned char 	speed


		stmfd sp!, {r7, lr}			@ Salva os registradores callee-save 
	@									 e o endereço de retorno
	
	@ Troca r1 com r0
	mov 	r3, 	r1
	mov 	r1, 	r0
	mov 	r0, 	r3


	cmp 	r1, 	#0				@ Compare if the id argument is 0

	bne 	end_if_1
	moveq 	r7, 	#126			@ Indentify the syscall 
	@									 to set the speed of motor 1
	svc 	0x0

	end_if_1:

	cmp 	r1, 	#1				@ Compare if the id argument is 1
	bne 	end_if_2
	mov 	r7, 	#127 			@ Indentify the syscall 
	@									 to set the speed of motor 1
	svc 	0x0

	end_if_2:
		

		ldmfd sp!, {r7, pc} 		@ Restaura os registradores e retorna

set_motors_speed:					@ 	(r0) : unsigned char 	spd_m0, 
	@									(r1) : unsigned char 	spd_m1


		stmfd sp!, {r7, lr}			@ Salva os registradores callee-save 
	@									 e o endereço de retorno
	mov 	r7, 	#124
	svc 	0x0

		ldmfd sp!, {r7, pc} 		@ Restaura os registradores e retorna

read_sonar: 						@ 	(r0) : unsigned char 	sonar_id, 
@										(r1) : unsigned short* 	dist


		stmfd sp!, {r4, r7, lr}		@ Salva os registradores callee-save 
@										e o endereço de retorno
	mov 	r4, 	r1				@ Salva dist em um registrador callee-save
	mov 	r7, 	#125
	svc 	0x0
	cmp 	r4, 	#0				@ Compara se o endereco passado por parametro 
@										eh valido [nao eh o zero (NULL)]
	strne 	r0, 	[r4]			@ Se for, Grava o retorno da sys-call em dist

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