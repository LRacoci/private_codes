
knrl:     file format elf32-littlearm


Disassembly of section .iv:

778005e0 <_start>:


Disassembly of section .text:

reset_handler:
ldr	sp, [pc, #132]	; 7780068c <_bootmessage+0x14>
msr	CPSR_c, #223	; 0xdf
ldr	sp, [pc, #128]	; 77800690 <_bootmessage+0x18>
msr	CPSR_c, #209	; 0xd1
ldr	sp, [pc, #124]	; 77800694 <_bootmessage+0x1c>
msr	CPSR_c, #210	; 0xd2
ldr	sp, [pc, #120]	; 77800698 <_bootmessage+0x20>
msr	CPSR_c, #215	; 0xd7
ldr	sp, [pc, #116]	; 7780069c <_bootmessage+0x24>
msr	CPSR_c, #219	; 0xdb
ldr	sp, [pc, #112]	; 778006a0 <_bootmessage+0x28>
ldr	r0, [pc, #112]	; 778006a4 <_bootmessage+0x2c>
77800630:	ee0c0f10 	mcr	15, 0, r0, cr12, cr0, {0}
77800634:	e321f01f 	msr	CPSR_c, #31	; 0x1f
77800638:	ea000000 	b	77800640 <system_init>

7780063c <data_abort_handler>:
7780063c:	e1b0f00e 	movs	pc, lr

77800640 <system_init>:
77800640:	eb000032 	bl	77800710 <configure_tzic>
77800644:	eb000019 	bl	778006b0 <configure_gpt>
77800648:	eb0001b8 	bl	77800d30 <configure_uart>
7780064c:	eb000227 	bl	77800ef0 <configure_gpio>
77800650:	eb000003 	bl	77800664 <print_boot_message>
77800654:	e321f010 	msr	CPSR_c, #16	; 0x10
77800658:	e59f0048 	ldr	r0, [pc, #72]	; 778006a8 <_bootmessage+0x30>
7780065c:	e12fff30 	blx	r0

77800660 <loop>:
77800660:	eafffffe 	b	77800660 <loop>

77800664 <print_boot_message>:
77800664:	e92d4000 	push	{lr}
77800668:	e28f0008 	add	r0, pc, #8	; 0x8
7780066c:	e3a01010 	mov	r1, #16	; 0x10
77800670:	eb0001c7 	bl	77800d94 <write>
77800674:	e8bd8000 	pop	{pc}

77800678 <_bootmessage>:
77800678:	746f6f42 	strbtvc	r6, [pc], #3906	; 77800680 <_bootmessage+0x8>
7780067c:	44206465 	strtmi	r6, [r0], #-1125
77800680:	796d6d75 	stmdbvc	sp!, {r0, r2, r4, r5, r6, r8, sl, fp, sp, lr}^
77800684:	0a2e534f 	beq	783953c8 <__bss_end__+0xb92f68>
77800688:	00000020 	andeq	r0, r0, r0, lsr #32
7780068c:	77701000 	.word	0x77701000
77800690:	77706000 	.word	0x77706000
77800694:	77705000 	.word	0x77705000
77800698:	77704000 	.word	0x77704000
7780069c:	77703000 	.word	0x77703000
778006a0:	77702000 	.word	0x77702000
778006a4:	778005e0 	.word	0x778005e0
778006a8:	77802000 	.word	0x77802000
778006ac:	00000000 	.word	0x00000000

778006b0 <configure_gpt>:
778006b0:	e59f101c 	ldr	r1, [pc, #28]	; 778006d4 <_sys_gpt_base_ptr>
778006b4:	e5810000 	str	r0, [r1]
778006b8:	e0200000 	eor	r0, r0, r0
778006bc:	e5810004 	str	r0, [r1, #4]
778006c0:	e3a00c01 	mov	r0, #256	; 0x100
778006c4:	e5810010 	str	r0, [r1, #16]
778006c8:	e3a00001 	mov	r0, #1	; 0x1
778006cc:	e581000c 	str	r0, [r1, #12]
778006d0:	e1a0f00e 	mov	pc, lr

778006d4 <_sys_gpt_base_ptr>:
778006d4:	53fa0000 	.word	0x53fa0000

778006d8 <int39>:
778006d8:	e92d4000 	push	{lr}
778006dc:	e59f101c 	ldr	r1, [pc, #28]	; 77800700 <_gpt_gpt_base_ptr>
778006e0:	e0200000 	eor	r0, r0, r0
778006e4:	e2400001 	sub	r0, r0, #1	; 0x1
778006e8:	e5810008 	str	r0, [r1, #8]
778006ec:	e59f0010 	ldr	r0, [pc, #16]	; 77800704 <_gpt_handler_ptr>
778006f0:	e3300000 	teq	r0, #0	; 0x0
778006f4:	0a000000 	beq	778006fc <_gpt_handle_exit>
778006f8:	e12fff30 	blx	r0

778006fc <_gpt_handle_exit>:
778006fc:	e8bd8000 	pop	{pc}

77800700 <_gpt_gpt_base_ptr>:
77800700:	53fa0000 	.word	0x53fa0000

77800704 <_gpt_handler_ptr>:
77800704:	00000000 	.word	0x00000000
77800708:	e1a00000 	.word	0xe1a00000
7780070c:	e1a00000 	.word	0xe1a00000

77800710 <configure_tzic>:
77800710:	e59f106c 	ldr	r1, [pc, #108]	; 77800784 <_sys_tzic_base_ptr>
77800714:	e0222002 	eor	r2, r2, r2
77800718:	e2420001 	sub	r0, r2, #1	; 0x1
7780071c:	e5810080 	str	r0, [r1, #128]
77800720:	e5810084 	str	r0, [r1, #132]
77800724:	e5810088 	str	r0, [r1, #136]
77800728:	e581008c 	str	r0, [r1, #140]
7780072c:	e3a00102 	mov	r0, #-2147483648	; 0x80000000
77800730:	e5810100 	str	r0, [r1, #256]
77800734:	e3a00080 	mov	r0, #128	; 0x80
77800738:	e5810104 	str	r0, [r1, #260]
7780073c:	e3a00000 	mov	r0, #0	; 0x0
77800740:	e5810108 	str	r0, [r1, #264]
77800744:	e581010c 	str	r0, [r1, #268]
77800748:	e591041c 	ldr	r0, [r1, #1052]
7780074c:	e3c004ff 	bic	r0, r0, #-16777216	; 0xff000000
77800750:	e3a02001 	mov	r2, #1	; 0x1
77800754:	e1800c02 	orr	r0, r0, r2, lsl #24
77800758:	e581041c 	str	r0, [r1, #1052]
7780075c:	e5910424 	ldr	r0, [r1, #1060]
77800760:	e3c004ff 	bic	r0, r0, #-16777216	; 0xff000000
77800764:	e3a02001 	mov	r2, #1	; 0x1
77800768:	e1800c02 	orr	r0, r0, r2, lsl #24
7780076c:	e5810424 	str	r0, [r1, #1060]
77800770:	e0200000 	eor	r0, r0, r0
77800774:	e581000c 	str	r0, [r1, #12]
77800778:	e3a00001 	mov	r0, #1	; 0x1
7780077c:	e5810000 	str	r0, [r1]
77800780:	e1a0f00e 	mov	pc, lr

77800784 <_sys_tzic_base_ptr>:
77800784:	0fffc000 	.word	0x0fffc000

77800788 <irq_handler>:
77800788:	e24ee004 	sub	lr, lr, #4	; 0x4
7780078c:	e92d4000 	push	{lr}
77800790:	e14fe000 	mrs	lr, SPSR
77800794:	e92d43e0 	push	{r5, r6, r7, r8, r9, lr}
77800798:	e59f90b8 	ldr	r9, [pc, #184]	; 77800858 <_irq_tzic_base_ptr>
7780079c:	e5995d80 	ldr	r5, [r9, #3456]
778007a0:	e5996d84 	ldr	r6, [r9, #3460]
778007a4:	e5997d88 	ldr	r7, [r9, #3464]
778007a8:	e5998d8c 	ldr	r8, [r9, #3468]
778007ac:	e92d0200 	push	{r9}
778007b0:	e3a09000 	mov	r9, #0	; 0x0
778007b4:	e3350000 	teq	r5, #0	; 0x0
778007b8:	1a00000c 	bne	778007f0 <_irq_found>
778007bc:	e1a05006 	mov	r5, r6
778007c0:	e2899020 	add	r9, r9, #32	; 0x20
778007c4:	e3350000 	teq	r5, #0	; 0x0
778007c8:	1a000008 	bne	778007f0 <_irq_found>
778007cc:	e1a05007 	mov	r5, r7
778007d0:	e2899020 	add	r9, r9, #32	; 0x20
778007d4:	e3350000 	teq	r5, #0	; 0x0
778007d8:	1a000004 	bne	778007f0 <_irq_found>
778007dc:	e1a05008 	mov	r5, r8
778007e0:	e2899020 	add	r9, r9, #32	; 0x20
778007e4:	e3350000 	teq	r5, #0	; 0x0
778007e8:	1a000000 	bne	778007f0 <_irq_found>
778007ec:	ea000016 	b	7780084c <_irq_quit>

778007f0 <_irq_found>:
778007f0:	e3350001 	teq	r5, #1	; 0x1
778007f4:	0a000002 	beq	77800804 <_irq_bit_found>
778007f8:	e2899001 	add	r9, r9, #1	; 0x1
778007fc:	e1a050a5 	lsr	r5, r5, #1
77800800:	eafffffa 	b	778007f0 <_irq_found>

77800804 <_irq_bit_found>:
77800804:	e1a05009 	mov	r5, r9
77800808:	e8bd0200 	pop	{r9}
7780080c:	e2896b01 	add	r6, r9, #1024	; 0x400
77800810:	e7d66005 	ldrb	r6, [r6, r5]
77800814:	e599700c 	ldr	r7, [r9, #12]
77800818:	e92d0080 	push	{r7}
7780081c:	e589600c 	str	r6, [r9, #12]
77800820:	e321f01f 	msr	CPSR_c, #31	; 0x1f
77800824:	e92d400f 	push	{r0, r1, r2, r3, lr}
77800828:	e28f602c 	add	r6, pc, #44	; 0x2c
7780082c:	e1a05105 	lsl	r5, r5, #2
77800830:	e0866005 	add	r6, r6, r5
77800834:	e12fff36 	blx	r6
77800838:	e8bd400f 	pop	{r0, r1, r2, r3, lr}
7780083c:	e321f092 	msr	CPSR_c, #146	; 0x92
77800840:	e8bd0080 	pop	{r7}
77800844:	e59f500c 	ldr	r5, [pc, #12]	; 77800858 <_irq_tzic_base_ptr>
77800848:	e585700c 	str	r7, [r5, #12]

7780084c <_irq_quit>:
7780084c:	e8bd43e0 	pop	{r5, r6, r7, r8, r9, lr}
77800850:	e169f00e 	msr	SPSR_fc, lr
77800854:	e8fd8000 	ldm	sp!, {pc}^

77800858 <_irq_tzic_base_ptr>:
77800858:	0fffc000 	.word	0x0fffc000

7780085c <interrupt_vector>:
7780085c:	eaffffff 	b	77800860 <interrupt_vector+0x4>
77800860:	eaffffff 	b	77800864 <interrupt_vector+0x8>
77800864:	eaffffff 	b	77800868 <interrupt_vector+0xc>
77800868:	eaffffff 	b	7780086c <interrupt_vector+0x10>
7780086c:	eaffffff 	b	77800870 <interrupt_vector+0x14>
77800870:	eaffffff 	b	77800874 <interrupt_vector+0x18>
77800874:	eaffffff 	b	77800878 <interrupt_vector+0x1c>
77800878:	eaffffff 	b	7780087c <interrupt_vector+0x20>
7780087c:	eaffffff 	b	77800880 <interrupt_vector+0x24>
77800880:	eaffffff 	b	77800884 <interrupt_vector+0x28>
77800884:	eaffffff 	b	77800888 <interrupt_vector+0x2c>
77800888:	eaffffff 	b	7780088c <interrupt_vector+0x30>
7780088c:	eaffffff 	b	77800890 <interrupt_vector+0x34>
77800890:	eaffffff 	b	77800894 <interrupt_vector+0x38>
77800894:	eaffffff 	b	77800898 <interrupt_vector+0x3c>
77800898:	eaffffff 	b	7780089c <interrupt_vector+0x40>
7780089c:	eaffffff 	b	778008a0 <interrupt_vector+0x44>
778008a0:	eaffffff 	b	778008a4 <interrupt_vector+0x48>
778008a4:	eaffffff 	b	778008a8 <interrupt_vector+0x4c>
778008a8:	eaffffff 	b	778008ac <interrupt_vector+0x50>
778008ac:	eaffffff 	b	778008b0 <interrupt_vector+0x54>
778008b0:	eaffffff 	b	778008b4 <interrupt_vector+0x58>
778008b4:	eaffffff 	b	778008b8 <interrupt_vector+0x5c>
778008b8:	eaffffff 	b	778008bc <interrupt_vector+0x60>
778008bc:	eaffffff 	b	778008c0 <interrupt_vector+0x64>
778008c0:	eaffffff 	b	778008c4 <interrupt_vector+0x68>
778008c4:	eaffffff 	b	778008c8 <interrupt_vector+0x6c>
778008c8:	eaffffff 	b	778008cc <interrupt_vector+0x70>
778008cc:	eaffffff 	b	778008d0 <interrupt_vector+0x74>
778008d0:	eaffffff 	b	778008d4 <interrupt_vector+0x78>
778008d4:	eaffffff 	b	778008d8 <interrupt_vector+0x7c>
778008d8:	ea000167 	b	77800e7c <int31>
778008dc:	eaffffff 	b	778008e0 <interrupt_vector+0x84>
778008e0:	eaffffff 	b	778008e4 <interrupt_vector+0x88>
778008e4:	eaffffff 	b	778008e8 <interrupt_vector+0x8c>
778008e8:	eaffffff 	b	778008ec <interrupt_vector+0x90>
778008ec:	eaffffff 	b	778008f0 <interrupt_vector+0x94>
778008f0:	eaffffff 	b	778008f4 <interrupt_vector+0x98>
778008f4:	eaffffff 	b	778008f8 <interrupt_vector+0x9c>
778008f8:	eaffff76 	b	778006d8 <int39>
778008fc:	eaffffff 	b	77800900 <interrupt_vector+0xa4>
77800900:	eaffffff 	b	77800904 <interrupt_vector+0xa8>
77800904:	eaffffff 	b	77800908 <interrupt_vector+0xac>
77800908:	eaffffff 	b	7780090c <interrupt_vector+0xb0>
7780090c:	eaffffff 	b	77800910 <interrupt_vector+0xb4>
77800910:	eaffffff 	b	77800914 <interrupt_vector+0xb8>
77800914:	eaffffff 	b	77800918 <interrupt_vector+0xbc>
77800918:	eaffffff 	b	7780091c <interrupt_vector+0xc0>
7780091c:	eaffffff 	b	77800920 <interrupt_vector+0xc4>
77800920:	eaffffff 	b	77800924 <interrupt_vector+0xc8>
77800924:	eaffffff 	b	77800928 <interrupt_vector+0xcc>
77800928:	eaffffff 	b	7780092c <interrupt_vector+0xd0>
7780092c:	eaffffff 	b	77800930 <interrupt_vector+0xd4>
77800930:	eaffffff 	b	77800934 <interrupt_vector+0xd8>
77800934:	eaffffff 	b	77800938 <interrupt_vector+0xdc>
77800938:	eaffffff 	b	7780093c <interrupt_vector+0xe0>
7780093c:	eaffffff 	b	77800940 <interrupt_vector+0xe4>
77800940:	eaffffff 	b	77800944 <interrupt_vector+0xe8>
77800944:	eaffffff 	b	77800948 <interrupt_vector+0xec>
77800948:	eaffffff 	b	7780094c <interrupt_vector+0xf0>
7780094c:	eaffffff 	b	77800950 <interrupt_vector+0xf4>
77800950:	eaffffff 	b	77800954 <interrupt_vector+0xf8>
77800954:	eaffffff 	b	77800958 <interrupt_vector+0xfc>
77800958:	eaffffff 	b	7780095c <interrupt_vector+0x100>
7780095c:	eaffffff 	b	77800960 <interrupt_vector+0x104>
77800960:	eaffffff 	b	77800964 <interrupt_vector+0x108>
77800964:	eaffffff 	b	77800968 <interrupt_vector+0x10c>
77800968:	eaffffff 	b	7780096c <interrupt_vector+0x110>
7780096c:	eaffffff 	b	77800970 <interrupt_vector+0x114>
77800970:	eaffffff 	b	77800974 <interrupt_vector+0x118>
77800974:	eaffffff 	b	77800978 <interrupt_vector+0x11c>
77800978:	eaffffff 	b	7780097c <interrupt_vector+0x120>
7780097c:	eaffffff 	b	77800980 <interrupt_vector+0x124>
77800980:	eaffffff 	b	77800984 <interrupt_vector+0x128>
77800984:	eaffffff 	b	77800988 <interrupt_vector+0x12c>
77800988:	eaffffff 	b	7780098c <interrupt_vector+0x130>
7780098c:	eaffffff 	b	77800990 <interrupt_vector+0x134>
77800990:	eaffffff 	b	77800994 <interrupt_vector+0x138>
77800994:	eaffffff 	b	77800998 <interrupt_vector+0x13c>
77800998:	eaffffff 	b	7780099c <interrupt_vector+0x140>
7780099c:	eaffffff 	b	778009a0 <interrupt_vector+0x144>
778009a0:	eaffffff 	b	778009a4 <interrupt_vector+0x148>
778009a4:	eaffffff 	b	778009a8 <interrupt_vector+0x14c>
778009a8:	eaffffff 	b	778009ac <interrupt_vector+0x150>
778009ac:	eaffffff 	b	778009b0 <interrupt_vector+0x154>
778009b0:	eaffffff 	b	778009b4 <interrupt_vector+0x158>
778009b4:	eaffffff 	b	778009b8 <interrupt_vector+0x15c>
778009b8:	eaffffff 	b	778009bc <interrupt_vector+0x160>
778009bc:	eaffffff 	b	778009c0 <interrupt_vector+0x164>
778009c0:	eaffffff 	b	778009c4 <interrupt_vector+0x168>
778009c4:	eaffffff 	b	778009c8 <interrupt_vector+0x16c>
778009c8:	eaffffff 	b	778009cc <interrupt_vector+0x170>
778009cc:	eaffffff 	b	778009d0 <interrupt_vector+0x174>
778009d0:	eaffffff 	b	778009d4 <interrupt_vector+0x178>
778009d4:	eaffffff 	b	778009d8 <interrupt_vector+0x17c>
778009d8:	eaffffff 	b	778009dc <interrupt_vector+0x180>
778009dc:	eaffffff 	b	778009e0 <interrupt_vector+0x184>
778009e0:	eaffffff 	b	778009e4 <interrupt_vector+0x188>
778009e4:	eaffffff 	b	778009e8 <interrupt_vector+0x18c>
778009e8:	eaffffff 	b	778009ec <interrupt_vector+0x190>
778009ec:	eaffffff 	b	778009f0 <interrupt_vector+0x194>
778009f0:	eaffffff 	b	778009f4 <interrupt_vector+0x198>
778009f4:	eaffffff 	b	778009f8 <interrupt_vector+0x19c>
778009f8:	eaffffff 	b	778009fc <interrupt_vector+0x1a0>
778009fc:	eaffffff 	b	77800a00 <interrupt_vector+0x1a4>
77800a00:	eaffffff 	b	77800a04 <interrupt_vector+0x1a8>
77800a04:	eaffffff 	b	77800a08 <interrupt_vector+0x1ac>
77800a08:	eaffffff 	b	77800a0c <interrupt_vector+0x1b0>
77800a0c:	eaffffff 	b	77800a10 <interrupt_vector+0x1b4>
77800a10:	eaffffff 	b	77800a14 <interrupt_vector+0x1b8>
77800a14:	eaffffff 	b	77800a18 <interrupt_vector+0x1bc>
77800a18:	eaffffff 	b	77800a1c <interrupt_vector+0x1c0>
77800a1c:	eaffffff 	b	77800a20 <interrupt_vector+0x1c4>
77800a20:	eaffffff 	b	77800a24 <interrupt_vector+0x1c8>
77800a24:	eaffffff 	b	77800a28 <interrupt_vector+0x1cc>
77800a28:	eaffffff 	b	77800a2c <interrupt_vector+0x1d0>
77800a2c:	eaffffff 	b	77800a30 <interrupt_vector+0x1d4>
77800a30:	eaffffff 	b	77800a34 <interrupt_vector+0x1d8>
77800a34:	eaffffff 	b	77800a38 <interrupt_vector+0x1dc>
77800a38:	eaffffff 	b	77800a3c <interrupt_vector+0x1e0>
77800a3c:	eaffffff 	b	77800a40 <interrupt_vector+0x1e4>
77800a40:	eaffffff 	b	77800a44 <interrupt_vector+0x1e8>
77800a44:	eaffffff 	b	77800a48 <interrupt_vector+0x1ec>
77800a48:	eaffffff 	b	77800a4c <interrupt_vector+0x1f0>
77800a4c:	eaffffff 	b	77800a50 <interrupt_vector+0x1f4>
77800a50:	eaffffff 	b	77800a54 <interrupt_vector+0x1f8>
77800a54:	eaffffff 	b	77800a58 <interrupt_vector+0x1fc>
77800a58:	eaffffff 	b	77800a5c <interrupt_vector+0x200>
77800a5c:	e1a00000 	nop			(mov r0,r0)

77800a60 <svc_handler>:
77800a60:	e92d4000 	push	{lr}
77800a64:	e14fe000 	mrs	lr, SPSR
77800a68:	e92d4000 	push	{lr}
77800a6c:	e321f01f 	msr	CPSR_c, #31	; 0x1f
77800a70:	e3570080 	cmp	r7, #128	; 0x80
77800a74:	ab000009 	blge	77800aa0 <unimplemented_syscall>
77800a78:	e92d0003 	push	{r0, r1}
77800a7c:	e28f007c 	add	r0, pc, #124	; 0x7c
77800a80:	e1a01107 	lsl	r1, r7, #2
77800a84:	e0807001 	add	r7, r0, r1
77800a88:	e8bd0003 	pop	{r0, r1}
77800a8c:	e12fff37 	blx	r7
77800a90:	e321f0d3 	msr	CPSR_c, #211	; 0xd3
77800a94:	e8bd4000 	pop	{lr}
77800a98:	e169f00e 	msr	SPSR_fc, lr
77800a9c:	e8fd8000 	ldm	sp!, {pc}^

77800aa0 <unimplemented_syscall>:
77800aa0:	e92d4000 	push	{lr}
77800aa4:	e28f0008 	add	r0, pc, #8	; 0x8
77800aa8:	e3a0103d 	mov	r1, #61	; 0x3d
77800aac:	eb0000b8 	bl	77800d94 <write>

77800ab0 <_panic>:
77800ab0:	eafffffe 	b	77800ab0 <_panic>

77800ab4 <_unmessage>:
77800ab4:	6d6d7544 	cfstr64vs	mvdx7, [sp, #-272]!
77800ab8:	20534f79 	subscs	r4, r3, r9, ror pc
77800abc:	6f727265 	svcvs	0x00727265
77800ac0:	75203a72 	strvc	r3, [r0, #-2674]!
77800ac4:	706d696e 	rsbvc	r6, sp, lr, ror #18
77800ac8:	656d656c 	strbvs	r6, [sp, #-1388]!
77800acc:	6465746e 	strbtvs	r7, [r5], #-1134
77800ad0:	73797320 	cmnvc	r9, #-2147483648	; 0x80000000
77800ad4:	6c6c6163 	stfvse	f6, [ip], #-396
77800ad8:	6e45202e 	cdpvs	0, 4, cr2, cr5, cr14, {1}
77800adc:	69726574 	ldmdbvs	r2!, {r2, r4, r5, r6, r8, sl, sp, lr}^
77800ae0:	7020676e 	eorvc	r6, r0, lr, ror #14
77800ae4:	63696e61 	cmnvs	r9, #1552	; 0x610
77800ae8:	646f6d20 	strbtvs	r6, [pc], #3360	; 77800af0 <_unmessage+0x3c>
77800aec:	293a2065 	ldmdbcs	sl!, {r0, r2, r5, r6, sp}
77800af0:	0000000a 	andeq	r0, r0, sl
77800af4:	e1a00000 	nop			(mov r0,r0)
77800af8:	e1a00000 	nop			(mov r0,r0)
77800afc:	e1a00000 	nop			(mov r0,r0)

77800b00 <syscall_vector>:
77800b00:	ea000089 	b	77800d2c <sys0>
77800b04:	ea00007d 	b	77800d00 <exit_sys_entry>
77800b08:	ea000087 	b	77800d2c <sys0>
77800b0c:	ea00007c 	b	77800d04 <read_sys_entry>
77800b10:	ea00007e 	b	77800d10 <sys4>
77800b14:	ea000084 	b	77800d2c <sys0>
77800b18:	ea000083 	b	77800d2c <sys0>
77800b1c:	ea000082 	b	77800d2c <sys0>
77800b20:	ea000081 	b	77800d2c <sys0>
77800b24:	ea000080 	b	77800d2c <sys0>
77800b28:	ea00007f 	b	77800d2c <sys0>
77800b2c:	ea00007e 	b	77800d2c <sys0>
77800b30:	ea00007d 	b	77800d2c <sys0>
77800b34:	ea00007c 	b	77800d2c <sys0>
77800b38:	ea00007b 	b	77800d2c <sys0>
77800b3c:	ea00007a 	b	77800d2c <sys0>
77800b40:	ea000079 	b	77800d2c <sys0>
77800b44:	ea000078 	b	77800d2c <sys0>
77800b48:	ea000077 	b	77800d2c <sys0>
77800b4c:	ea000076 	b	77800d2c <sys0>
77800b50:	ea000075 	b	77800d2c <sys0>
77800b54:	ea000074 	b	77800d2c <sys0>
77800b58:	ea000073 	b	77800d2c <sys0>
77800b5c:	ea000072 	b	77800d2c <sys0>
77800b60:	ea000071 	b	77800d2c <sys0>
77800b64:	ea000070 	b	77800d2c <sys0>
77800b68:	ea00006f 	b	77800d2c <sys0>
77800b6c:	ea00006e 	b	77800d2c <sys0>
77800b70:	ea00006d 	b	77800d2c <sys0>
77800b74:	ea00006c 	b	77800d2c <sys0>
77800b78:	ea00006b 	b	77800d2c <sys0>
77800b7c:	ea00006a 	b	77800d2c <sys0>
77800b80:	ea000069 	b	77800d2c <sys0>
77800b84:	ea000068 	b	77800d2c <sys0>
77800b88:	ea000067 	b	77800d2c <sys0>
77800b8c:	ea000066 	b	77800d2c <sys0>
77800b90:	ea000065 	b	77800d2c <sys0>
77800b94:	ea000064 	b	77800d2c <sys0>
77800b98:	ea000063 	b	77800d2c <sys0>
77800b9c:	ea000062 	b	77800d2c <sys0>
77800ba0:	ea000061 	b	77800d2c <sys0>
77800ba4:	ea000060 	b	77800d2c <sys0>
77800ba8:	ea00005f 	b	77800d2c <sys0>
77800bac:	ea00005e 	b	77800d2c <sys0>
77800bb0:	ea00005d 	b	77800d2c <sys0>
77800bb4:	ea00005c 	b	77800d2c <sys0>
77800bb8:	ea00005b 	b	77800d2c <sys0>
77800bbc:	ea00005a 	b	77800d2c <sys0>
77800bc0:	ea000059 	b	77800d2c <sys0>
77800bc4:	ea000058 	b	77800d2c <sys0>
77800bc8:	ea000057 	b	77800d2c <sys0>
77800bcc:	ea000056 	b	77800d2c <sys0>
77800bd0:	ea000055 	b	77800d2c <sys0>
77800bd4:	ea000054 	b	77800d2c <sys0>
77800bd8:	ea000053 	b	77800d2c <sys0>
77800bdc:	ea000052 	b	77800d2c <sys0>
77800be0:	ea000051 	b	77800d2c <sys0>
77800be4:	ea000050 	b	77800d2c <sys0>
77800be8:	ea00004f 	b	77800d2c <sys0>
77800bec:	ea00004e 	b	77800d2c <sys0>
77800bf0:	ea00004d 	b	77800d2c <sys0>
77800bf4:	ea00004c 	b	77800d2c <sys0>
77800bf8:	ea00004b 	b	77800d2c <sys0>
77800bfc:	ea00004a 	b	77800d2c <sys0>
77800c00:	ea000049 	b	77800d2c <sys0>
77800c04:	ea000048 	b	77800d2c <sys0>
77800c08:	ea000047 	b	77800d2c <sys0>
77800c0c:	ea000046 	b	77800d2c <sys0>
77800c10:	ea000045 	b	77800d2c <sys0>
77800c14:	ea000044 	b	77800d2c <sys0>
77800c18:	ea000043 	b	77800d2c <sys0>
77800c1c:	ea000042 	b	77800d2c <sys0>
77800c20:	ea000041 	b	77800d2c <sys0>
77800c24:	ea000040 	b	77800d2c <sys0>
77800c28:	ea00003f 	b	77800d2c <sys0>
77800c2c:	ea00003e 	b	77800d2c <sys0>
77800c30:	ea00003d 	b	77800d2c <sys0>
77800c34:	ea00003c 	b	77800d2c <sys0>
77800c38:	ea00003b 	b	77800d2c <sys0>
77800c3c:	ea00003a 	b	77800d2c <sys0>
77800c40:	ea000039 	b	77800d2c <sys0>
77800c44:	ea000038 	b	77800d2c <sys0>
77800c48:	ea000037 	b	77800d2c <sys0>
77800c4c:	ea000036 	b	77800d2c <sys0>
77800c50:	ea000035 	b	77800d2c <sys0>
77800c54:	ea000034 	b	77800d2c <sys0>
77800c58:	ea000033 	b	77800d2c <sys0>
77800c5c:	ea000032 	b	77800d2c <sys0>
77800c60:	ea000031 	b	77800d2c <sys0>
77800c64:	ea000030 	b	77800d2c <sys0>
77800c68:	ea00002f 	b	77800d2c <sys0>
77800c6c:	ea00002e 	b	77800d2c <sys0>
77800c70:	ea00002d 	b	77800d2c <sys0>
77800c74:	ea00002c 	b	77800d2c <sys0>
77800c78:	ea00002b 	b	77800d2c <sys0>
77800c7c:	ea00002a 	b	77800d2c <sys0>
77800c80:	ea000029 	b	77800d2c <sys0>
77800c84:	ea000028 	b	77800d2c <sys0>
77800c88:	ea000027 	b	77800d2c <sys0>
77800c8c:	ea000026 	b	77800d2c <sys0>
77800c90:	ea000025 	b	77800d2c <sys0>
77800c94:	ea000024 	b	77800d2c <sys0>
77800c98:	ea000023 	b	77800d2c <sys0>
77800c9c:	ea000022 	b	77800d2c <sys0>
77800ca0:	ea000021 	b	77800d2c <sys0>
77800ca4:	ea000020 	b	77800d2c <sys0>
77800ca8:	ea00001f 	b	77800d2c <sys0>
77800cac:	ea00001e 	b	77800d2c <sys0>
77800cb0:	ea00001d 	b	77800d2c <sys0>
77800cb4:	ea00001c 	b	77800d2c <sys0>
77800cb8:	ea00001b 	b	77800d2c <sys0>
77800cbc:	ea00001a 	b	77800d2c <sys0>
77800cc0:	ea000019 	b	77800d2c <sys0>
77800cc4:	ea000018 	b	77800d2c <sys0>
77800cc8:	ea000017 	b	77800d2c <sys0>
77800ccc:	ea000016 	b	77800d2c <sys0>
77800cd0:	ea000015 	b	77800d2c <sys0>
77800cd4:	ea000014 	b	77800d2c <sys0>
77800cd8:	ea000013 	b	77800d2c <sys0>
77800cdc:	ea000012 	b	77800d2c <sys0>
77800ce0:	ea000011 	b	77800d2c <sys0>
77800ce4:	ea000010 	b	77800d2c <sys0>
77800ce8:	ea00000f 	b	77800d2c <sys0>
77800cec:	ea00000e 	b	77800d2c <sys0>
77800cf0:	ea000009 	b	77800d1c <sys124>
77800cf4:	ea000009 	b	77800d20 <sys125>
77800cf8:	ea000009 	b	77800d24 <sys126>
77800cfc:	ea000009 	b	77800d28 <sys127>

77800d00 <exit_sys_entry>:
77800d00:	eafffffe 	b	77800d00 <exit_sys_entry>

77800d04 <read_sys_entry>:
77800d04:	e1a00001 	mov	r0, r1
77800d08:	e1a01002 	mov	r1, r2
77800d0c:	ea000010 	b	77800d54 <read>

77800d10 <sys4>:
77800d10:	e1a00001 	mov	r0, r1
77800d14:	e1a01002 	mov	r1, r2
77800d18:	ea00001d 	b	77800d94 <write>

77800d1c <sys124>:
77800d1c:	ea0000b5 	b	77800ff8 <write_motors>

77800d20 <sys125>:
77800d20:	ea00007d 	b	77800f1c <read_sonar>

77800d24 <sys126>:
77800d24:	ea00009d 	b	77800fa0 <write_motor1>

77800d28 <sys127>:
77800d28:	ea0000a7 	b	77800fcc <write_motor2>

77800d2c <sys0>:
77800d2c:	eaffff5b 	b	77800aa0 <unimplemented_syscall>

77800d30 <configure_uart>:
77800d30:	e59f1018 	ldr	r1, [pc, #24]	; 77800d50 <_sys_uart_base_ptr>
77800d34:	e3a00027 	mov	r0, #39	; 0x27
77800d38:	e3800901 	orr	r0, r0, #16384	; 0x4000
77800d3c:	e5810084 	str	r0, [r1, #132]
77800d40:	e3a00001 	mov	r0, #1	; 0x1
77800d44:	e3800c22 	orr	r0, r0, #8704	; 0x2200
77800d48:	e5810080 	str	r0, [r1, #128]
77800d4c:	e1a0f00e 	mov	pc, lr

77800d50 <_sys_uart_base_ptr>:
77800d50:	53fbc000 	.word	0x53fbc000

77800d54 <read>:
77800d54:	e92d40f0 	push	{r4, r5, r6, r7, lr}
77800d58:	e59f4180 	ldr	r4, [pc, #384]	; 77800ee0 <irq_uart_transmit+0x4>
77800d5c:	e3a06000 	mov	r6, #0	; 0x0

77800d60 <_read_loop>:
77800d60:	e1560001 	cmp	r6, r1
77800d64:	aa000008 	bge	77800d8c <_read_end>

77800d68 <_read_poll>:
77800d68:	e5945098 	ldr	r5, [r4, #152]
77800d6c:	e2055001 	and	r5, r5, #1	; 0x1
77800d70:	e3550001 	cmp	r5, #1	; 0x1
77800d74:	1afffffb 	bne	77800d68 <_read_poll>
77800d78:	e5947000 	ldr	r7, [r4]
77800d7c:	e20770ff 	and	r7, r7, #255	; 0xff
77800d80:	e7c07006 	strb	r7, [r0, r6]
77800d84:	e2866001 	add	r6, r6, #1	; 0x1
77800d88:	eafffff4 	b	77800d60 <_read_loop>

77800d8c <_read_end>:
77800d8c:	e1a00006 	mov	r0, r6
77800d90:	e8bd80f0 	pop	{r4, r5, r6, r7, pc}

77800d94 <write>:
77800d94:	e92d40f0 	push	{r4, r5, r6, r7, lr}
77800d98:	e59f4140 	ldr	r4, [pc, #320]	; 77800ee0 <irq_uart_transmit+0x4>
77800d9c:	e3a06000 	mov	r6, #0	; 0x0

77800da0 <__write_loop>:
77800da0:	e1560001 	cmp	r6, r1
77800da4:	aafffff8 	bge	77800d8c <_read_end>

77800da8 <_write_poll>:
77800da8:	e5945094 	ldr	r5, [r4, #148]
77800dac:	e1a056a5 	lsr	r5, r5, #13
77800db0:	e2055001 	and	r5, r5, #1	; 0x1
77800db4:	e3550001 	cmp	r5, #1	; 0x1
77800db8:	1afffffa 	bne	77800da8 <_write_poll>
77800dbc:	e7d07006 	ldrb	r7, [r0, r6]
77800dc0:	e20770ff 	and	r7, r7, #255	; 0xff
77800dc4:	e5c47040 	strb	r7, [r4, #64]
77800dc8:	e2866001 	add	r6, r6, #1	; 0x1
77800dcc:	eafffff3 	b	77800da0 <__write_loop>

77800dd0 <_write_end>:
77800dd0:	e1a00006 	mov	r0, r6
77800dd4:	e8bd80f0 	pop	{r4, r5, r6, r7, pc}

77800dd8 <write2>:
77800dd8:	e92d4030 	push	{r4, r5, lr}
77800ddc:	e1a04000 	mov	r4, r0
77800de0:	e1a05001 	mov	r5, r1
77800de4:	eb000007 	bl	77800e08 <busy_wait_for_write_cnt>
77800de8:	e59f0010 	ldr	r0, [pc, #16]	; 77800e00 <_wr_write_buffer_ptr_ptr>
77800dec:	e5804000 	str	r4, [r0]
77800df0:	e59f000c 	ldr	r0, [pc, #12]	; 77800e04 <_wr_write_cnt_ptr>
77800df4:	e5805000 	str	r5, [r0]
77800df8:	eb000012 	bl	77800e48 <enable_trdy>
77800dfc:	e8bd8030 	pop	{r4, r5, pc}

77800e00 <_wr_write_buffer_ptr_ptr>:
77800e00:	77802454 	.word	0x77802454

77800e04 <_wr_write_cnt_ptr>:
77800e04:	77802458 	.word	0x77802458

77800e08 <busy_wait_for_write_cnt>:
77800e08:	e59f000c 	ldr	r0, [pc, #12]	; 77800e1c <_bw_write_cnt_ptr>

77800e0c <_bw_w_loop>:
77800e0c:	e5901000 	ldr	r1, [r0]
77800e10:	e3310000 	teq	r1, #0	; 0x0
77800e14:	1afffffc 	bne	77800e0c <_bw_w_loop>
77800e18:	e1a0f00e 	mov	pc, lr

77800e1c <_bw_write_cnt_ptr>:
77800e1c:	77802458 	.word	0x77802458

77800e20 <check_tx>:
77800e20:	e59f001c 	ldr	r0, [pc, #28]	; 77800e44 <_check_uart_base_ptr>
77800e24:	e5900094 	ldr	r0, [r0, #148]
77800e28:	e2000a02 	and	r0, r0, #8192	; 0x2000
77800e2c:	e3300000 	teq	r0, #0	; 0x0
77800e30:	1a000001 	bne	77800e3c <_check_ok>
77800e34:	e0200000 	eor	r0, r0, r0
77800e38:	e1a0f00e 	mov	pc, lr

77800e3c <_check_ok>:
77800e3c:	e3a00001 	mov	r0, #1	; 0x1
77800e40:	e1a0f00e 	mov	pc, lr

77800e44 <_check_uart_base_ptr>:
77800e44:	53fbc000 	.word	0x53fbc000

77800e48 <enable_trdy>:
77800e48:	e59f000c 	ldr	r0, [pc, #12]	; 77800e5c <_en_trdy_uart_base_ptr>
77800e4c:	e5901080 	ldr	r1, [r0, #128]
77800e50:	e3811a02 	orr	r1, r1, #8192	; 0x2000
77800e54:	e5801080 	str	r1, [r0, #128]
77800e58:	e1a0f00e 	mov	pc, lr

77800e5c <_en_trdy_uart_base_ptr>:
77800e5c:	53fbc000 	.word	0x53fbc000

77800e60 <disable_trdy>:
77800e60:	e59f0010 	ldr	r0, [pc, #16]	; 77800e78 <_dis_trdy_uart_base_ptr>
77800e64:	e5901080 	ldr	r1, [r0, #128]
77800e68:	e3e02a02 	mvn	r2, #8192	; 0x2000
77800e6c:	e0011002 	and	r1, r1, r2
77800e70:	e5801080 	str	r1, [r0, #128]
77800e74:	e1a0f00e 	mov	pc, lr

77800e78 <_dis_trdy_uart_base_ptr>:
77800e78:	53fbc000 	.word	0x53fbc000

77800e7c <int31>:
77800e7c:	e1a0f00e 	mov	pc, lr

77800e80 <handle_uart_interrupt>:
77800e80:	e92d4030 	push	{r4, r5, lr}
77800e84:	e59f1048 	ldr	r1, [pc, #72]	; 77800ed4 <_uart_uart_base_ptr>
77800e88:	e5910094 	ldr	r0, [r1, #148]
77800e8c:	e2000c02 	and	r0, r0, #512	; 0x200
77800e90:	e3300000 	teq	r0, #0	; 0x0
77800e94:	0a000003 	beq	77800ea8 <_int31_test_TXDY>
77800e98:	e1a04000 	mov	r4, r0
77800e9c:	e1a05001 	mov	r5, r1
77800ea0:	eb00000c 	bl	77800ed8 <irq_uart_receive>
77800ea4:	e5854094 	str	r4, [r5, #148]

77800ea8 <_int31_test_TXDY>:
77800ea8:	e59f1024 	ldr	r1, [pc, #36]	; 77800ed4 <_uart_uart_base_ptr>
77800eac:	e5910094 	ldr	r0, [r1, #148]
77800eb0:	e2000a02 	and	r0, r0, #8192	; 0x2000
77800eb4:	e3300000 	teq	r0, #0	; 0x0
77800eb8:	0a000003 	beq	77800ecc <_int31_exit>
77800ebc:	e1a04000 	mov	r4, r0
77800ec0:	e1a05001 	mov	r5, r1
77800ec4:	eb000004 	bl	77800edc <irq_uart_transmit>
77800ec8:	e5854094 	str	r4, [r5, #148]

77800ecc <_int31_exit>:
77800ecc:	e8bd4030 	pop	{r4, r5, lr}
77800ed0:	e1a0f00e 	mov	pc, lr

77800ed4 <_uart_uart_base_ptr>:
77800ed4:	53fbc000 	.word	0x53fbc000

77800ed8 <irq_uart_receive>:
77800ed8:	e1a0f00e 	mov	pc, lr

77800edc <irq_uart_transmit>:
77800edc:	e1a0f00e 	mov	pc, lr
77800ee0:	53fbc000 	.word	0x53fbc000
77800ee4:	e1a00000 	.word	0xe1a00000
77800ee8:	e1a00000 	.word	0xe1a00000
77800eec:	e1a00000 	.word	0xe1a00000

77800ef0 <configure_gpio>:
77800ef0:	e59f0140 	ldr	r0, [pc, #320]	; 77801038 <DELAY+0x4>
77800ef4:	e59f1140 	ldr	r1, [pc, #320]	; 7780103c <DELAY+0x8>
77800ef8:	e5810004 	str	r0, [r1, #4]
77800efc:	e3a00000 	mov	r0, #0	; 0x0
77800f00:	e5810000 	str	r0, [r1]
77800f04:	e581000c 	str	r0, [r1, #12]
77800f08:	e5810010 	str	r0, [r1, #16]
77800f0c:	e5810014 	str	r0, [r1, #20]
77800f10:	e5810018 	str	r0, [r1, #24]
77800f14:	e581001c 	str	r0, [r1, #28]
77800f18:	e1a0f00e 	mov	pc, lr

77800f1c <read_sonar>:
77800f1c:	e92d4ff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
77800f20:	e59f1114 	ldr	r1, [pc, #276]	; 7780103c <DELAY+0x8>
77800f24:	e5912000 	ldr	r2, [r1]
77800f28:	e3a0301f 	mov	r3, #31	; 0x1f
77800f2c:	e1a03083 	lsl	r3, r3, #1
77800f30:	e0034100 	and	r4, r3, r0, lsl #2
77800f34:	e1e05003 	mvn	r5, r3
77800f38:	e0022005 	and	r2, r2, r5
77800f3c:	e1822004 	orr	r2, r2, r4
77800f40:	e5812000 	str	r2, [r1]
77800f44:	e59f30e8 	ldr	r3, [pc, #232]	; 77801034 <DELAY>

77800f48 <_loop_wait_1>:
77800f48:	e2533001 	subs	r3, r3, #1	; 0x1
77800f4c:	1afffffd 	bne	77800f48 <_loop_wait_1>
77800f50:	e2222002 	eor	r2, r2, #2	; 0x2
77800f54:	e5812000 	str	r2, [r1]
77800f58:	e59f30d4 	ldr	r3, [pc, #212]	; 77801034 <DELAY>

77800f5c <_loop_wait_2>:
77800f5c:	e2533001 	subs	r3, r3, #1	; 0x1
77800f60:	1afffffd 	bne	77800f5c <_loop_wait_2>
77800f64:	e2222002 	eor	r2, r2, #2	; 0x2
77800f68:	e5812000 	str	r2, [r1]
77800f6c:	e59f30c0 	ldr	r3, [pc, #192]	; 77801034 <DELAY>

77800f70 <_loop_wait_3>:
77800f70:	e2533001 	subs	r3, r3, #1	; 0x1
77800f74:	1afffffd 	bne	77800f70 <_loop_wait_3>

77800f78 <_loop_pooling>:
77800f78:	e5912000 	ldr	r2, [r1]
77800f7c:	e3120001 	tst	r2, #1	; 0x1
77800f80:	1a000003 	bne	77800f94 <_end>
77800f84:	e59f30a8 	ldr	r3, [pc, #168]	; 77801034 <DELAY>

77800f88 <_loop_wait_4>:
77800f88:	e2533001 	subs	r3, r3, #1	; 0x1
77800f8c:	1afffffd 	bne	77800f88 <_loop_wait_4>
77800f90:	eafffff8 	b	77800f78 <_loop_pooling>

77800f94 <_end>:
77800f94:	e59f00a4 	ldr	r0, [pc, #164]	; 77801040 <DELAY+0xc>
77800f98:	e0000322 	and	r0, r0, r2, lsr #6
77800f9c:	e8bd8ff0 	pop	{r4, r5, r6, r7, r8, r9, sl, fp, pc}

77800fa0 <write_motor1>:
77800fa0:	e92d4ff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
77800fa4:	e59f1090 	ldr	r1, [pc, #144]	; 7780103c <DELAY+0x8>
77800fa8:	e3a0203f 	mov	r2, #63	; 0x3f
77800fac:	e1a02982 	lsl	r2, r2, #19
77800fb0:	e0023980 	and	r3, r2, r0, lsl #19
77800fb4:	e1e02002 	mvn	r2, r2
77800fb8:	e5910000 	ldr	r0, [r1]
77800fbc:	e0000002 	and	r0, r0, r2
77800fc0:	e1800003 	orr	r0, r0, r3
77800fc4:	e5810000 	str	r0, [r1]
77800fc8:	e8bd8ff0 	pop	{r4, r5, r6, r7, r8, r9, sl, fp, pc}

77800fcc <write_motor2>:
77800fcc:	e92d4ff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
77800fd0:	e59f1064 	ldr	r1, [pc, #100]	; 7780103c <DELAY+0x8>
77800fd4:	e3a0203f 	mov	r2, #63	; 0x3f
77800fd8:	e1a02d02 	lsl	r2, r2, #26
77800fdc:	e0023d00 	and	r3, r2, r0, lsl #26
77800fe0:	e1e02002 	mvn	r2, r2
77800fe4:	e5910000 	ldr	r0, [r1]
77800fe8:	e0000002 	and	r0, r0, r2
77800fec:	e1800003 	orr	r0, r0, r3
77800ff0:	e5810000 	str	r0, [r1]
77800ff4:	e8bd8ff0 	pop	{r4, r5, r6, r7, r8, r9, sl, fp, pc}

77800ff8 <write_motors>:
77800ff8:	e92d4ff0 	push	{r4, r5, r6, r7, r8, r9, sl, fp, lr}
77800ffc:	e59f2038 	ldr	r2, [pc, #56]	; 7780103c <DELAY+0x8>
77801000:	e3a0303f 	mov	r3, #63	; 0x3f
77801004:	e1a04983 	lsl	r4, r3, #19
77801008:	e1844d03 	orr	r4, r4, r3, lsl #26
7780100c:	e1e04004 	mvn	r4, r4
77801010:	e0000003 	and	r0, r0, r3
77801014:	e0011003 	and	r1, r1, r3
77801018:	e1a03980 	lsl	r3, r0, #19
7780101c:	e1833d01 	orr	r3, r3, r1, lsl #26
77801020:	e5920000 	ldr	r0, [r2]
77801024:	e0000004 	and	r0, r0, r4
77801028:	e1800003 	orr	r0, r0, r3
7780102c:	e5820000 	str	r0, [r2]
77801030:	e8bd8ff0 	pop	{r4, r5, r6, r7, r8, r9, sl, fp, pc}

77801034 <DELAY>:
77801034:	00001388 	.word	0x00001388
77801038:	fffc003e 	.word	0xfffc003e
7780103c:	53f84000 	.word	0x53f84000
77801040:	00000fff 	.word	0x00000fff
77801044:	e1a00000 	.word	0xe1a00000
77801048:	e1a00000 	.word	0xe1a00000
7780104c:	e1a00000 	.word	0xe1a00000

Disassembly of section .data:

77802050 <__data_start>:
	...

77802450 <read_cnt>:
77802450:	00000000 	.word	0x00000000

77802454 <write_buffer_ptr>:
77802454:	00000000 	.word	0x00000000

77802458 <write_cnt>:
	...

Disassembly of section .debug_aranges:

00000000 <.debug_aranges>:
   0:	00000024 	andeq	r0, r0, r4, lsr #32
   4:	00000002 	andeq	r0, r0, r2
   8:	00040000 	andeq	r0, r4, r0
   c:	00000000 	andeq	r0, r0, r0
  10:	778005e0 	strvc	r0, [r0, r0, ror #11]
  14:	00000020 	andeq	r0, r0, r0, lsr #32
  18:	77800600 	strvc	r0, [r0, r0, lsl #12]
  1c:	000000ac 	andeq	r0, r0, ip, lsr #1
	...
  28:	0000001c 	andeq	r0, r0, ip, lsl r0
  2c:	006c0002 	rsbeq	r0, ip, r2
  30:	00040000 	andeq	r0, r4, r0
  34:	00000000 	andeq	r0, r0, r0
  38:	778006b0 	undefined
  3c:	00000058 	andeq	r0, r0, r8, asr r0
	...
  48:	0000001c 	andeq	r0, r0, ip, lsl r0
  4c:	00db0002 	sbcseq	r0, fp, r2
  50:	00040000 	andeq	r0, r4, r0
  54:	00000000 	andeq	r0, r0, r0
  58:	77800710 	usada8vc	r0, r0, r7, r0
  5c:	0000034c 	andeq	r0, r0, ip, asr #6
	...
  68:	0000001c 	andeq	r0, r0, ip, lsl r0
  6c:	014a0002 	cmpeq	sl, r2
  70:	00040000 	andeq	r0, r4, r0
  74:	00000000 	andeq	r0, r0, r0
  78:	77800a60 	strvc	r0, [r0, r0, ror #20]
  7c:	000002d0 	ldrdeq	r0, [r0], -r0
	...
  88:	0000001c 	andeq	r0, r0, ip, lsl r0
  8c:	01be0002 	undefined instruction 0x01be0002
  90:	00040000 	andeq	r0, r4, r0
  94:	00000000 	andeq	r0, r0, r0
  98:	77800d30 	undefined
  9c:	000001b4 	strheq	r0, [r0], -r4
	...
  a8:	0000001c 	andeq	r0, r0, ip, lsl r0
  ac:	022e0002 	eoreq	r0, lr, #2	; 0x2
  b0:	00040000 	andeq	r0, r4, r0
  b4:	00000000 	andeq	r0, r0, r0
  b8:	77800ef0 	undefined
  bc:	00000154 	andeq	r0, r0, r4, asr r1
	...

Disassembly of section .debug_info:

00000000 <.debug_info>:
   0:	00000068 	andeq	r0, r0, r8, rrx
   4:	00000002 	andeq	r0, r0, r2
   8:	01040000 	tsteq	r4, r0
	...
  14:	65736162 	ldrbvs	r6, [r3, #-354]!
  18:	2f00732e 	svccs	0x0000732e
  1c:	656d6f68 	strbvs	r6, [sp, #-3944]!
  20:	6570732f 	ldrbvs	r7, [r0, #-815]!
  24:	32316763 	eorscc	r6, r1, #25952256	; 0x18c0000
  28:	6d2f312d 	stfvss	f3, [pc, #-180]!
  2c:	34303463 	ldrtcc	r3, [r0], #-1123
  30:	6d6f682f 	stclvs	8, cr6, [pc, #-188]!
  34:	722f7365 	eorvc	r7, pc, #-1811939327	; 0x94000001
  38:	32343161 	eorscc	r3, r4, #1073741848	; 0x40000018
  3c:	2f333936 	svccs	0x00333936
  40:	2f706d74 	svccs	0x00706d74
  44:	756d6973 	strbvc	r6, [sp, #-2419]!
  48:	6f64616c 	svcvs	0x0064616c
  4c:	6c705f72 	ldclvs	15, cr5, [r0], #-456
  50:	72657961 	rsbvc	r7, r5, #1589248	; 0x184000
  54:	626f722f 	rsbvs	r7, pc, #-268435454	; 0xf0000002
  58:	6f5f746f 	svcvs	0x005f746f
  5c:	4e470073 	mcrmi	0, 2, r0, cr7, cr3, {3}
  60:	53412055 	movtpl	r2, #4181	; 0x1055
  64:	312e3220 	teqcc	lr, r0, lsr #4
  68:	80010039 	andhi	r0, r1, r9, lsr r0
  6c:	0000006b 	andeq	r0, r0, fp, rrx
  70:	00120002 	andseq	r0, r2, r2
  74:	01040000 	tsteq	r4, r0
  78:	0000006d 	andeq	r0, r0, sp, rrx
  7c:	778006b0 	undefined
  80:	77800708 	strvc	r0, [r0, r8, lsl #14]
  84:	2e747067 	cdpcs	0, 7, cr7, cr4, cr7, {3}
  88:	682f0073 	stmdavs	pc!, {r0, r1, r4, r5, r6}
  8c:	2f656d6f 	svccs	0x00656d6f
  90:	63657073 	cmnvs	r5, #115	; 0x73
  94:	2d323167 	ldfcss	f3, [r2, #-412]!
  98:	636d2f31 	cmnvs	sp, #196	; 0xc4
  9c:	2f343034 	svccs	0x00343034
  a0:	656d6f68 	strbvs	r6, [sp, #-3944]!
  a4:	61722f73 	cmnvs	r2, r3, ror pc
  a8:	36323431 	undefined
  ac:	742f3339 	strtvc	r3, [pc], #825	; b4 <UART_UTS>
  b0:	732f706d 	teqvc	pc, #109	; 0x6d
  b4:	6c756d69 	ldclvs	13, cr6, [r5], #-420
  b8:	726f6461 	rsbvc	r6, pc, #1627389952	; 0x61000000
  bc:	616c705f 	qdsubvs	r7, pc, ip
  c0:	2f726579 	svccs	0x00726579
  c4:	6f626f72 	svcvs	0x00626f72
  c8:	736f5f74 	cmnvc	pc, #464	; 0x1d0
  cc:	554e4700 	strbpl	r4, [lr, #-1792]
  d0:	20534120 	subscs	r4, r3, r0, lsr #2
  d4:	39312e32 	ldmdbcc	r1!, {r1, r4, r5, r9, sl, fp, sp}
  d8:	6b800100 	blvs	fe0004e0 <__bss_end__+0x867fe080>
  dc:	02000000 	andeq	r0, r0, #0	; 0x0
  e0:	00002600 	andeq	r2, r0, r0, lsl #12
  e4:	b6010400 	strlt	r0, [r1], -r0, lsl #8
  e8:	10000000 	andne	r0, r0, r0
  ec:	5c778007 	ldclpl	0, cr8, [r7], #-28
  f0:	6977800a 	ldmdbvs	r7!, {r1, r3, pc}^
  f4:	732e7172 	teqvc	lr, #-2147483620	; 0x8000001c
  f8:	6f682f00 	svcvs	0x00682f00
  fc:	732f656d 	teqvc	pc, #457179136	; 0x1b400000
 100:	67636570 	undefined
 104:	312d3231 	teqcc	sp, r1, lsr r2
 108:	34636d2f 	strbtcc	r6, [r3], #-3375
 10c:	682f3430 	stmdavs	pc!, {r4, r5, sl, ip, sp}
 110:	73656d6f 	cmnvc	r5, #7104	; 0x1bc0
 114:	3161722f 	cmncc	r1, pc, lsr #4
 118:	39363234 	ldmdbcc	r6!, {r2, r4, r5, r9, ip, sp}
 11c:	6d742f33 	ldclvs	15, cr2, [r4, #-204]!
 120:	69732f70 	ldmdbvs	r3!, {r4, r5, r6, r8, r9, sl, fp, sp}^
 124:	616c756d 	cmnvs	ip, sp, ror #10
 128:	5f726f64 	svcpl	0x00726f64
 12c:	79616c70 	stmdbvc	r1!, {r4, r5, r6, sl, fp, sp, lr}^
 130:	722f7265 	eorvc	r7, pc, #1342177286	; 0x50000006
 134:	746f626f 	strbtvc	r6, [pc], #623	; 13c <TZIC_ENSET3+0x30>
 138:	00736f5f 	rsbseq	r6, r3, pc, asr pc
 13c:	20554e47 	subscs	r4, r5, r7, asr #28
 140:	32205341 	eorcc	r5, r0, #67108865	; 0x4000001
 144:	0039312e 	eorseq	r3, r9, lr, lsr #2
 148:	00708001 	rsbseq	r8, r0, r1
 14c:	00020000 	andeq	r0, r2, r0
 150:	0000003a 	andeq	r0, r0, sl, lsr r0
 154:	01bf0104 	undefined instruction 0x01bf0104
 158:	0a600000 	beq	1800160 <_stack+0x1780160>
 15c:	0d307780 	ldceq	7, cr7, [r0, #-512]!
 160:	79737780 	ldmdbvc	r3!, {r7, r8, r9, sl, ip, sp, lr}^
 164:	6c616373 	stclvs	3, cr6, [r1], #-460
 168:	732e736c 	teqvc	lr, #-1342177279	; 0xb0000001
 16c:	6f682f00 	svcvs	0x00682f00
 170:	732f656d 	teqvc	pc, #457179136	; 0x1b400000
 174:	67636570 	undefined
 178:	312d3231 	teqcc	sp, r1, lsr r2
 17c:	34636d2f 	strbtcc	r6, [r3], #-3375
 180:	682f3430 	stmdavs	pc!, {r4, r5, sl, ip, sp}
 184:	73656d6f 	cmnvc	r5, #7104	; 0x1bc0
 188:	3161722f 	cmncc	r1, pc, lsr #4
 18c:	39363234 	ldmdbcc	r6!, {r2, r4, r5, r9, ip, sp}
 190:	6d742f33 	ldclvs	15, cr2, [r4, #-204]!
 194:	69732f70 	ldmdbvs	r3!, {r4, r5, r6, r8, r9, sl, fp, sp}^
 198:	616c756d 	cmnvs	ip, sp, ror #10
 19c:	5f726f64 	svcpl	0x00726f64
 1a0:	79616c70 	stmdbvc	r1!, {r4, r5, r6, sl, fp, sp, lr}^
 1a4:	722f7265 	eorvc	r7, pc, #1342177286	; 0x50000006
 1a8:	746f626f 	strbtvc	r6, [pc], #623	; 1b0 <TZIC_ENCLEAR3+0x24>
 1ac:	00736f5f 	rsbseq	r6, r3, pc, asr pc
 1b0:	20554e47 	subscs	r4, r5, r7, asr #28
 1b4:	32205341 	eorcc	r5, r0, #67108865	; 0x4000001
 1b8:	0039312e 	eorseq	r3, r9, lr, lsr #2
 1bc:	006c8001 	rsbeq	r8, ip, r1
 1c0:	00020000 	andeq	r0, r2, r0
 1c4:	0000004e 	andeq	r0, r0, lr, asr #32
 1c8:	02a00104 	adceq	r0, r0, #1	; 0x1
 1cc:	0d300000 	ldceq	0, cr0, [r0]
 1d0:	0ee47780 	cdpeq	7, 14, cr7, cr4, cr0, {4}
 1d4:	61757780 	cmnvs	r5, r0, lsl #15
 1d8:	732e7472 	teqvc	lr, #1912602624	; 0x72000000
 1dc:	6f682f00 	svcvs	0x00682f00
 1e0:	732f656d 	teqvc	pc, #457179136	; 0x1b400000
 1e4:	67636570 	undefined
 1e8:	312d3231 	teqcc	sp, r1, lsr r2
 1ec:	34636d2f 	strbtcc	r6, [r3], #-3375
 1f0:	682f3430 	stmdavs	pc!, {r4, r5, sl, ip, sp}
 1f4:	73656d6f 	cmnvc	r5, #7104	; 0x1bc0
 1f8:	3161722f 	cmncc	r1, pc, lsr #4
 1fc:	39363234 	ldmdbcc	r6!, {r2, r4, r5, r9, ip, sp}
 200:	6d742f33 	ldclvs	15, cr2, [r4, #-204]!
 204:	69732f70 	ldmdbvs	r3!, {r4, r5, r6, r8, r9, sl, fp, sp}^
 208:	616c756d 	cmnvs	ip, sp, ror #10
 20c:	5f726f64 	svcpl	0x00726f64
 210:	79616c70 	stmdbvc	r1!, {r4, r5, r6, sl, fp, sp, lr}^
 214:	722f7265 	eorvc	r7, pc, #1342177286	; 0x50000006
 218:	746f626f 	strbtvc	r6, [pc], #623	; 220 <TZIC_SRCSET3+0x14>
 21c:	00736f5f 	rsbseq	r6, r3, pc, asr pc
 220:	20554e47 	subscs	r4, r5, r7, asr #28
 224:	32205341 	eorcc	r5, r0, #67108865	; 0x4000001
 228:	0039312e 	eorseq	r3, r9, lr, lsr #2
 22c:	00728001 	rsbseq	r8, r2, r1
 230:	00020000 	andeq	r0, r2, r0
 234:	00000062 	andeq	r0, r0, r2, rrx
 238:	03410104 	movteq	r0, #4356	; 0x1104
 23c:	0ef00000 	cdpeq	0, 15, cr0, cr0, cr0, {0}
 240:	10447780 	subne	r7, r4, r0, lsl #15
 244:	70677780 	rsbvc	r7, r7, r0, lsl #15
 248:	725f6f69 	subsvc	r6, pc, #420	; 0x1a4
 24c:	746f626f 	strbtvc	r6, [pc], #623	; 254 <TZIC_SRCSET3+0x48>
 250:	2f00732e 	svccs	0x0000732e
 254:	656d6f68 	strbvs	r6, [sp, #-3944]!
 258:	6570732f 	ldrbvs	r7, [r0, #-815]!
 25c:	32316763 	eorscc	r6, r1, #25952256	; 0x18c0000
 260:	6d2f312d 	stfvss	f3, [pc, #-180]!
 264:	34303463 	ldrtcc	r3, [r0], #-1123
 268:	6d6f682f 	stclvs	8, cr6, [pc, #-188]!
 26c:	722f7365 	eorvc	r7, pc, #-1811939327	; 0x94000001
 270:	32343161 	eorscc	r3, r4, #1073741848	; 0x40000018
 274:	2f333936 	svccs	0x00333936
 278:	2f706d74 	svccs	0x00706d74
 27c:	756d6973 	strbvc	r6, [sp, #-2419]!
 280:	6f64616c 	svcvs	0x0064616c
 284:	6c705f72 	ldclvs	15, cr5, [r0], #-456
 288:	72657961 	rsbvc	r7, r5, #1589248	; 0x184000
 28c:	626f722f 	rsbvs	r7, pc, #-268435454	; 0xf0000002
 290:	6f5f746f 	svcvs	0x005f746f
 294:	4e470073 	mcrmi	0, 2, r0, cr7, cr3, {3}
 298:	53412055 	movtpl	r2, #4181	; 0x1055
 29c:	312e3220 	teqcc	lr, r0, lsr #4
 2a0:	80010039 	andhi	r0, r1, r9, lsr r0

Disassembly of section .debug_abbrev:

00000000 <.debug_abbrev>:
   0:	10001101 	andne	r1, r0, r1, lsl #2
   4:	03065506 	movweq	r5, #25862	; 0x6506
   8:	25081b08 	strcs	r1, [r8, #-2824]
   c:	00051308 	andeq	r1, r5, r8, lsl #6
  10:	11010000 	tstne	r1, r0
  14:	11061000 	tstne	r6, r0
  18:	03011201 	movweq	r1, #4609	; 0x1201
  1c:	25081b08 	strcs	r1, [r8, #-2824]
  20:	00051308 	andeq	r1, r5, r8, lsl #6
  24:	11010000 	tstne	r1, r0
  28:	11061000 	tstne	r6, r0
  2c:	03011201 	movweq	r1, #4609	; 0x1201
  30:	25081b08 	strcs	r1, [r8, #-2824]
  34:	00051308 	andeq	r1, r5, r8, lsl #6
  38:	11010000 	tstne	r1, r0
  3c:	11061000 	tstne	r6, r0
  40:	03011201 	movweq	r1, #4609	; 0x1201
  44:	25081b08 	strcs	r1, [r8, #-2824]
  48:	00051308 	andeq	r1, r5, r8, lsl #6
  4c:	11010000 	tstne	r1, r0
  50:	11061000 	tstne	r6, r0
  54:	03011201 	movweq	r1, #4609	; 0x1201
  58:	25081b08 	strcs	r1, [r8, #-2824]
  5c:	00051308 	andeq	r1, r5, r8, lsl #6
  60:	11010000 	tstne	r1, r0
  64:	11061000 	tstne	r6, r0
  68:	03011201 	movweq	r1, #4609	; 0x1201
  6c:	25081b08 	strcs	r1, [r8, #-2824]
  70:	00051308 	andeq	r1, r5, r8, lsl #6
	...

Disassembly of section .debug_line:

00000000 <.debug_line>:
   0:	00000069 	andeq	r0, r0, r9, rrx
   4:	001d0002 	andseq	r0, sp, r2
   8:	01020000 	tsteq	r2, r0
   c:	000d0efb 	strdeq	r0, [sp], -fp
  10:	01010101 	tsteq	r1, r1, lsl #2
  14:	01000000 	tsteq	r0, r0
  18:	00010000 	andeq	r0, r1, r0
  1c:	65736162 	ldrbvs	r6, [r3, #-354]!
  20:	0000732e 	andeq	r7, r0, lr, lsr #6
  24:	00000000 	andeq	r0, r0, r0
  28:	05e00205 	strbeq	r0, [r0, #517]!
  2c:	1b037780 	blne	dde34 <_stack+0x5de34>
  30:	2f2f2f01 	svccs	0x002f2f01
  34:	2f2f2f2f 	svccs	0x002f2f2f
  38:	01000202 	tsteq	r0, r2, lsl #4
  3c:	02050001 	andeq	r0, r5, #1	; 0x1
  40:	77800600 	strvc	r0, [r0, r0, lsl #12]
  44:	2f013303 	svccs	0x00013303
  48:	2f2f2f2f 	svccs	0x002f2f2f
  4c:	2f2f2f2f 	svccs	0x002f2f2f
  50:	302f312f 	eorcc	r3, pc, pc, lsr #2
  54:	2e0b0330 	mcrcs	3, 0, r0, cr11, cr0, {1}
  58:	2f2e0e03 	svccs	0x002e0e03
  5c:	2f2f2f2f 	svccs	0x002f2f2f
  60:	31312f30 	teqcc	r1, r0, lsr pc
  64:	2f2f2f2f 	svccs	0x002f2f2f
  68:	01001c02 	tsteq	r0, r2, lsl #24
  6c:	00004501 	andeq	r4, r0, r1, lsl #10
  70:	1c000200 	sfmne	f0, 4, [r0], {0}
  74:	02000000 	andeq	r0, r0, #0	; 0x0
  78:	0d0efb01 	vstreq	d15, [lr, #-4]
  7c:	01010100 	tsteq	r1, r0, lsl #2
  80:	00000001 	andeq	r0, r0, r1
  84:	01000001 	tsteq	r0, r1
  88:	74706700 	ldrbtvc	r6, [r0], #-1792
  8c:	0000732e 	andeq	r7, r0, lr, lsr #6
  90:	00000000 	andeq	r0, r0, r0
  94:	06b00205 	ldrteq	r0, [r0], r5, lsl #4
  98:	16037780 	strne	r7, [r3], -r0, lsl #15
  9c:	2f303101 	svccs	0x00303101
  a0:	2f302f31 	svccs	0x00302f31
  a4:	4a0d032f 	bmi	340d68 <_stack+0x2c0d68>
  a8:	2f2f2f31 	svccs	0x002f2f31
  ac:	2f2f2f2f 	svccs	0x002f2f2f
  b0:	00060231 	andeq	r0, r6, r1, lsr r2
  b4:	01050101 	tsteq	r5, r1, lsl #2
  b8:	00020000 	andeq	r0, r2, r0
  bc:	0000001c 	andeq	r0, r0, ip, lsl r0
  c0:	0efb0102 	cdpeq	1, 15, cr0, cr11, cr2, {0}
  c4:	0101000d 	tsteq	r1, sp
  c8:	00000101 	andeq	r0, r0, r1, lsl #2
  cc:	00000100 	andeq	r0, r0, r0, lsl #2
  d0:	72690001 	rsbvc	r0, r9, #1	; 0x1
  d4:	00732e71 	rsbseq	r2, r3, r1, ror lr
  d8:	00000000 	andeq	r0, r0, r0
  dc:	10020500 	andne	r0, r2, r0, lsl #10
  e0:	03778007 	cmneq	r7, #7	; 0x7
  e4:	2f300115 	svccs	0x00300115
  e8:	2f2f2f2f 	svccs	0x002f2f2f
  ec:	2f2f2f32 	svccs	0x002f2f32
  f0:	312f2f2f 	teqcc	pc, pc, lsr #30
  f4:	2f2f2f2f 	svccs	0x002f2f2f
  f8:	2f2f2f31 	svccs	0x002f2f31
  fc:	302f302f 	eorcc	r3, pc, pc, lsr #32
 100:	10032f2f 	andne	r2, r3, pc, lsr #30
 104:	2f2f2f4a 	svccs	0x002f2f4a
 108:	2f2f2f30 	svccs	0x002f2f30
 10c:	2f2f302f 	svccs	0x002f302f
 110:	2f2f2f2f 	svccs	0x002f2f2f
 114:	2f2f2f2f 	svccs	0x002f2f2f
 118:	2f2f2f2f 	svccs	0x002f2f2f
 11c:	2f32312f 	svccs	0x0032312f
 120:	302f2f2f 	eorcc	r2, pc, pc, lsr #30
 124:	2f2f312f 	svccs	0x002f312f
 128:	2f312f2f 	svccs	0x00312f2f
 12c:	2f2f2f30 	svccs	0x002f2f30
 130:	2f302f2f 	svccs	0x00302f2f
 134:	2f2f302f 	svccs	0x002f302f
 138:	2f4a2303 	svccs	0x004a2303
 13c:	2f2f2f2f 	svccs	0x002f2f2f
 140:	2f2f2f2f 	svccs	0x002f2f2f
 144:	2f2f2f2f 	svccs	0x002f2f2f
 148:	2f2f2f2f 	svccs	0x002f2f2f
 14c:	2f2f2f2f 	svccs	0x002f2f2f
 150:	2f2f2f2f 	svccs	0x002f2f2f
 154:	2f2f2f2f 	svccs	0x002f2f2f
 158:	2f2f2f2f 	svccs	0x002f2f2f
 15c:	2f2f2f2f 	svccs	0x002f2f2f
 160:	2f2f2f2f 	svccs	0x002f2f2f
 164:	2f2f2f2f 	svccs	0x002f2f2f
 168:	2f2f2f2f 	svccs	0x002f2f2f
 16c:	2f2f2f2f 	svccs	0x002f2f2f
 170:	2f2f2f2f 	svccs	0x002f2f2f
 174:	2f2f2f2f 	svccs	0x002f2f2f
 178:	2f2f2f2f 	svccs	0x002f2f2f
 17c:	2f2f2f2f 	svccs	0x002f2f2f
 180:	2f2f2f2f 	svccs	0x002f2f2f
 184:	2f2f2f2f 	svccs	0x002f2f2f
 188:	2f2f2f2f 	svccs	0x002f2f2f
 18c:	2f2f2f2f 	svccs	0x002f2f2f
 190:	2f2f2f2f 	svccs	0x002f2f2f
 194:	2f2f2f2f 	svccs	0x002f2f2f
 198:	2f2f2f2f 	svccs	0x002f2f2f
 19c:	2f2f2f2f 	svccs	0x002f2f2f
 1a0:	2f2f2f2f 	svccs	0x002f2f2f
 1a4:	2f2f2f2f 	svccs	0x002f2f2f
 1a8:	2f2f2f2f 	svccs	0x002f2f2f
 1ac:	2f2f2f2f 	svccs	0x002f2f2f
 1b0:	2f2f2f2f 	svccs	0x002f2f2f
 1b4:	2f2f2f2f 	svccs	0x002f2f2f
 1b8:	02022f2f 	andeq	r2, r2, #188	; 0xbc
 1bc:	dd010100 	stfles	f0, [r1]
 1c0:	02000000 	andeq	r0, r0, #0	; 0x0
 1c4:	00002100 	andeq	r2, r0, r0, lsl #2
 1c8:	fb010200 	blx	409d2 <TZIC_SWINT+0x3fad2>
 1cc:	01000d0e 	tsteq	r0, lr, lsl #26
 1d0:	00010101 	andeq	r0, r1, r1, lsl #2
 1d4:	00010000 	andeq	r0, r1, r0
 1d8:	73000100 	movwvc	r0, #256	; 0x100
 1dc:	61637379 	smcvs	14137
 1e0:	2e736c6c 	cdpcs	12, 7, cr6, cr3, cr12, {3}
 1e4:	00000073 	andeq	r0, r0, r3, ror r0
 1e8:	05000000 	streq	r0, [r0]
 1ec:	800a6002 	andhi	r6, sl, r2
 1f0:	01160377 	tsteq	r6, r7, ror r3
 1f4:	302f2f2f 	eorcc	r2, pc, pc, lsr #30
 1f8:	2f2f2f2f 	svccs	0x002f2f2f
 1fc:	302f2f2f 	eorcc	r2, pc, pc, lsr #30
 200:	332f2f2f 	teqcc	pc, #188	; 0xbc
 204:	2f2f2f2f 	svccs	0x002f2f2f
 208:	28020903 	stmdacs	r2, {r0, r1, r8, fp}
 20c:	2f2f2f01 	svccs	0x002f2f01
 210:	2f2f2f2f 	svccs	0x002f2f2f
 214:	2f2f2f2f 	svccs	0x002f2f2f
 218:	2f2f2f2f 	svccs	0x002f2f2f
 21c:	2f2f2f2f 	svccs	0x002f2f2f
 220:	2f2f2f2f 	svccs	0x002f2f2f
 224:	2f2f2f2f 	svccs	0x002f2f2f
 228:	2f2f2f2f 	svccs	0x002f2f2f
 22c:	2f2f2f2f 	svccs	0x002f2f2f
 230:	2f2f2f2f 	svccs	0x002f2f2f
 234:	2f2f2f2f 	svccs	0x002f2f2f
 238:	2f2f2f2f 	svccs	0x002f2f2f
 23c:	2f2f2f2f 	svccs	0x002f2f2f
 240:	2f2f2f2f 	svccs	0x002f2f2f
 244:	2f2f2f2f 	svccs	0x002f2f2f
 248:	2f2f2f2f 	svccs	0x002f2f2f
 24c:	2f2f2f2f 	svccs	0x002f2f2f
 250:	2f2f2f2f 	svccs	0x002f2f2f
 254:	2f2f2f2f 	svccs	0x002f2f2f
 258:	2f2f2f2f 	svccs	0x002f2f2f
 25c:	2f2f2f2f 	svccs	0x002f2f2f
 260:	2f2f2f2f 	svccs	0x002f2f2f
 264:	2f2f2f2f 	svccs	0x002f2f2f
 268:	2f2f2f2f 	svccs	0x002f2f2f
 26c:	2f2f2f2f 	svccs	0x002f2f2f
 270:	2f2f2f2f 	svccs	0x002f2f2f
 274:	2f2f2f2f 	svccs	0x002f2f2f
 278:	2f2f2f2f 	svccs	0x002f2f2f
 27c:	2f2f2f2f 	svccs	0x002f2f2f
 280:	2f2f2f2f 	svccs	0x002f2f2f
 284:	2f2f2f2f 	svccs	0x002f2f2f
 288:	2f2f2f2f 	svccs	0x002f2f2f
 28c:	2f2f3235 	svccs	0x002f3235
 290:	312f2f32 	teqcc	pc, r2, lsr pc
 294:	03303032 	teqeq	r0, #50	; 0x32
 298:	022e0186 	eoreq	r0, lr, #-2147483615	; 0x80000021
 29c:	01010002 	tsteq	r1, r2
 2a0:	0000009d 	muleq	r0, sp, r0
 2a4:	001d0002 	andseq	r0, sp, r2
 2a8:	01020000 	tsteq	r2, r0
 2ac:	000d0efb 	strdeq	r0, [sp], -fp
 2b0:	01010101 	tsteq	r1, r1, lsl #2
 2b4:	01000000 	tsteq	r0, r0
 2b8:	00010000 	andeq	r0, r1, r0
 2bc:	74726175 	ldrbtvc	r6, [r2], #-373
 2c0:	0000732e 	andeq	r7, r0, lr, lsr #6
 2c4:	00000000 	andeq	r0, r0, r0
 2c8:	0d300205 	lfmeq	f0, 4, [r0, #-20]!
 2cc:	21037780 	smlabbcs	r3, r0, r7, r7
 2d0:	2f303501 	svccs	0x00303501
 2d4:	2f2e1703 	svccs	0x002e1703
 2d8:	0b032f2f 	bleq	cbf9c <_stack+0x4bf9c>
 2dc:	302f2f4a 	eorcc	r2, pc, sl, asr #30
 2e0:	2f2f302f 	svccs	0x002f302f
 2e4:	2f2f302f 	svccs	0x002f302f
 2e8:	2f302f2f 	svccs	0x00302f2f
 2ec:	302f2f36 	eorcc	r2, pc, r6, lsr pc
 2f0:	2f2f302f 	svccs	0x002f302f
 2f4:	2f302f2f 	svccs	0x00302f2f
 2f8:	302f2f2f 	eorcc	r2, pc, pc, lsr #30
 2fc:	2f2f342f 	svccs	0x002f342f
 300:	2f2f2f2f 	svccs	0x002f2f2f
 304:	032f2f2f 	teqeq	pc, #188	; 0xbc
 308:	2f30660a 	svccs	0x0030660a
 30c:	2f512f2f 	svccs	0x00512f2f
 310:	2f2f2f2f 	svccs	0x002f2f2f
 314:	502f302f 	eorpl	r3, pc, pc, lsr #32
 318:	2f2f2f2f 	svccs	0x002f2f2f
 31c:	2f2f2f50 	svccs	0x002f2f50
 320:	09032f2f 	stmdbeq	r3, {r0, r1, r2, r3, r5, r8, r9, sl, fp, sp}
 324:	2f31314a 	svccs	0x0031314a
 328:	2f2f2f2f 	svccs	0x002f2f2f
 32c:	30302f2f 	eorscc	r2, r0, pc, lsr #30
 330:	2f2f2f2f 	svccs	0x002f2f2f
 334:	302f2f2f 	eorcc	r2, pc, pc, lsr #30
 338:	32502f31 	subscc	r2, r0, #196	; 0xc4
 33c:	01000402 	tsteq	r0, r2, lsl #8
 340:	00008c01 	andeq	r8, r0, r1, lsl #24
 344:	23000200 	movwcs	r0, #512	; 0x200
 348:	02000000 	andeq	r0, r0, #0	; 0x0
 34c:	0d0efb01 	vstreq	d15, [lr, #-4]
 350:	01010100 	tsteq	r1, r0, lsl #2
 354:	00000001 	andeq	r0, r0, r1
 358:	01000001 	tsteq	r0, r1
 35c:	69706700 	ldmdbvs	r0!, {r8, r9, sl, sp, lr}^
 360:	6f725f6f 	svcvs	0x00725f6f
 364:	2e746f62 	cdpcs	15, 7, cr6, cr4, cr2, {3}
 368:	00000073 	andeq	r0, r0, r3, ror r0
 36c:	05000000 	streq	r0, [r0]
 370:	800ef002 	andhi	pc, lr, r2
 374:	01180377 	tsteq	r8, r7, ror r3
 378:	2f30302f 	svccs	0x0030302f
 37c:	2f2f2f2f 	svccs	0x002f2f2f
 380:	0b03302f 	bleq	cc444 <_stack+0x4c444>
 384:	312f322e 	teqcc	pc, lr, lsr #4
 388:	2f2f2f2f 	svccs	0x002f2f2f
 38c:	3031302f 	eorscc	r3, r1, pc, lsr #32
 390:	312f342f 	teqcc	pc, pc, lsr #8
 394:	2f342f30 	svccs	0x00342f30
 398:	362f3031 	undefined
 39c:	30312f2f 	eorscc	r2, r1, pc, lsr #30
 3a0:	2f34302f 	svccs	0x0034302f
 3a4:	30303630 	eorscc	r3, r0, r0, lsr r6
 3a8:	302f2f2f 	eorcc	r2, pc, pc, lsr #30
 3ac:	30302f2f 	eorscc	r2, r0, pc, lsr #30
 3b0:	2f303036 	svccs	0x00303036
 3b4:	2f302f2f 	svccs	0x00302f2f
 3b8:	0330302f 	teqeq	r0, #47	; 0x2f
 3bc:	32302e0b 	eorscc	r2, r0, #176	; 0xb0
 3c0:	2f2f2f2f 	svccs	0x002f2f2f
 3c4:	302f2f2f 	eorcc	r2, pc, pc, lsr #30
 3c8:	30302f2f 	eorscc	r2, r0, pc, lsr #30
 3cc:	01000a02 	tsteq	r0, r2, lsl #20
 3d0:	Address 0x000003d0 is out of bounds.


Disassembly of section .debug_ranges:

00000000 <.debug_ranges>:
   0:	ffffffff 	undefined instruction 0xffffffff
   4:	00000000 	andeq	r0, r0, r0
   8:	778005e0 	strvc	r0, [r0, r0, ror #11]
   c:	77800600 	strvc	r0, [r0, r0, lsl #12]
  10:	77800600 	strvc	r0, [r0, r0, lsl #12]
  14:	778006ac 	strvc	r0, [r0, ip, lsr #13]
	...

Disassembly of section .ARM.attributes:

00000000 <_stack-0x80000>:
   0:	00001341 	andeq	r1, r0, r1, asr #6
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	00000009 	andeq	r0, r0, r9
  10:	01080306 	tsteq	r8, r6, lsl #6
