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

    @Set interrupt table base address on coprocessor 15.
    ldr r0, =interrupt_vector
    mcr p15, 0, r0, c12, c0, 0

initialize_stacks:

	msr CPSR_c, FIQ_MODE_I_1_F_1 	@ FIQ mode, interuptions disnabled
	ldr sp, =STACK_FIQ_BASE			@ Initialize sp_FIQ

	msr CPSR_c, IRQ_MODE_I_1_F_1 	@ IRQ mode, interuptions disnabled
	ldr sp, =STACK_IRQ_BASE			@ Initialize sp_IRQ

	msr CPSR_c, ABT_MODE_I_1_F_1 	@ ABT mode, interuptions disnabled
	ldr sp, =STACK_ABT_BASE			@ Initialize sp_ABT

	msr CPSR_c, UND_MODE_I_1_F_1 	@ UND mode, interuptions disnabled
	ldr sp, =STACK_UND_BASE			@ Initialize sp_UND

	msr CPSR_c, SYS_MODE_I_1_F_1 	@ SYS mode, interuptions disnabled
	ldr sp, =STACK_SYS_BASE			@ Initialize sp_SYS

	mov r0, #SVC_MODE_I_1_F_1		@ Read the SVC_MODE_I_1_F_1 mask with 
@											Interuption Flags Disabled

	bic r0, #0b11000000				@ Enable interuptions I=0; F=0;
	msr CPSR_c, r0 					@ SVC mode, interuptions enabled
	ldr sp, =STACK_SVC_BASE			@ Initialize sp_SVC

set_gpt:
	.set TIME_SZ, 				0x64
	@ Constantes para os enderecos do GPT
	.set GPT_BASE, 				0x53FA0000
	.set GPT_CR, 				0x0
	.set GPT_PR, 				0x4
	.set GPT_SR,				0x8
	.set GPT_OCR1,				0x10
	.set GPT_IR,				0xC
	@ Valores a serem setados em GPT
	.set GPT_CR_val, 			0x41
	.set GPT_PR_val, 			0x0
	.set GPT_OCR1_val,			TIME_SZ
	.set GPT_IR_val,			0x1
	
	@ Carrega a base do GPT
	ldr r1, =GPT_BASE

	@ Habilitar e configurar o clock_src para periférico
	ldr r0, =GPT_CR_val
	str	r0, [r1, #GPT_CR]

	@ Zerar o prescaler (GPT_PR)
	ldr r0, =GPT_PR_val
	str	r0, [r1, #GPT_PR]
	@ 	Colocar em GPT_COR1 o valor que gera 
	@ a interrupção durante a contagem
	ldr r0, =GPT_OCR1_val
	str	r0, [r1, #GPT_OCR1]
	@ Habilitar a interrupção Output Compare Channel 1
	ldr r0, =GPT_IR_val
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

	@instrucao msr - habilita interrupcoes
	msr  CPSR_c, #0x13       @ SUPERVISOR mode, IRQ/FIQ enabled

set_gpio:
	@ Constantes para os enderecos do GPIO
	.set GPIO_BASE, 			0x53F84000
	.set GPIO_DR,				0x0
	.set GPIO_GDIR, 			0x4
	.set GPIO_PSR, 				0x8
	@ Constantes para os valores do GPIO
	.set GPIO_GDIR_val, 		0xFFFC003E



	@ Configurar entradas e saídas da GPIO
	ldr r0, =GPIO_GDIR_val
	str	r0, [r1, #GPIO_GDIR]


@ Tentativa de mudar para o modo usuário
CHANGE_TO_USER_MODE_IN_THE_START_POSITION:
	
	ldr r1, =USER_START_POSITION
	mov r0, #USR_MODE_I_1_F_1		@ Read the USR_MODE_I_1_F_1 mask with 
@											Interuption Flags Disabled

	bic r0, #0b11000000				@ Enable interuptions I=0; F=0;
	msr CPSR_c, r0 					@ USR mode, interuptions enabled
	mov pc, r1						@ Jump to user start position
	



IRQ_HANDLER:
		stmfd sp!, {r0, r2}

	@ 	Informa ao GPT que o  processador 
	@ já está ciente de que ocorreu a interrupção
	ldr r2, =GPT_BASE
	mov r0, #0x1
	str r0, [r2, #GPT_SR]



	@ Le o endereço do contador
	ldr r2, =system_time
	@ Carega o contador
	ldr r0, [r2]
	add r0, r0, #1
	@ Grava de volta o contador incrementado
	str r0,[r2]
		

		ldmfd sp!, {r0, r2}
		@ Ajusta o lr antes de retornar
		sub 	lr, lr, #4
		movs 	pc, lr

SVC_HANDLER:
		stmfd sp!, {r0-r12, lr}


	
	sub r7, r7, #16
	add pc, pc, r7, lsl #3
	mov r0, r0
	
	b read_sonar
	b end_svc_handler
	b register_proximity_callback 
	b end_svc_handler
	b set_motor_speed 
	b end_svc_handler
	b set_motors_speed
	b end_svc_handler
	b get_time
	b end_svc_handler
	b set_time
	b end_svc_handler
	b set_alarm

	end_svc_handler:
		ldmfd sp!, {r0-r12,lr}
		movs 	pc, lr



read_sonar:
	stmfd sp!, {r4-r12, lr}


	ldmfd sp!, {r4-r12, pc}


register_proximity_callback :
	stmfd sp!, {r4-r12, lr}


	ldmfd sp!, {r4-r12, pc}


set_motor_speed :
	stmfd sp!, {r4-r12, lr}


	ldmfd sp!, {r4-r12, pc}


set_motors_speed:
	stmfd sp!, {r4-r12, lr}


	ldmfd sp!, {r4-r12, pc}


get_time:
	stmfd sp!, {r4-r12, lr}


	ldmfd sp!, {r4-r12, pc}


set_time:
	stmfd sp!, {r4-r12, lr}


	ldmfd sp!, {r4-r12, pc}


set_alarm:
	stmfd sp!, {r4-r12, lr}


	ldmfd sp!, {r4-r12, pc}





.data
system_time:
.word 0x0
@ Declaração das Stacks

.org STACKS_START_POSITION

.set DEFAULT_STACK_SIZE, 	0x100

.set FIQ_STACK_SIZE, 		0x1
.set IRQ_STACK_SIZE, 		DEFAULT_STACK_SIZE
.set SVC_STACK_SIZE, 		DEFAULT_STACK_SIZE
.set ABT_STACK_SIZE, 		0x1
.set UND_STACK_SIZE, 		0x1
.set SYS_STACK_SIZE, 		DEFAULT_STACK_SIZE


STACK_FIQ_END: .skip FIQ_STACK_SIZE
STACK_FIQ_BASE:

STACK_IRQ_END: .skip IRQ_STACK_SIZE
STACK_IRQ_BASE:

STACK_ABT_END: .skip ABT_STACK_SIZE
STACK_ABT_BASE:

STACK_UND_END: .skip UND_STACK_SIZE
STACK_UND_BASE:

STACK_SYS_END: .skip SYS_STACK_SIZE
STACK_SYS_BASE:

STACK_SVC_END: .skip SVC_STACK_SIZE
STACK_SVC_BASE:

.text

UNDEFINED_INSTRUCTION:
INSTRUCTION_ABORT_HANDLER:
DATA_ABORT_HANDLER:
FIQ_ABORT_HANDLER:
limbo_42:
	b limbo_42

