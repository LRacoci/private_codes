@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @
@																		@
@ 	Trabalho 2 de MC404 - Sistema de software do Uoli					@
@	-	#	-	#	-	#	-	#	-									@
@																		@
@	Autores:															@
@		Nome: 	Luiz Fernando Rodrigues da Fonseca						@
@		RA:		156475													@
@																		@
@		Nome: 	Lucas Alves Racoci										@
@		RA: 	156331													@
@																		@
@																		@
@																		@
@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @


@ Endereco de inicio do codigo do usuario
.set USER_START_POSITION, 	0x77802000

.org 0x0

.section .iv,"a"

_start:	

interrupt_vector:

	b RESET_HANDLER
.org 0x04
	b UNDEFINED_INSTRUCTION
.org 0x08
	b SVC_HANDLER
.org 0x0C
	b INSTRUCTION_ABORT_HANDLER
.org 0x10
	b DATA_ABORT_HANDLER
.org 0x18
	b IRQ_HANDLER
.org 0x1C
	b FIQ_ABORT_HANDLER

.org 0x100

.text

@ Modos com as flags de interrupcoes desabilitadas
.set USR_MODE_I_1_F_1, 		0xD0
.set FIQ_MODE_I_1_F_1, 		0xD1
.set IRQ_MODE_I_1_F_1, 		0xD2
.set SVC_MODE_I_1_F_1, 		0xD3
.set ABT_MODE_I_1_F_1, 		0xD7
.set UND_MODE_I_1_F_1, 		0xDB
.set SYS_MODE_I_1_F_1, 		0xDF

@ Modos com as flags de interrupcoes habilitadas
.set USR_MODE_I_0_F_0, 		0x10
.set FIQ_MODE_I_0_F_0, 		0x11
.set IRQ_MODE_I_0_F_0, 		0x12
.set SVC_MODE_I_0_F_0, 		0x13
.set ABT_MODE_I_0_F_0, 		0x17
.set UND_MODE_I_0_F_0, 		0x1B
.set SYS_MODE_I_0_F_0, 		0x1F

