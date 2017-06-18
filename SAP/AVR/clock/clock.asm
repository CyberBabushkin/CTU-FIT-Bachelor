.include 	"m169def.inc"
.org 		0x1000
.include 	"print.inc"

.org 		0x0000

.dseg

.org		0x0356

ms0:		.byte 1
ms1:		.byte 1
sec0:		.byte 1
sec1:		.byte 1
min0:		.byte 1
min1:		.byte 1
flag:		.byte 1

.cseg

jmp 		main

.org 		0x000A

jmp 		INT_CLC

.org 		0x0100

INT_CLC:
	; save data
	push 		r16
	in			r16, SREG
	push 		r16

	lds			r16, ms1
	cpi			r16, 2
	brlt		skip0
	breq		skip1
	jmp			increment

	skip0:
		lds			r16, flag
		tst			r16
		breq 		setFlag
		jmp			increment

	skip1:
		lds			r16, ms0
		cpi			r16, 8 
		brlt		skip0

	increment:
		lds			r16, ms0
		inc			r16
		sts			ms0, r16
		ldi			r16, 0
		sts			flag, r16
		jmp			skip_exit

	setFlag:
		ldi			r16, 1
		sts			flag, r16

    skip_exit:

	; restore data
	pop			r16
	out			SREG, r16
	pop			r16
	
	reti

incMs:
	call		INT_CLC
	ret

setTime:

  setTime_msCheck:
	lds			r16, ms0
	cpi			r16, 10
	brsh		setTime_ms1Inc
	jmp			setTime_exit

  setTime_ms1Inc:
	ldi			r16, 0
	sts			ms0, r16
	lds			r16, ms1
	inc 		r16
	sts			ms1, r16
	cpi			r16, 10
	brsh		setTime_s0Inc
	jmp			setTime_exit

  setTime_s0Inc:
    ldi			r16, 0
	sts			ms1, r16
	lds			r16, sec0
	inc			r16
	sts			sec0, r16
	cpi			r16, 10
	brsh		setTime_s1Inc
	jmp			setTime_exit

  setTime_s1Inc:
	ldi			r16, 0
	sts			sec0, r16
	lds			r16, sec1
	inc 		r16
	sts			sec1, r16
	cpi			r16, 6
	brsh		setTime_m0Inc
	jmp			setTime_exit

  setTime_m0Inc:
	ldi			r16, 0
	sts			sec1, r16
	lds			r16, min0
	inc 		r16
	sts			min0, r16
	cpi			r16, 10
	brsh		setTime_m1Inc
	jmp			setTime_exit
  
  setTime_m1Inc:
	ldi			r16, 0
	sts			min0, r16
	lds			r16, min1
	inc 		r16
	sts			min1, r16

  setTime_exit:
  	ret
	

showTime:
	call		setTime

	lds			r16, min1
	subi		r16, -'0'
	ldi			r17, 2
	call		show_char

	lds			r16, min0
	subi		r16, -'0'
	ldi			r17, 3
	call		show_char

	lds			r16, sec1
	subi		r16, -'0'
	ldi			r17, 4
	call		show_char

	lds			r16, sec0
	subi		r16, -'0'
	ldi			r17, 5
	call		show_char

	lds			r16, ms1
	subi		r16, -'0'
	ldi			r17, 6
	call		show_char

	lds			r16, ms0
	subi		r16, -'0'
	ldi			r17, 7
	call		show_char

	ret

loop:
	call 		showTime
	
	in 			r16, PINE ; right
	in 			r17, PINE ; left
	in			r18, PINB ; enter
	andi		r16, 0x08
	andi		r17, 0x04
	andi		r18, 0x10

	tst			r16
	breq		start

	start_ret:

	tst			r17
	breq		stop

	stop_ret:
	
	tst			r18
	breq		reset

	reset_ret:
	
	;call		incMs
	jmp 		loop


reset:
	ldi			r16, 0x00
	sts			ms0, r16
	sts			ms1, r16
	sts			sec0, r16
	sts			sec1, r16
	sts			min0, r16
	sts			min1, r16
	sts			flag, r16
	jmp			reset_ret
		
stop:
	cli
	jmp 		stop_ret
	
start:
	sei
	jmp 		start_ret

main:

	; stack
	ldi 		r16, 0xFF
	out 		SPL, r16
	ldi 		r16, 0x04
	out 		SPH, r16

	; don't interrupt
	cli

	; display initialization
	call 		init_disp

	; joystick
	in 	 		r17, DDRE
	andi 		r17, 0xF3
	in 	 		r16, PORTE
	ori  		r16, 0x0C
	out  		DDRE, r17
	out  		PORTE, r16
	ldi  		r16, 0x00
	sts  		DIDR1, r16
	in   		r17, DDRB
	andi 		r17, 0x2F
	in   		r16, PORTB
	ori  		r16, 0xDF
	in	 		r16, PORTB
	ori  		r16, 0xD0
	out  		DDRB, r17
	out	 		PORTB, r16
	
	; interruptor initialization
	ldi 		r16, 0x08
	sts 		ASSR, r16
	ldi 		r16, 0x01
	sts 		TIMSK2, r16
	ldi 		r16, 0x01 ; here
	sts 		TCCR2A, r16
	clr 		r16
	out 		EIMSK, r16

	; some initialization
	call 		reset

	jmp 		loop
