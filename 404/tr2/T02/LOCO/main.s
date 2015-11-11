	.arch armv5te
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"main.c"
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.text
.Ltext0:
	.comm	estate,1,1
	.align	2
	.global	_start
	.type	_start, %function
_start:
.LFB0:
	.file 1 "main.c"
	.loc 1 35 0
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI0:
	add	fp, sp, #4
.LCFI1:
	.loc 1 36 0
	bl	stop
.L2:
	.loc 1 39 0
	bl	folow_wall
	.loc 1 40 0
	b	.L2
.LFE0:
	.size	_start, .-_start
	.align	2
	.global	delay
	.type	delay, %function
delay:
.LFB1:
	.loc 1 45 0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
.LCFI2:
	add	fp, sp, #0
.LCFI3:
	sub	sp, sp, #12
.LCFI4:
	.loc 1 48 0
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L5
.L6:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L5:
	ldr	r2, [fp, #-8]
	ldr	r3, .L8
	cmp	r2, r3
	ble	.L6
	.loc 1 49 0
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.L9:
	.align	2
.L8:
	.word	9999
.LFE1:
	.size	delay, .-delay
	.align	2
	.global	folow_wall
	.type	folow_wall, %function
folow_wall:
.LFB2:
	.loc 1 50 0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI5:
	add	fp, sp, #4
.LCFI6:
	sub	sp, sp, #8
.LCFI7:
	.loc 1 52 0
	mov	r0, #0
	bl	read_sonar
	mov	r3, r0
	strh	r3, [fp, #-10]	@ movhi
	.loc 1 53 0
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	strh	r3, [fp, #-8]	@ movhi
	.loc 1 54 0
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	strh	r3, [fp, #-6]	@ movhi
	.loc 1 55 0
	ldrh	r2, [fp, #-10]
	ldr	r3, .L15
	cmp	r2, r3
	bhi	.L11
	.loc 1 56 0
	mov	r0, #10
	bl	turn_left
	b	.L14
.L11:
	.loc 1 57 0
	ldrh	r3, [fp, #-10]
	cmp	r3, #1024
	bls	.L13
	.loc 1 58 0
	mov	r0, #10
	bl	turn_right
	b	.L14
.L13:
	.loc 1 60 0
	mov	r0, #15
	bl	go_front
.L14:
	.loc 1 63 0
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L16:
	.align	2
.L15:
	.word	1023
.LFE2:
	.size	folow_wall, .-folow_wall
	.align	2
	.global	swerve
	.type	swerve, %function
swerve:
.LFB3:
	.loc 1 65 0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI8:
	add	fp, sp, #4
.LCFI9:
	sub	sp, sp, #8
.LCFI10:
	mov	r2, r0
	mov	r3, r1
	strh	r2, [fp, #-6]	@ movhi
	strh	r3, [fp, #-8]	@ movhi
	.loc 1 67 0
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	strh	r3, [fp, #-6]	@ movhi
	.loc 1 68 0
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	strh	r3, [fp, #-8]	@ movhi
	.loc 1 70 0
	ldrh	r2, [fp, #-6]
	ldr	r3, .L25
	cmp	r2, r3
	bls	.L18
	ldrh	r2, [fp, #-8]
	ldr	r3, .L25
	cmp	r2, r3
	bhi	.L19
.L18:
	.loc 1 72 0
	bl	stop
	.loc 1 77 0
	sub	r2, fp, #6
	sub	r3, fp, #8
	mov	r0, r2
	mov	r1, r3
	bl	get_mins
	.loc 1 79 0
	ldrh	r2, [fp, #-6]
	ldrh	r3, [fp, #-8]
	cmp	r2, r3
	bcs	.L20
.L21:
	.loc 1 82 0
	mov	r0, #10
	bl	turn_right
	.loc 1 84 0
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	strh	r3, [fp, #-6]	@ movhi
	.loc 1 85 0
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	strh	r3, [fp, #-8]	@ movhi
	.loc 1 86 0
	ldrh	r2, [fp, #-6]
	ldr	r3, .L25
	cmp	r2, r3
	bls	.L21
	ldrh	r2, [fp, #-8]
	ldr	r3, .L25
	cmp	r2, r3
	bls	.L21
	.loc 1 87 0
	bl	stop
	.loc 1 70 0
	b	.L24
.L20:
	.loc 1 92 0
	mov	r0, #10
	bl	turn_left
	.loc 1 94 0
	mov	r0, #3
	bl	read_sonar
	mov	r3, r0
	strh	r3, [fp, #-6]	@ movhi
	.loc 1 95 0
	mov	r0, #4
	bl	read_sonar
	mov	r3, r0
	strh	r3, [fp, #-8]	@ movhi
	.loc 1 96 0
	ldrh	r2, [fp, #-6]
	ldr	r3, .L25
	cmp	r2, r3
	bls	.L20
	ldrh	r2, [fp, #-8]
	ldr	r3, .L25
	cmp	r2, r3
	bls	.L20
	.loc 1 97 0
	bl	stop
	.loc 1 70 0
	b	.L24
.L19:
	.loc 1 101 0
	mov	r0, #15
	bl	go_front
.L24:
	.loc 1 103 0
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L26:
	.align	2
.L25:
	.word	1023
.LFE3:
	.size	swerve, .-swerve
	.align	2
	.global	get_mins
	.type	get_mins, %function
get_mins:
.LFB4:
	.loc 1 106 0
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI11:
	add	fp, sp, #4
.LCFI12:
	sub	sp, sp, #16
.LCFI13:
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	.loc 1 110 0
	mov	r3, #0
	strb	r3, [fp, #-7]
	b	.L28
.L30:
	.loc 1 111 0
	ldrb	r3, [fp, #-7]	@ zero_extendqisi2
	mov	r0, r3
	bl	read_sonar
	mov	r3, r0
	strh	r3, [fp, #-6]	@ movhi
	.loc 1 112 0
	ldr	r3, [fp, #-16]
	ldrh	r3, [r3, #0]
	ldrh	r2, [fp, #-6]
	cmp	r2, r3
	bcs	.L29
	.loc 1 113 0
	ldr	r3, [fp, #-16]
	ldrh	r2, [fp, #-6]	@ movhi
	strh	r2, [r3, #0]	@ movhi
.L29:
	.loc 1 110 0
	ldrb	r3, [fp, #-7]
	add	r3, r3, #1
	strb	r3, [fp, #-7]
.L28:
	ldrb	r3, [fp, #-7]	@ zero_extendqisi2
	cmp	r3, #2
	bls	.L30
	.loc 1 117 0
	mov	r3, #5
	strb	r3, [fp, #-7]
	b	.L31
.L33:
	.loc 1 118 0
	ldrb	r3, [fp, #-7]	@ zero_extendqisi2
	mov	r0, r3
	bl	read_sonar
	mov	r3, r0
	strh	r3, [fp, #-6]	@ movhi
	.loc 1 119 0
	ldr	r3, [fp, #-20]
	ldrh	r3, [r3, #0]
	ldrh	r2, [fp, #-6]
	cmp	r2, r3
	bcs	.L32
	.loc 1 120 0
	ldr	r3, [fp, #-20]
	ldrh	r2, [fp, #-6]	@ movhi
	strh	r2, [r3, #0]	@ movhi
.L32:
	.loc 1 117 0
	ldrb	r3, [fp, #-7]
	add	r3, r3, #1
	strb	r3, [fp, #-7]
.L31:
	ldrb	r3, [fp, #-7]	@ zero_extendqisi2
	cmp	r3, #7
	bls	.L33
	.loc 1 123 0
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.LFE4:
	.size	get_mins, .-get_mins
	.align	2
	.global	get_mins_reading_all
	.type	get_mins_reading_all, %function
get_mins_reading_all:
.LFB5:
	.loc 1 126 0
	@ args = 0, pretend = 0, frame = 80
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI14:
	add	fp, sp, #4
.LCFI15:
	sub	sp, sp, #80
.LCFI16:
	str	r0, [fp, #-80]
	str	r1, [fp, #-84]
	.loc 1 130 0
	sub	r3, fp, #72
	mov	r0, r3
	bl	read_sonars
	.loc 1 132 0
	mov	r3, #0
	strb	r3, [fp, #-5]
	b	.L36
.L37:
	.loc 1 133 0
	ldr	r3, [fp, #-80]
	ldrh	r3, [r3, #0]
	mov	r2, r3
	ldrb	r1, [fp, #-5]	@ zero_extendqisi2
	mvn	r3, #67
	mov	r1, r1, asl #2
	sub	r0, fp, #4
	add	r1, r0, r1
	add	r3, r1, r3
	ldr	r3, [r3, #0]
	cmp	r2, r3
	movcc	r3, r2
	mov	r3, r3, asl #16
	mov	r2, r3, lsr #16
	ldr	r3, [fp, #-80]
	strh	r2, [r3, #0]	@ movhi
	.loc 1 132 0
	ldrb	r3, [fp, #-5]
	add	r3, r3, #1
	strb	r3, [fp, #-5]
.L36:
	ldrb	r3, [fp, #-5]	@ zero_extendqisi2
	cmp	r3, #3
	bls	.L37
	.loc 1 136 0
	mov	r3, #4
	strb	r3, [fp, #-5]
	b	.L38
.L39:
	.loc 1 137 0
	ldr	r3, [fp, #-84]
	ldrh	r3, [r3, #0]
	mov	r2, r3
	ldrb	r1, [fp, #-5]	@ zero_extendqisi2
	mvn	r3, #67
	mov	r1, r1, asl #2
	sub	r0, fp, #4
	add	r1, r0, r1
	add	r3, r1, r3
	ldr	r3, [r3, #0]
	cmp	r2, r3
	movcc	r3, r2
	mov	r3, r3, asl #16
	mov	r2, r3, lsr #16
	ldr	r3, [fp, #-84]
	strh	r2, [r3, #0]	@ movhi
	.loc 1 136 0
	ldrb	r3, [fp, #-5]
	add	r3, r3, #1
	strb	r3, [fp, #-5]
.L38:
	ldrb	r3, [fp, #-5]	@ zero_extendqisi2
	cmp	r3, #7
	bls	.L39
	.loc 1 139 0
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.LFE5:
	.size	get_mins_reading_all, .-get_mins_reading_all
	.align	2
	.global	go_front
	.type	go_front, %function
go_front:
.LFB6:
	.loc 1 141 0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI17:
	add	fp, sp, #4
.LCFI18:
	sub	sp, sp, #8
.LCFI19:
	mov	r3, r0
	strb	r3, [fp, #-5]
	.loc 1 142 0
	ldrb	r2, [fp, #-5]	@ zero_extendqisi2
	ldrb	r3, [fp, #-5]	@ zero_extendqisi2
	mov	r0, r2
	mov	r1, r3
	bl	set_speed_motors
	.loc 1 143 0
	ldr	r3, .L43
	mov	r2, #3
	strb	r2, [r3, #0]
	.loc 1 144 0
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L44:
	.align	2
.L43:
	.word	estate
.LFE6:
	.size	go_front, .-go_front
	.align	2
	.global	turn_left
	.type	turn_left, %function
turn_left:
.LFB7:
	.loc 1 146 0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI20:
	add	fp, sp, #4
.LCFI21:
	sub	sp, sp, #8
.LCFI22:
	mov	r3, r0
	strb	r3, [fp, #-5]
	.loc 1 148 0
	ldr	r3, .L53
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L46
.L51:
	.word	.L47
	.word	.L46
	.word	.L49
	.word	.L50
.L50:
	.loc 1 150 0
	mov	r0, #0
	mov	r1, #1
	bl	set_speed_motor
	.loc 1 151 0
	b	.L46
.L49:
	.loc 1 156 0
	ldrb	r3, [fp, #-5]	@ zero_extendqisi2
	mov	r0, r3
	mov	r1, #0
	bl	set_speed_motors
	.loc 1 157 0
	b	.L46
.L47:
	.loc 1 159 0
	ldrb	r3, [fp, #-5]	@ zero_extendqisi2
	mov	r0, r3
	mov	r1, #0
	bl	set_speed_motor
.L46:
	.loc 1 162 0
	ldr	r3, .L53
	mov	r2, #1
	strb	r2, [r3, #0]
	.loc 1 163 0
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L54:
	.align	2
.L53:
	.word	estate
.LFE7:
	.size	turn_left, .-turn_left
	.align	2
	.global	turn_right
	.type	turn_right, %function
turn_right:
.LFB8:
	.loc 1 165 0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI23:
	add	fp, sp, #4
.LCFI24:
	sub	sp, sp, #8
.LCFI25:
	mov	r3, r0
	strb	r3, [fp, #-5]
	.loc 1 167 0
	ldr	r3, .L63
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #3
	ldrls	pc, [pc, r3, asl #2]
	b	.L56
.L61:
	.word	.L57
	.word	.L58
	.word	.L56
	.word	.L60
.L60:
	.loc 1 169 0
	mov	r0, #0
	mov	r1, #0
	bl	set_speed_motor
	.loc 1 170 0
	b	.L56
.L58:
	.loc 1 173 0
	ldrb	r3, [fp, #-5]	@ zero_extendqisi2
	mov	r0, #0
	mov	r1, r3
	bl	set_speed_motors
	.loc 1 174 0
	b	.L56
.L57:
	.loc 1 178 0
	ldrb	r3, [fp, #-5]	@ zero_extendqisi2
	mov	r0, r3
	mov	r1, #1
	bl	set_speed_motor
.L56:
	.loc 1 181 0
	ldr	r3, .L63
	mov	r2, #2
	strb	r2, [r3, #0]
	.loc 1 182 0
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L64:
	.align	2
.L63:
	.word	estate
.LFE8:
	.size	turn_right, .-turn_right
	.align	2
	.global	stop
	.type	stop, %function
stop:
.LFB9:
	.loc 1 184 0
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
.LCFI26:
	add	fp, sp, #4
.LCFI27:
	.loc 1 185 0
	mov	r0, #0
	mov	r1, #0
	bl	set_speed_motors
	.loc 1 186 0
	ldr	r3, .L67
	mov	r2, #0
	strb	r2, [r3, #0]
	.loc 1 187 0
	ldmfd	sp!, {fp, pc}
.L68:
	.align	2
.L67:
	.word	estate
.LFE9:
	.size	stop, .-stop
	.section	.debug_frame,"",%progbits
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x1
	.ascii	"\000"
	.uleb128 0x1
	.sleb128 -4
	.byte	0xe
	.byte	0xc
	.uleb128 0xd
	.uleb128 0x0
	.align	2
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.byte	0x4
	.4byte	.LCFI0-.LFB0
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI1-.LCFI0
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.byte	0x4
	.4byte	.LCFI2-.LFB1
	.byte	0xe
	.uleb128 0x4
	.byte	0x11
	.uleb128 0xb
	.sleb128 1
	.byte	0x4
	.4byte	.LCFI3-.LCFI2
	.byte	0xd
	.uleb128 0xb
	.align	2
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.byte	0x4
	.4byte	.LCFI5-.LFB2
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI6-.LCFI5
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.byte	0x4
	.4byte	.LCFI8-.LFB3
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI9-.LCFI8
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE6:
.LSFDE8:
	.4byte	.LEFDE8-.LASFDE8
.LASFDE8:
	.4byte	.Lframe0
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.byte	0x4
	.4byte	.LCFI11-.LFB4
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI12-.LCFI11
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE8:
.LSFDE10:
	.4byte	.LEFDE10-.LASFDE10
.LASFDE10:
	.4byte	.Lframe0
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.byte	0x4
	.4byte	.LCFI14-.LFB5
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI15-.LCFI14
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE10:
.LSFDE12:
	.4byte	.LEFDE12-.LASFDE12
.LASFDE12:
	.4byte	.Lframe0
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.byte	0x4
	.4byte	.LCFI17-.LFB6
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI18-.LCFI17
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE12:
.LSFDE14:
	.4byte	.LEFDE14-.LASFDE14
.LASFDE14:
	.4byte	.Lframe0
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.byte	0x4
	.4byte	.LCFI20-.LFB7
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI21-.LCFI20
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE14:
.LSFDE16:
	.4byte	.LEFDE16-.LASFDE16
.LASFDE16:
	.4byte	.Lframe0
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.byte	0x4
	.4byte	.LCFI23-.LFB8
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI24-.LCFI23
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE16:
.LSFDE18:
	.4byte	.LEFDE18-.LASFDE18
.LASFDE18:
	.4byte	.Lframe0
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.byte	0x4
	.4byte	.LCFI26-.LFB9
	.byte	0xe
	.uleb128 0x8
	.byte	0x11
	.uleb128 0xe
	.sleb128 1
	.byte	0x11
	.uleb128 0xb
	.sleb128 2
	.byte	0x4
	.4byte	.LCFI27-.LCFI26
	.byte	0xc
	.uleb128 0xb
	.uleb128 0x4
	.align	2
.LEFDE18:
	.text
.Letext0:
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LFB0-.Ltext0
	.4byte	.LCFI0-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0-.Ltext0
	.4byte	.LCFI1-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI1-.Ltext0
	.4byte	.LFE0-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST1:
	.4byte	.LFB1-.Ltext0
	.4byte	.LCFI2-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI2-.Ltext0
	.4byte	.LCFI3-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI3-.Ltext0
	.4byte	.LFE1-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST2:
	.4byte	.LFB2-.Ltext0
	.4byte	.LCFI5-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI5-.Ltext0
	.4byte	.LCFI6-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI6-.Ltext0
	.4byte	.LFE2-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST3:
	.4byte	.LFB3-.Ltext0
	.4byte	.LCFI8-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI8-.Ltext0
	.4byte	.LCFI9-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI9-.Ltext0
	.4byte	.LFE3-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST4:
	.4byte	.LFB4-.Ltext0
	.4byte	.LCFI11-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI11-.Ltext0
	.4byte	.LCFI12-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI12-.Ltext0
	.4byte	.LFE4-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST5:
	.4byte	.LFB5-.Ltext0
	.4byte	.LCFI14-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI14-.Ltext0
	.4byte	.LCFI15-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI15-.Ltext0
	.4byte	.LFE5-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST6:
	.4byte	.LFB6-.Ltext0
	.4byte	.LCFI17-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI17-.Ltext0
	.4byte	.LCFI18-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI18-.Ltext0
	.4byte	.LFE6-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST7:
	.4byte	.LFB7-.Ltext0
	.4byte	.LCFI20-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI20-.Ltext0
	.4byte	.LCFI21-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI21-.Ltext0
	.4byte	.LFE7-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST8:
	.4byte	.LFB8-.Ltext0
	.4byte	.LCFI23-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI23-.Ltext0
	.4byte	.LCFI24-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI24-.Ltext0
	.4byte	.LFE8-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
.LLST9:
	.4byte	.LFB9-.Ltext0
	.4byte	.LCFI26-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI26-.Ltext0
	.4byte	.LCFI27-.Ltext0
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI27-.Ltext0
	.4byte	.LFE9-.Ltext0
	.2byte	0x2
	.byte	0x7b
	.sleb128 4
	.4byte	0x0
	.4byte	0x0
	.section	.debug_info
	.4byte	0x259
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF11
	.byte	0x1
	.4byte	.LASF12
	.4byte	.LASF13
	.4byte	.Ltext0
	.4byte	.Letext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.4byte	.LASF14
	.byte	0x1
	.byte	0x1
	.byte	0x9
	.4byte	0x42
	.uleb128 0x3
	.ascii	"S\000"
	.sleb128 0
	.uleb128 0x3
	.ascii	"L\000"
	.sleb128 1
	.uleb128 0x3
	.ascii	"R\000"
	.sleb128 2
	.uleb128 0x3
	.ascii	"F\000"
	.sleb128 3
	.byte	0x0
	.uleb128 0x4
	.byte	0x1
	.4byte	.LASF15
	.byte	0x1
	.byte	0x23
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.4byte	.LLST0
	.uleb128 0x5
	.byte	0x1
	.4byte	.LASF0
	.byte	0x1
	.byte	0x2c
	.4byte	.LFB1
	.4byte	.LFE1
	.4byte	.LLST1
	.4byte	0x7c
	.uleb128 0x6
	.ascii	"i\000"
	.byte	0x1
	.byte	0x2e
	.4byte	0x7c
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0x0
	.uleb128 0x7
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x5
	.byte	0x1
	.4byte	.LASF1
	.byte	0x1
	.byte	0x32
	.4byte	.LFB2
	.4byte	.LFE2
	.4byte	.LLST2
	.4byte	0xc3
	.uleb128 0x6
	.ascii	"s0\000"
	.byte	0x1
	.byte	0x33
	.4byte	0xc3
	.byte	0x2
	.byte	0x91
	.sleb128 -14
	.uleb128 0x6
	.ascii	"s3\000"
	.byte	0x1
	.byte	0x33
	.4byte	0xc3
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.uleb128 0x6
	.ascii	"s4\000"
	.byte	0x1
	.byte	0x33
	.4byte	0xc3
	.byte	0x2
	.byte	0x91
	.sleb128 -10
	.byte	0x0
	.uleb128 0x8
	.byte	0x2
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x9
	.byte	0x1
	.4byte	.LASF3
	.byte	0x1
	.byte	0x41
	.byte	0x1
	.4byte	.LFB3
	.4byte	.LFE3
	.4byte	.LLST3
	.4byte	0xfe
	.uleb128 0xa
	.ascii	"s3\000"
	.byte	0x1
	.byte	0x41
	.4byte	0xc3
	.byte	0x2
	.byte	0x91
	.sleb128 -10
	.uleb128 0xa
	.ascii	"s4\000"
	.byte	0x1
	.byte	0x41
	.4byte	0xc3
	.byte	0x2
	.byte	0x91
	.sleb128 -12
	.byte	0x0
	.uleb128 0x9
	.byte	0x1
	.4byte	.LASF4
	.byte	0x1
	.byte	0x6a
	.byte	0x1
	.4byte	.LFB4
	.4byte	.LFE4
	.4byte	.LLST4
	.4byte	0x14a
	.uleb128 0xa
	.ascii	"l\000"
	.byte	0x1
	.byte	0x6a
	.4byte	0x14a
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xa
	.ascii	"r\000"
	.byte	0x1
	.byte	0x6a
	.4byte	0x14a
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x6
	.ascii	"i\000"
	.byte	0x1
	.byte	0x6b
	.4byte	0x150
	.byte	0x2
	.byte	0x91
	.sleb128 -11
	.uleb128 0x6
	.ascii	"aux\000"
	.byte	0x1
	.byte	0x6c
	.4byte	0xc3
	.byte	0x2
	.byte	0x91
	.sleb128 -10
	.byte	0x0
	.uleb128 0xb
	.byte	0x4
	.4byte	0xc3
	.uleb128 0x8
	.byte	0x1
	.byte	0x8
	.4byte	.LASF5
	.uleb128 0x9
	.byte	0x1
	.4byte	.LASF6
	.byte	0x1
	.byte	0x7e
	.byte	0x1
	.4byte	.LFB5
	.4byte	.LFE5
	.4byte	.LLST5
	.4byte	0x1a4
	.uleb128 0xa
	.ascii	"l\000"
	.byte	0x1
	.byte	0x7e
	.4byte	0x14a
	.byte	0x3
	.byte	0x91
	.sleb128 -84
	.uleb128 0xa
	.ascii	"r\000"
	.byte	0x1
	.byte	0x7e
	.4byte	0x14a
	.byte	0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x6
	.ascii	"i\000"
	.byte	0x1
	.byte	0x7f
	.4byte	0x150
	.byte	0x2
	.byte	0x91
	.sleb128 -9
	.uleb128 0x6
	.ascii	"s\000"
	.byte	0x1
	.byte	0x80
	.4byte	0x1a4
	.byte	0x3
	.byte	0x91
	.sleb128 -76
	.byte	0x0
	.uleb128 0xc
	.4byte	0x1b7
	.4byte	0x1b4
	.uleb128 0xd
	.4byte	0x1b4
	.byte	0xf
	.byte	0x0
	.uleb128 0xe
	.byte	0x4
	.byte	0x7
	.uleb128 0x8
	.byte	0x4
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x9
	.byte	0x1
	.4byte	.LASF8
	.byte	0x1
	.byte	0x8d
	.byte	0x1
	.4byte	.LFB6
	.4byte	.LFE6
	.4byte	.LLST6
	.4byte	0x1e6
	.uleb128 0xa
	.ascii	"vel\000"
	.byte	0x1
	.byte	0x8d
	.4byte	0x150
	.byte	0x2
	.byte	0x91
	.sleb128 -9
	.byte	0x0
	.uleb128 0x9
	.byte	0x1
	.4byte	.LASF9
	.byte	0x1
	.byte	0x92
	.byte	0x1
	.4byte	.LFB7
	.4byte	.LFE7
	.4byte	.LLST7
	.4byte	0x20e
	.uleb128 0xa
	.ascii	"vel\000"
	.byte	0x1
	.byte	0x92
	.4byte	0x150
	.byte	0x2
	.byte	0x91
	.sleb128 -9
	.byte	0x0
	.uleb128 0x9
	.byte	0x1
	.4byte	.LASF10
	.byte	0x1
	.byte	0xa5
	.byte	0x1
	.4byte	.LFB8
	.4byte	.LFE8
	.4byte	.LLST8
	.4byte	0x236
	.uleb128 0xa
	.ascii	"vel\000"
	.byte	0x1
	.byte	0xa5
	.4byte	0x150
	.byte	0x2
	.byte	0x91
	.sleb128 -9
	.byte	0x0
	.uleb128 0xf
	.byte	0x1
	.4byte	.LASF16
	.byte	0x1
	.byte	0xb8
	.4byte	.LFB9
	.4byte	.LFE9
	.4byte	.LLST9
	.uleb128 0x10
	.4byte	.LASF17
	.byte	0x1
	.byte	0x9
	.4byte	0x25
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	estate
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x28
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x2e
	.byte	0x0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0x2e
	.byte	0x0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",%progbits
	.4byte	0xa1
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x25d
	.4byte	0x42
	.ascii	"_start\000"
	.4byte	0x57
	.ascii	"delay\000"
	.4byte	0x83
	.ascii	"folow_wall\000"
	.4byte	0xca
	.ascii	"swerve\000"
	.4byte	0xfe
	.ascii	"get_mins\000"
	.4byte	0x157
	.ascii	"get_mins_reading_all\000"
	.4byte	0x1be
	.ascii	"go_front\000"
	.4byte	0x1e6
	.ascii	"turn_left\000"
	.4byte	0x20e
	.ascii	"turn_right\000"
	.4byte	0x236
	.ascii	"stop\000"
	.4byte	0x24a
	.ascii	"estate\000"
	.4byte	0x0
	.section	.debug_aranges,"",%progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.2byte	0x0
	.2byte	0x0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0x0
	.4byte	0x0
	.section	.debug_str,"MS",%progbits,1
.LASF7:
	.ascii	"unsigned int\000"
.LASF5:
	.ascii	"unsigned char\000"
.LASF12:
	.ascii	"main.c\000"
.LASF13:
	.ascii	"/home/ec2014/ra156331/Documents/T02/LOCO\000"
.LASF9:
	.ascii	"turn_left\000"
.LASF17:
	.ascii	"estate\000"
.LASF11:
	.ascii	"GNU C 4.4.3\000"
.LASF8:
	.ascii	"go_front\000"
.LASF4:
	.ascii	"get_mins\000"
.LASF1:
	.ascii	"folow_wall\000"
.LASF16:
	.ascii	"stop\000"
.LASF2:
	.ascii	"short unsigned int\000"
.LASF6:
	.ascii	"get_mins_reading_all\000"
.LASF10:
	.ascii	"turn_right\000"
.LASF3:
	.ascii	"swerve\000"
.LASF0:
	.ascii	"delay\000"
.LASF15:
	.ascii	"_start\000"
.LASF14:
	.ascii	"Estate\000"
	.ident	"GCC: (GNU) 4.4.3"
	.section	.note.GNU-stack,"",%progbits