RESET_HANDLER:

    @ Zera o contador
    ldr r2, =system_time				@ Carrega o endereco da variavel
    mov r0, #0							@ Move o valor 0 para r0
    str r0, [r2]						@ Guarda o valor inicializado

    @ Set interrupt table base address on coprocessor 15.
    ldr r0, =interrupt_vector
    mcr p15, 0, r0, c12, c0, 0

	initialize_stacks:

		msr CPSR_c, IRQ_MODE_I_1_F_1 	@ IRQ mode, interrupcoes desabilitadas
		ldr sp, =STACK_IRQ_BASE			@ Inicializa pilha sp_IRQ

		msr CPSR_c, SYS_MODE_I_1_F_1 	@ SYS mode, interrupcoes desabilitadas
		ldr sp, =STACK_SYS_BASE			@ Inicializa pilha sp_SYS

		msr CPSR_c, SVC_MODE_I_1_F_1 	@ SVC mode, interrupcoes desabilitadas
		ldr sp, =STACK_SVC_BASE			@ Inicializa pilha sp_SVC

	set_gpt:
		@ Constantes para os enderecos do GPT
		.set GPT_BASE, 			0x53FA0000
		.set GPT_CR, 			0x0
		.set GPT_PR, 			0x4
		.set GPT_SR,			0x8
		.set GPT_OCR1,			0x10
		.set GPT_IR,			0xC

		@ Constante do contador de ciclos para gerar uma interrupcao
		.set TIME_SZ,			0x330
		
		@ Carrega a base do GPT
		ldr r1, =GPT_BASE

		@ Habilitar e configurar o clock_src para periférico
		ldr r0, =0x41
		str	r0, [r1, #GPT_CR]

		@ Zerar o prescaler (GPT_PR)
		ldr r0, =0x0
		str	r0, [r1, #GPT_PR]

		@ Colocar em GPT_OCR1 o valor que gera 
		@ a interrupção durante a contagem
		ldr r0, =TIME_SZ
		str	r0, [r1, #GPT_OCR1]

		@ Habilitar a interrupção Output Compare Channel 1
		ldr r0, =0b1
		str	r0, [r1, #GPT_IR]

	set_tzic:
		@ Constantes para os enderecos do TZIC
		.set TZIC_BASE,             0x0FFFC000
		.set TZIC_INTCTRL,          0x0
		.set TZIC_INTSEC1,          0x84 
		.set TZIC_ENSET1,           0x104
		.set TZIC_PRIOMASK,         0xC
		.set TZIC_PRIORITY9,        0x424

		@ Liga o controlador de interrupcoes
		@ R1 <= TZIC_BASE

		ldr	r1, =TZIC_BASE

		@ Configura interrupcao 39 do GPT como nao segura
		mov	r0, #(1 << 7)
		str	r0, [r1, #TZIC_INTSEC1]

		@ Habilita interrupcao 39 (GPT)
		@ reg1 bit 7 (gpt)

		mov	r0, #(1 << 7)
		str	r0, [r1, #TZIC_ENSET1]

		@ Configure interrupt39 priority as 1
		@ reg9, byte 3

		ldr r0, [r1, #TZIC_PRIORITY9]
		bic r0, r0, #0xFF000000
		mov r2, #1
		orr r0, r0, r2, lsl #24
		str r0, [r1, #TZIC_PRIORITY9]

		@ Configure PRIOMASK as 0
		eor r0, r0, r0
		str r0, [r1, #TZIC_PRIOMASK]

		@ Habilita o controlador de interrupcoes
		mov	r0, #1
		str	r0, [r1, #TZIC_INTCTRL]

	set_gpio:
		@ Constantes para os enderecos do GPIO
		.set GPIO_BASE, 			0x53F84000
		.set GPIO_DR,				0x0
		.set GPIO_GDIR, 			0x4
		.set GPIO_PSR, 				0x8

		ldr	r1, =GPIO_BASE

		@ Configurar entradas e saídas da GPIO
		ldr r0, =0xFFFC003E @ 1 = Saída 0 = Entrada
		str	r0, [r1, #GPIO_GDIR]

		@ Zera as entradas do GPIO_DR
		ldr r2, [r1, #GPIO_DR]
		bic r0, r2, r0 
		str	r0, [r1, #GPIO_DR]

	@ Muda para o modo usuário
	CHANGE_TO_USER_MODE_IN_THE_START_POSITION:

		ldr r1, =USER_START_POSITION	@ Carrega a posicao do programa do usuario
		msr CPSR_c, #USR_MODE_I_0_F_0   @ Modo USR, com as interrupcoes habilitadas
		mov pc, r1						@ Pula para a posicao de inicio do usuario


IRQ_HANDLER:
	stmfd sp!, {r0, r2, r3, r11, lr}	@ Salva contexto
	mrs r11, SPSR					 	@ Move registrador de status de retorno
	stmfd sp!, {r11}					@ Guarda na pilha
	
	@ Informa ao GPT que o  processador 
	@ já está ciente de que ocorreu a interrupção
	ldr r2, =GPT_BASE
	mov r0, #0x1
	str r0, [r2, #GPT_SR]

	@ Le o endereço do contador de tempo de sistema
	ldr r2, =system_time

	@ Carega o tempo do sistema
	ldr r0, [r2]

	@ Incrementa o tempo do sistema
	add r0, r0, #1

	@ Grava de volta o tempo do sistema incrementado
	str r0, [r2]

	@ Tratamento de alarmes e callbacks
	mrs r3, CPSR 						@ Salva modo atual pra voltar
	
		@ Mudar para o modo usuario habilitando interrupcoes
		msr CPSR_c, USR_MODE_I_0_F_0 
		
		stmfd sp!, {r3}					@ Salva contexto

			@ Tratamento dos alarmes em modo usuario
			bl alarms_handler
			@ Tratamento das Callbacks em modo usuario
			bl callbacks_handler

		ldmfd sp!, {r3}					@ Recupera contexto
		
		@ Voltar do modo usuario
		mov r0, r3						@ Status anterior ao modo USER 
		mov r7, #23						@ Identifica a syscall
		svc 0x0
	
	ldmfd 	sp!, {r11}					@ Desempilha status anterior
	msr SPSR, r11						@ Recupera o status anterior
	ldmfd sp!, {r0, r2, r3, r11, lr}	@ Recupera contexto
	
	sub 	lr, lr, #4					@ Ajusta o lr antes de retornar
	movs 	pc, lr


alarms_handler:
	stmfd sp!, {r4-r6, lr} 		@ Salva Registradores Callee-save

	ldr r1, =active_alarms		@ Carrega o numero de alarmes
	ldr r1, [r1]

	ldr r2, =alarms_vect		@ Carrega a base do vetor de alarmes

	ldr r3, =system_time		@ Carrega o tempo do sistema
	ldr r3, [r3]

	@ Inicialização do for
	mov r0, #0					@ Inicializa o iterador
	for_1:
		cmp r0, r1				@ Compara iterador com tamanho do vetor
		bhs end_for_1			@ Salta caso r0 >= r1
	@ Corpo do for
		ldr r4, [r2], #4		@ Carrega o tempo na posicao atual do vetor
		ldr r5, [r2]			@ Carrega o endereco da funcao

		if_1:
			mov r6, r5			@ Copia o endereco da funcao
			cmp r5, #0			@ Ve se a funcao ja foi marcada
								@ como se estivesse finalizada
			beq end_if_1		@ Pula o if se r5 == 0

			cmp r5, #1			@ Ve se a funcao ja foi marcada
								@ como se estivesse sendo executada
			beq end_if_1		@ Pula o if se r5 == 1

			cmp r3, r4			@ Compara tempo atual com tempo do vetor
			blo end_if_1		@ Pula o if se r3 < r4

			@ if (r5 != 0 && r3 >= r4 && r5 != 1)
			mov r5, #1			@ Coloca o valor 1 em r5
			str r5, [r2]		@ Marca a funcao a ser chamada para que
								@ ela nao seja chamada na proxima vez

			stmfd sp!, {r0-r3}	@ Salva o contexto
			blx r6				@ Pula para o codigo do usuario
			ldmfd sp!, {r0-r3}	@ Recupera o contexto

			mov r5, #0			@ Move o valor 0 para r5
			str r5, [r2]		@ Marca a funcao que foi chamada dizendon que
								@ ela ja acabou, e pode ser retirada do vetor
		
		end_if_1:
		add r2, r2, #4			@ Incrementa a posicao do vetor
	
	@ Passo
		add r0, r0, #1			@ Incrementa o iterador
		b for_1

	end_for_1:

	@ Chama uma rotina para retirar os alarmes que foram usados
	ldr r0, =alarms_vect		@ Passa o endereco do vetor
	ldr r1, =active_alarms		@ Passa o endereco do tamanho do vetor
	bl vector_rectifier

	ldmfd sp!, {r4-r6, pc} 		@ Recupera Registradores Callee-save


callbacks_handler:
	stmfd sp!, {r5-r9, lr} 		@ Salva Registradores Callee-save

	ldr r2, =active_callbacks	@ Carrega o numero de callbacks
	ldr r2, [r2]

	ldr r3, =callbacks_vect		@ Carrega a base do vetor de callbacks

	@ Inicialização do for
	mov r8, #0					@ Inicializa o iterador
	for_3:
		cmp r8, r2				@ Compara iterador com tamanho do vetor
		bhs end_for_3			@ Salta caso r8 >= r2

	@ Corpo do for
		ldrh r0, [r3], #2		@ Carrega o id do sensor
		ldrh r5, [r3], #2		@ Carrega a distancia limite
		ldr r6, [r3]			@ Carrega o endereco da funcao

		cmp r6, #0				@ Ve se a funcao ja foi marcada
		beq end_if_3			@ Salta para o fim caso verdade

		mov r7, #16				@ Move o identificador da syscall read_sonar
		stmfd sp!, {r2, r3}		@ Salva o contexto
		svc 0x0
		ldmfd sp!, {r2, r3}		@ Recupera o contexto

		if_3:
			cmp r0, r5			@ Compara tempo atual com tempo do vetor
			bhi end_if_3		@ Pula o if se r0 > r5

			@ if (r0 <= r5)
			mov r9, r6			@ Copia o endereco de salto da funcao
			mov r6, #0			@ Coloca o valor 0 em r6
			str r6, [r3]		@ Marca a funcao a ser chamada
			
			stmfd sp!, {r0-r3}	@ Salva o contexto
			blx r9				@ Pula para o codigo do usuario
			ldmfd sp!, {r0-r3}	@ Recupera o contexto
			str r9, [r3]		@ Desmarca a funcao que foi chamada
		
		end_if_3:
		add r3, r3, #4			@ Incrementa a posicao do vetor
	
	@ Passo
		add r8, r8, #1			@ Incrementa o iterador
		b for_3

	end_for_3:
	ldmfd sp!, {r5-r9, pc} 		@ Recupera Registradores Callee-save


vector_rectifier:				@ (r0) : struct			vetor
								@ (r1) : unsigned int* 	tam
	stmfd sp!, {r4-r8, lr} 		@ Salva Registradores Callee-save

	@ Inicializacao do for
		mov r2, #0				@ Iterador: i = 0
		ldr r4, [r1]			@ Tamanho mutavel do vetor
		mov r5, r4				@ Tamanho inicial fixo do vetor
		mov r6, r0				@ Copia o endereco do vetor em um auxiliar
	for_2:
		cmp r2, r5				@ Compara o iterador com o tamanho fixo
		bhs end_for_2			@ Salta para o fim se acabou
	
	@ Corpo
		ldr r8, [r0, #4]		@ Carrega o endereco da funcao
		
		if_2:
			cmp r8, #0			@ Compara o endereco com 0
			beq else_if_2		@ Se for igual salta para o else,
								@ se for diferente, reordena o vetor
			@ if (r8 != 0)
			ldr r7, [r0]		@ Carrega o valor a primeira posicao da struct
			str r7, [r6], #4	@ Salva na posicao auxiliar a primeira parte da struct
			str r8, [r6], #4	@ Salva na posicao auxiliar a segunda parte
			b end_if_2			@ Salta para o fim do if
		
		else_if_2:
			sub r4, r4, #1		@ Subtrai o tamanho do vetor pois encontrou
								@ uma marcacao com o valor 0

		end_if_2:
		add r0, r0, #8			@ Incrementa a posicao atual do vetor
	
	@ Passo
		add r2, r2, #1			@ Incrementa o iterador
		b for_2

	end_for_2:

	str r4, [r1]				@ Guarda o novo tamanho do vetor no endereco apropriado
	ldmfd sp!, {r4-r8, pc} 	@ Recupera Registradores Callee-save


SVC_HANDLER:
	stmfd sp!, {r7, r11, lr}			@ Salva contexto
	mrs r11, SPSR					 	@ Move registrador de status de retorno
	stmfd sp!, {r11}					@ Guarda na pilha

	msr CPSR_c, #SVC_MODE_I_0_F_0	@ SVC mode, interrupcoes abilitadas

	sub r7, r7, #16				@ Subtrai o valor da syscall de r7
	ldr lr, =end_svc_handler	@ Carrega em lr o valor da posicao
								@ para retornar apos tratar a syscall
	add pc, pc, r7, lsl #2		@ Faz um deslocamento em pc para pular para
								@ a posicao correta no vetor de rotinas

	@ Apesar de parecer inútil, esse comando 
	@ é necessário para o salto na intstrução 
	@ anterior dar certo
	mov r0, r0 
	
	@ Vetor de rotinas que cuidam das varias syscalls
	b read_sonar
	b register_proximity_callback 
	b set_motor_speed 
	b set_motors_speed
	b get_time
	b set_time
	b set_alarm
	@ Syscalls Personalizadas
	b back_to_r0

	end_svc_handler:
		ldmfd 	sp!, {r11}				@ Desempilha status anterior
		msr SPSR, r11					@ Recupera status anterior
		ldmfd 	sp!, {r7, r11, lr}		@ Recupera contexto
		movs 	pc, lr


read_sonar:						@ (r0) : unsigned char 		sonar_id, 
								@ (r1) : unsigned short* 	dist
	stmfd sp!, {lr}
	msr CPSR_c, #SVC_MODE_I_1_F_1 @ Desabilita interrupcoes durante a leitura do sonar
	
	@ Confere se o sonar e valido
	cmp r0, #0b1111
	movhi r0, #0
	subhi r0, r0, #1
	bhi end_read_sonar

	@ Corpo da funcao
	@ @ @ @ @ @ @ @ @ @ @ @ @ @ @

	@ SONAR_MUX <= sonar_id (r0)
	ldr	r3, =GPIO_BASE 			@ Carrega a Base do GPIO
	ldr r2, [r3, #GPIO_DR]		@ Carrega Valor de DR

	bic r2, #(0b1111<<2)		@ Limpa Bits de 2 a 5
	orr r2, r0, lsl #2			@ Escreve sonar_id em SONAR_MUX

	str	r2, [r3, #GPIO_DR] 		@ Grava em DR

	@ TRIGGER <= 0; Delay
	bic r2, #0b10				@ Limpa o Trigger
	str	r2, [r3, #GPIO_DR] 		@ Grava em DR

	stmfd sp!, {r2, r3}			@ Salva os registradores caller-save
	bl delay_sonar				@ Salta para o loop de espera
	ldmfd sp!, {r2, r3}			@ Recupera os registradores

	@ TRIGGER <= 1; Delay
	orr r2, #0b10				@ Adiciona o valor 1 bit do trigger
	str	r2, [r3, #GPIO_DR] 		@ Grava em DR

	stmfd sp!, {r2, r3}			@ Salva os registradores caller-save
	bl delay_sonar				@ Salta para o loop de espera
	ldmfd sp!, {r2, r3}			@ Recupera os registradores

	@ TRIGGER <= 0;
	bic r2, #0b10				@ Limpa o Trigger
	str	r2, [r3, #GPIO_DR] 		@ Grava em DR

	@ FLAG == 1 ?
	loop_flag:
		ldr r2, [r3, #GPIO_DR]	@ Carrega Valor de PSR
		and r2, r2, #1			@ Isola a flag
		cmp r2, #1				@ Compara flag com 1
		@ Nao
			@ Delay
		stmfd sp!, {r3}			@ Salva o resgistrador caller-save
		blne delay_sonar		@ Chama o delay enquanto flag != 1
		ldmfd sp!, {r3}			@ Recupera o contexto

		bne loop_flag			@ Repete o loop

	@ SIM
		@ Distancia <= Sonar_Data
	ldr r2, [r3, #GPIO_DR]		@ Carrega Valor de PSR
	lsl r2, #14					@ Desloca os bits de r2 para esquerda e depois para
	lsr r2, #20					@ direita para manter apenas os bits da distancia
	
	mov r0, r2					@ Move a distancia para r0

	end_read_sonar:
		msr CPSR_c, #SVC_MODE_I_0_F_0 @ Reabilita interrupcoes
		ldmfd sp!, {pc}


register_proximity_callback :	@ (r0) : unsigned char 	sensor_id, 
								@ (r1) : unsigned short 	dist_threshold, 
								@ (r2) : void (*f)()
	stmfd sp!, {r4-r6, lr}
	
	@ Conferir se os argumentos são válidos
	@ Carregas o valor maximo de Callbacks e os ativos
	ldr r4, =MAX_CALLBACKS
	ldr r5, =active_callbacks
	ldr r3, [r5]

	@ Compara para ver se esta no maximo e retorna caso for verdade
	cmp r3, r4
	movhs r0, #0
	subhs r0, r0, #1
	bhs end_register_proximity_callback

	@ Checa se o identificador do sonar e valido
	cmp r0, #0b1111
	movhi r0, #0
	subhi r0, r0, #2
	bhi end_register_proximity_callback
	
	@ Corpo da funcao
    ldr 	r6, =callbacks_vect		@ Carrega a base do vetor de callbacks
    add 	r6, r6, r3, lsl #3		@ Faz um deslocamento considerando a
    								@ quantidade de elementos no vetor e
    								@ o tamanho de cada posicao do vetor
    strh 	r0, [r6], #2			@ Guarda o id do sonar
    strh 	r1, [r6], #2			@ Guarda a distancia limite
    str 	r2, [r6]				@ Guarda o endereco da funcao a ser chamada

    @ Incremento contador de alarmes
    add r3, r3, #1
    @ Grava de volta o contador incrementado
    str r3,[r5]

    @ Retorna 0 indicando sucesso
	mov r0, #0

	end_register_proximity_callback:
		ldmfd sp!, {r4-r6, pc}


set_motor_speed:				@ (r0) : unsigned char 	id, 
								@ (r1) : unsigned char 	speed
	stmfd sp!, {lr}
	
	@ Conferir se os argumentos são válidos
	@ Checa se o identificador do sonar e valido
	@ e retorna caso contrario
	cmp r0, #0b1
	movhi r0, #0
	subhi r0, r0, #1
	bhi end_set_motor_speed

	@ Checa se a velocidade e valida, ou seja,
	@ possui valor no maximo ate o bit 6
	cmp r1, #0b111111
	movhi r0, #0
	subhi r0, r0, #2
	bhi end_set_motor_speed
	
	@ Corpo da funcao
	@ @ @ @ @ @ @ @ @

	@ Carrega o valor de DR
	ldr	r3, =GPIO_BASE
	ldr r2, [r3, #GPIO_DR]

	@ Compara com zero para saber o motor
	cmp r0, #0

	@ Modifica apenas os bits correspondente ao motor correto
	@ fazendo um bic com uma mascara e orr para modificar
	biceq r2, #(0b111111<<19)
	orreq r2, r1, lsl #19
	bicne r2, #(0b111111<<26)
	orrne r2, r1, lsl #26

	@ Guarda o valor de DR
	str	r2, [r3, #GPIO_DR]

	@ Realiza uma espera para se ter certeza que foi escrito no motor
	bl delay_motors

	@ Move o valor 0 para r0 identificando a corretude da syscall
	mov r0, #0

	end_set_motor_speed:
		ldmfd sp!, {pc}


set_motors_speed:				@ (r0) : unsigned char 	spd_m0, 
								@ (r1) : unsigned char 	spd_m1
	stmfd sp!, {lr}

	@ Confere se as duas velocidades sao validas, retornando em r0
	@ -1 caso a primeira seja invalida e -2 caso a segunda seja invalida
	cmp r0, #0b111111
	movhi r0, #0
	subhi r0, r0, #1
	bhi end_set_motors_speed
	cmp r1, #0b111111
	movhi r0, #0
	subhi r0, r0, #2
	bhi end_set_motors_speed

	@ Corpo da funcao
	@ @ @ @ @ @ @ @ @ 

	@ Carrega o valor de DR
	ldr	r3, =GPIO_BASE
	ldr r2, [r3, #GPIO_DR]

	@ Escreve as duas velocidades, uma de cada vez, fazendo bic
	@ com uma mascara e orr para modificar apenas o necessario
	bic r2, #(0b111111<<19)
	orr r2, r0, lsl #19
	bic r2, #(0b111111<<26)
	orr r2, r1, lsl #26

	@ Guarda o valor em DR e realiza uma espera
	str	r2, [r3, #GPIO_DR] 
	bl delay_motors

	@ Move 0 para r0 confirmando a validade da syscall
	mov r0, #0

	end_set_motors_speed:
		ldmfd sp!, {pc}


get_time:						@ 	Nao tem parametros
	stmfd sp!, {lr}

	ldr r0, =system_time		@ Pega o tempo do sistema e retorna para o usuario
	ldr r0, [r0]

	ldmfd sp!, {pc}


set_time:						@ 	(r0) : unsigned int 	t
	stmfd sp!, {lr}

	ldr r1, =system_time		@ Carrega o endereco da variavel do tempo do sistema
	str r0, [r1]				@ Guarda o novo valor

	ldmfd sp!, {pc}


set_alarm:						@ (r0) : void (*f)(), 
								@ (r1) : unsigned int time
	stmfd sp!, {r4-r5, lr}

	@ Confere se o numero de alarmes ativos e menor que o maximo possivel
	ldr r2, =MAX_ALARMS
	ldr r4, =active_alarms
	ldr r3, [r4]
	cmp r3, r2

	@ Salta para o fim retornando -1 caso tenha extrapolado limite de alarmes
	movhs r0, #0
	subhs r0, r0, #1
	bhs end_set_alarm

	@ Salta para o fim retornando -2 caso o tempo do sistema
	@ seja menor ou igual o tempo que ele queira setar
	ldr r2, =system_time
	ldr r2, [r2]
	cmp r1, r2 					@ r1 = time; r2 = System Time
	movls r0, #0
	subls r0, r0, #2
	bls end_set_alarm

	@ Corpo da funcao
    ldr r5, =alarms_vect		@ Carrega o endereco do vetor de alarmes
    add r5, r5, r3, lsl #3		@ Desloca o apontador considerando
    							@ o numero de alarmes ativos
    str r1, [r5], #4			@ Guarda o tempo para ser chamado
    str r0, [r5]				@ Guarda o endereco da funcao a ser chamada

    @ Incremento contador de alarmes
    add r3, r3, #1
    @ Grava de volta o contador incrementado
    str r3, [r4]

    @ Move 0 para r0 indicando sucesso
    mov r0, #0

    end_set_alarm:
        ldmfd sp!, {r4-r5, pc}


back_to_r0:						@ 	(r0) : status register save 	SPSR
	@ Ainda em modo SUPERVISOR, desempilha os registradores salvos no inicio
	ldmfd sp!, {r11}		
	ldmfd sp!, {r7, r11, lr}

	@ Grava no registrador de status de retorno (status save) o argumento da syscall
	msr SPSR, r0 
	movs pc, lr 				@ Retorna para o lr que foi desempilhado (anterior a syscall)


delay_motors:					@ 	Nao tem parametros
	stmfd sp!, {r4, lr}

	mov r4, #0					@ Inicializa o iterador
	loop_delay_1:
		add r4, r4, #1			@ Adiciona 1
		cmp r4, #0x550			@ Compara com o maximo 0x1000
	bls loop_delay_1			@ Salta para o inicio caso nao acabou

	ldmfd sp!, {r4, pc}


delay_sonar:					@ 	Nao tem parametros
	stmfd sp!, {r4, lr}

	mov r4, #0x550				@ Inicializa o iterador com o valor maximo 0x1400
	loop_delay_2:
		sub r4, r4, #1			@ Subtrai 1
		cmp r4, #0				@ Compara com 0
	bhi loop_delay_2			@ Salta para o inicio caso nao seja 0

	ldmfd sp!, {r4, pc}

@ Interrupcoes nao tratadas
UNDEFINED_INSTRUCTION:
INSTRUCTION_ABORT_HANDLER:
DATA_ABORT_HANDLER:
FIQ_ABORT_HANDLER:
limbo_42:
	b limbo_42

@ Secao de Dados
@ @ @ @ @ @ @ @ @ @ @ @
.data

@ Tempo do sistema
system_time:
.word 0x0
 
@ Alarmes
.set MAX_ALARMS, 0x8
.set ALARMS_SIZE, 0x8

@ Numero de alarmes ativos
active_alarms:
.word 0x0

@ Vetor de alarmes
alarms_vect:
.space MAX_ALARMS * ALARMS_SIZE
 
@ Callbacks
.set MAX_CALLBACKS, 0x8
.set CALLBACKS_SIZE, 0xC

@ Numero de callbacks ativas
active_callbacks:
.word 0x0

@ Vetor de callbacks
callbacks_vect:
.space MAX_CALLBACKS * CALLBACKS_SIZE
 
@ Declaração das Stacks
 
.set DEFAULT_STACK_SIZE,        0x200
 
.set IRQ_STACK_SIZE,            DEFAULT_STACK_SIZE
.set SVC_STACK_SIZE,            0x300
.set SYS_STACK_SIZE,            DEFAULT_STACK_SIZE

STACK_IRQ_END:
.skip IRQ_STACK_SIZE
STACK_IRQ_BASE:
 
STACK_SYS_END:
.skip SYS_STACK_SIZE
STACK_SYS_BASE:
 
STACK_SVC_END:
.skip SVC_STACK_SIZE
STACK_SVC_BASE:
