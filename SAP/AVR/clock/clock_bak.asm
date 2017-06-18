
.include "m169def.inc"
.org 	0x1000
.include "print.inc"

.dseg

plus:	.byte 1
flag:	.byte 1

.cseg

.org 	0x0000

jmp 	main

.org 	0x000A

jmp 	INT_CLC

.org 	0x0100

INT_CLC:
	; save data
	push 	r16
	in		r16, SREG
	push 	r16

	cpi		r30, 0
	brlt	skip0
	breq	skip1
	jmp		increment

	skip0:
		lds		r16, flag
		andi	r16, 0x01
		tst		r16
		breq 	setFlag
		jmp		increment

	skip1:
		cpi		r31, 0
		brlt	skip0

	increment:
		lds		r16, plus
		inc		r16
		sts		plus, r16
		ldi		r16, 0
		sts		flag, r16
		jmp		skip_exit

	setFlag:
		ldi		r16, 1
		sts		flag, r16

    skip_exit:

	; restore data
	pop		r16
	out		SREG, r16
	pop		r16
	
	reti

incMs:
	call	INT_CLC
	ret

setTime:
	lds		r16, plus
	add		r31, r16
	ldi		r16, 0
	sts		plus, r16

  setTime_msCheck:
	cpi		r31, 10
	brsh	setTime_ms1Inc
	jmp		setTime_exit

  setTime_ms1Inc:
  	ldi		r31, 0
	inc		r30
	cpi		r30, 10
	brsh	setTime_s0Inc
	jmp		setTime_exit

  setTime_s0Inc:
    ldi		r30, 0
	inc		r29
	cpi		r29, 10
	brsh	setTime_s1Inc
	jmp		setTime_exit

  setTime_s1Inc:
  	ldi		r29, 0
	inc 	r28
	cpi		r28, 6
	brsh	setTime_m0Inc
	jmp		setTime_exit

  setTime_m0Inc:
  	ldi 	r28, 0
	inc 	r27
	cpi		r27, 10
	brsh	setTime_m1Inc
	jmp		setTime_exit
  
  setTime_m1Inc:
  	ldi		r27, 0
	inc		r26
	cpi		r26, 10
	brsh	setTime_clrMin
	jmp		setTime_exit

  setTime_clrMin:
    ldi		r26, 0
	jmp		setTime_exit

  setTime_exit:
  	ret
	

showTime:
	call	setTime

	mov		r16, r26
	subi	r16, -'0'
	ldi		r17, 2
	call	show_char

	mov		r16, r27
	subi	r16, -'0'
	ldi		r17, 3
	call	show_char

	mov		r16, r28
	subi	r16, -'0'
	ldi		r17, 4
	call	show_char

	mov		r16, r29
	subi	r16, -'0'
	ldi		r17, 5
	call	show_char

	mov		r16, r30
	subi	r16, -'0'
	ldi		r17, 6
	call	show_char

	mov		r16, r31
	subi	r16, -'0'
	ldi		r17, 7
	call	show_char

	ret

loop:
	call 	showTime
	
	in 		r16, PINE ; right
	in 		r17, PINE ; left
	in		r18, PINB ; enter
	andi	r16, 0x08
	andi	r17, 0x04
	andi	r18, 0x10

	tst		r16
	breq	start

	start_ret:

	tst		r17
	breq	stop

	stop_ret:

	tst		r18
	breq	reset

	reset_ret:
	
	;call	incMs
	jmp 	loop


reset:
	ldi		r16, 0x00
	ldi		r31, 0
	ldi		r30, 0
	ldi		r29, 0
	ldi		r28, 0
	ldi		r27, 0
	ldi		r26, 0
	st		X, r16
	st		Y, r16
	st		Z, r16
	jmp		reset_ret
	
stop:
	cli
	jmp 	stop_ret
	
start:
	sei
	jmp 	start_ret

main:

	; stack
	ldi 	r16, 0xFF
	out 	SPL, r16
	ldi 	r16, 0x04
	out 	SPH, r16

	; don't interrupt
	cli

	; display initialization
	call 	init_disp

	; joystick
	in 	 	r17, DDRE
	andi 	r17, 0xF3
	in 	 	r16, PORTE
	ori  	r16, 0x0C
	out  	DDRE, r17
	out  	PORTE, r16
	ldi  	r16, 0x00
	sts  	DIDR1, r16
	in   	r17, DDRB
	andi 	r17, 0x2F
	in   	r16, PORTB
	ori  	r16, 0xDF
	in	 	r16, PORTB
	ori  	r16, 0xD0
	out  	DDRB, r17
	out	 	PORTB, r16
	
	; interruptor initialization
	ldi 	r16, 0x08
	sts 	ASSR, r16
	ldi 	r16, 0x01
	sts 	TIMSK2, r16
	ldi 	r16, 0x01
	sts 	TCCR2A, r16
	clr 	r16
	out 	EIMSK, r16

	; some initialization
	call reset

	jmp loop
