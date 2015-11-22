.set USER_START_POSITION, 	0x77802000
.set STACKS_START_POSITION, 0x77852000

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

@ Modes with Interuption Flags Disabled
.set USR_MODE_I_1_F_1, 		0xD0
.set FIQ_MODE_I_1_F_1, 		0xD1
.set IRQ_MODE_I_1_F_1, 		0xD2
.set SVC_MODE_I_1_F_1, 		0xD3
.set ABT_MODE_I_1_F_1, 		0xD7
.set UND_MODE_I_1_F_1, 		0xDB
.set SYS_MODE_I_1_F_1, 		0xDF

RESET_HANDLER:

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

		
		@ Carrega a base do GPT
		ldr r1, =GPT_BASE

		@ Habilitar e configurar o clock_src para periférico
		ldr r0, =0x41
		str	r0, [r1, #GPT_CR]

		@ Zerar o prescaler (GPT_PR)
		ldr r0, =0x0
		str	r0, [r1, #GPT_PR]

		@ Colocar em GPT_COR1 o valor que gera 
		@ a interrupção durante a contagem
		ldr r0, =100
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


	@ Tentativa de mudar para o modo usuário
	CHANGE_TO_USER_MODE_IN_THE_START_POSITION:

		ldr r1, =USER_START_POSITION
		mov r0, #USR_MODE_I_1_F_1		@ Le a mascara USR_MODE_I_1_F_1 com 
										@ Flags de interrupcao desabilitadas
		bic r0, #0b11000000				@ Abilita interrupcoes na mascara I=0; F=0;
		msr CPSR_c, r0 					@ USR mode, interrupcoes abilitadas
		mov pc, r1						@ Pula para a posicao de inicio do usuario

IRQ_HANDLER:
	stmfd sp!, {r0, r2}
	@ Habilitar/Desabilitar interrupcoes

	@ Informa ao GPT que o  processador 
	@ já está ciente de que ocorreu a interrupção
	ldr r2, =GPT_BASE
	mov r0, #0x1
	str r0, [r2, #GPT_SR]


	@ Le o endereço do contador
	ldr r2, =system_time

	@ Carega o contador
	ldr r0, [r2]

	@ Incrementa o contador
	add r0, r0, #1

	@ Grava de volta o contador incrementado
	str r0, [r2]
	
	ldmfd sp!, {r0, r2}
	@ Ajusta o lr antes de retornar
	sub 	lr, lr, #4
	movs 	pc, lr

SVC_HANDLER:
	stmfd sp!, {r1-r12, lr}

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

	end_svc_handler:
		ldmfd 	sp!, {r1-r12, lr}
		movs 	pc, lr



read_sonar:						@ (r0) : unsigned char 	sonar_id, 
								@ (r1) : unsigned short* 	dist

	stmfd sp!, {r4-r12, lr}

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
	bl delay_sonar				@ Salta para o loop de espera

	@ TRIGGER <= 1; Delay
	orr r2, #0b10				@ Adiciona o valor 1 bit do trigger
	str	r2, [r3, #GPIO_DR] 		@ Grava em DR
	bl delay_sonar

	@ TRIGGER <= 0;
	bic r2, #0b10				@ Limpa o Trigger
	str	r2, [r3, #GPIO_DR] 		@ Grava em DR

	@ FLAG == 1 ?
	loop_flag:
		ldr r2, [r3, #GPIO_DR]	@ Carrega Valor de DR
		and r2, r2, #1			@ Compara flag com 1
		cmp r2, #1
		@ Nao
			@ Delay
		blne delay_sonar		@ Chama o delay enquanto flag != 1
		bne loop_flag			@ Repete o loop

	@ SIM
		@ Distancia <= Sonar_Data
	ldr r2, [r3, #GPIO_DR]		@ Carrega Valor de DR
	lsl r2, #14					@ Desloca os bits de r2 para esquerda e depois para
	lsr r2, #20					@ direita para manter apenas os bits da distancia
	
	mov r0, r2					@ Move a distancia para r0

	end_read_sonar:
		ldmfd sp!, {r4-r12, pc}


register_proximity_callback :	@ (r0) : unsigned char 	sensor_id, 
								@ (r1) : unsigned short 	dist_threshold, 
								@ (r2) : void (*f)()
	stmfd sp!, {r4-r12, lr}
	
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
    ldr r6, =callbacks_vect
    add r6, r6, r3, lsl #3
    str r1, [r6], #4
    str r0, [r6]

    @ Incremento contador de alarmes
    add r3, r3, #1
    @ Grava de volta o contador incrementado
    str r3,[r5]

	mov r0, #0
	end_register_proximity_callback:
		ldmfd sp!, {r4-r12, pc}


set_motor_speed:				@ (r0) : unsigned char 	id, 
								@ (r1) : unsigned char 	speed

	stmfd sp!, {r4-r12, lr}
	
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
	bl delay_100

	@ Move o valor 0 para r0 identificando a corretude da syscall
	mov r0, #0

	end_set_motor_speed:
		ldmfd sp!, {r4-r12, pc}


set_motors_speed:				@ (r0) : unsigned char 	spd_m0, 
								@ (r1) : unsigned char 	spd_m1
	stmfd sp!, {r4-r12, lr}

	@ Confere se as duas velocidades sao validas, retornando em r0
	@ -1 caso a primeira seja invalida e -2 caso a segunda
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
	bl delay_100

	@ Move 0 para r0 confirmando a validade da syscall
	mov r0, #0

	end_set_motors_speed:
		ldmfd sp!, {r4-r12, pc}


get_time:						@ 	Nao tem parametros
	stmfd sp!, {r4-r12, lr}

	ldr r0, =system_time		@ Pega o tempo do sistema e retorna para o usuario
	ldr r0, [r0]

	ldmfd sp!, {r4-r12, pc}


set_time:						@ 	(r0) : unsigned int 	t
	stmfd sp!, {r4-r12, lr}

	ldr r1, =system_time		@ Carrega o endereco da variavel do tempo do sistema
	str r0, [r1]				@ Guarda o novo valor

	ldmfd sp!, {r4-r12, pc}


set_alarm:						@ (r0) : void (*f)(), 
								@ (r1) : unsigned int time
	stmfd sp!, {r4-r12, lr}

	@ Conferir se os argumentos são válidos
	ldr r2, =MAX_ALARMS
	ldr r4, =active_alarms
	ldr r3, [r4]
	cmp r3, r2
	movhs r0, #0
	subhs r0, r0, #1
	bhs end_set_alarm
	ldr r2, =system_time
	ldr r2, [r2]
	cmp r1, r2 @ r1 = time; r2 = System Time
	movls r0, #0
	subls r0, r0, #2
	bls end_set_alarm

	@ Corpo da funcao
    ldr r5, =alarms_vect
    add r5, r5, r3, lsl #3
    str r1, [r5], #4
    str r0, [r5]

    @ Incremento contador de alarmes
    add r3, r3, #1
    @ Grava de volta o contador incrementado
    str r3,[r4]

    mov r0, #0
    end_set_alarm:
            ldmfd sp!, {r4-r12, pc}

delay_100:
stmfd sp!, {r4, lr}

	mov r4, #0
	loop_delay_1:
		cmp r4, #100
		add r4, r4, #1
	bhs loop_delay_1

ldmfd sp!, {r4, pc}

delay_sonar:
stmfd sp!, {r4, lr}

	mov r4, #0
	loop_delay_2:
		cmp r4, #2048
		add r4, r4, #1
	bhs loop_delay_2

ldmfd sp!, {r4, pc}

UNDEFINED_INSTRUCTION:
INSTRUCTION_ABORT_HANDLER:
DATA_ABORT_HANDLER:
FIQ_ABORT_HANDLER:
limbo_42:
	b limbo_42


.data

@ Tempo do sistema
system_time:
.word 0x0
 
@ Alarmes
.set MAX_ALARMS, 0x8
.set ALARMS_SIZE, 0x8
 
active_alarms:
.word 0x0
 
alarms_vect:
.space MAX_ALARMS * ALARMS_SIZE
 
@ Callbacks
.set MAX_CALLBACKS, 0x8
.set CALLBACKS_SIZE, 0xC
 
active_callbacks:
.word 0x0
 
callbacks_vect:
.space MAX_CALLBACKS * CALLBACKS_SIZE
 
@ Declaração das Stacks
 
.set DEFAULT_STACK_SIZE,        0x100
 
.set IRQ_STACK_SIZE,            DEFAULT_STACK_SIZE
.set SVC_STACK_SIZE,            DEFAULT_STACK_SIZE
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
