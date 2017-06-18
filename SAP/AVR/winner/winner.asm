
.include 	"m169def.inc"
.org 		0x1000
.include 	"print.inc"

.dseg

state:		.byte 3
number:		.byte 1
game:		.byte 1
winner:		.byte 1

prevBS:		.byte 1

.cseg

.org 		0x0000

jmp 		main

.org 		0x000A

jmp 		INT_WIN

.org 		0x0100

INT_WIN:
	; save data
	push 		r16
	in		r16, SREG
	push 		r16
	push		r17

	lds		r16, number
	cpi		r16, 0
	brne		inc1n	
	lds		r17, state
	jmp		changeSt

    inc1n:
	cpi		r16, 1
	brne		inc2n
	lds		r17, state+1
	jmp		changeSt

    inc2n:
	lds		r17, state+2

    changeSt:
	inc		r17
	cpi		r17, 10
	brlt		wrt
	ldi		r17, 0

    wrt:
	cpi		r16, 0
	brne		wrt1
	sts		state, r17
	jmp		rest

    wrt1:
	cpi		r16, 1
	brne		wrt2
	sts		state+1, r17
	jmp		rest

    wrt2:
	sts		state+2, r17

    rest:
	; restore data
	pop		r17
	pop		r16
	out		SREG, r16
	pop		r16
	
	reti

showState:
	lds		r16, game
	tst		r16
	breq		loseWinShow
	jmp		stateShow

    loseWinShow:
	lds		r16, winner
	tst		r16
	breq		loseShow
	jmp		winShow

    winShow:
	ldi		r16, 'W'
	ldi		r17, 2
	call		show_char
	ldi		r16, 'I'
	ldi		r17, 3
	call		show_char
	ldi		r16, 'N'
	ldi		r17, 4
	call		show_char
	ldi		r16, 'N'
	ldi		r17, 5
	call		show_char
	ldi		r16, 'E'
	ldi		r17, 6
	call		show_char
	ldi		r16, 'R'
	ldi		r17, 7
	call		show_char
	jmp		shown

    loseShow:
	ldi		r16, 'L'
	ldi		r17, 2
	call		show_char
	ldi		r16, 'O'
	ldi		r17, 3
	call		show_char
	ldi		r16, 'S'
	ldi		r17, 4
	call		show_char
	ldi		r16, 'E'
	ldi		r17, 5
	call		show_char
	ldi		r16, 'R'
	ldi		r17, 6
	call		show_char
	ldi		r16, ' '
	ldi		r17, 7
	call		show_char
	jmp		shown

    stateShow:
	lds		r16, state
	subi	r16, -'0'
	ldi		r17, 2
	call		show_char
	ldi		r16, ' '
	ldi		r17, 3
	call		show_char
	lds		r16, state+1
	subi	r16, -'0'
	ldi		r17, 4
	call		show_char
	ldi		r16, ' '
	ldi		r17, 5
	call		show_char
	lds		r16, state+2
	subi	r16, -'0'
	ldi		r17, 6
	call		show_char
	ldi		r16, ' '
	ldi		r17, 7
	call		show_char
	jmp		shown

    shown:
	ret

debugInterrupt:
	call		INT_WIN
	ret

loop:
	call 		showState
	;call		debugInterrupt
	
	in			r17, PINB ; enter
	andi		r17, 0x10
	lds			r16, prevBS
	cp			r17, r16
	brne		bsc

	jmp		loop

    bsc:
	sts			prevBS, r17
	lds			r16, game
	tst			r16
	breq		waitSec
	jmp			cccc

	ldi			r16, 0
	waitSec:
		inc			r16
		ldi			r17, 0
		waitSec1:
			inc			r17
			ldi			r18, 0
			waitSec2:
				inc			r18
				cpi			r18, 0xFF
				brlt		waitSec2
			cpi			r17, 0xFF
			brlt		waitSec1
		cpi			r16, 0xFF
		brlt		waitSec
	
	
	cccc:
	lds			r17, prevBS
	tst			r17
	breq		bp
	jmp			loop

	bp:

	call		buttonAction
	jmp			loop

buttonAction:
	lds			r16, game
	tst			r16
	brne		setState

    start:
	call		reset
	ldi			r16, 1
	sts			game, r16
	sei
	jmp			contGame

    setState:
	lds			r16, number
	cpi			r16, 2
	brsh		stopGame
	inc			r16
	sts			number, r16
	jmp			contGame

    stopGame:
	cli
	ldi			r16, 0
	sts			game, r16
	call		checkWinner

    contGame:
	ret
	
checkWinner:
	lds		r16, state
	lds		r17, state+1
	cp		r16, r17
	brne		lose
	lds		r16, state+2
	cp		r16, r17
	brne		lose
	ldi		r16, 1
	jmp		wrtWin

    lose:
	ldi		r16, 0

    wrtWin:
	sts		winner, r16

	ret

reset:
	ldi		r16, 0x00
	sts		state, r16
	sts		state+1, r16
	sts		state+2, r16
	sts		winner, r16
	sts		number, r16
	ret

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
	in 	 	r17, DDRE
	andi 		r17, 0xF3
	in 	 	r16, PORTE
	ori  		r16, 0x0C
	out  		DDRE, r17
	out  		PORTE, r16
	ldi  		r16, 0x00
	sts  		DIDR1, r16
	in   		r17, DDRB
	andi 		r17, 0x2F
	in   		r16, PORTB
	ori  		r16, 0xDF
	in	 	r16, PORTB
	ori  		r16, 0xD0
	out  		DDRB, r17
	out	 	PORTB, r16
	
	; interrupter initialization
	ldi 		r16, 0x08
	sts 		ASSR, r16
	ldi 		r16, 0x01
	sts 		TIMSK2, r16
	ldi 		r16, 0x03 ;;;;;;;;;3
	sts 		TCCR2A, r16
	clr 		r16
	out 		EIMSK, r16

	; some initialization
	call 		reset
	ldi			r16, 1
	sts			game, r16
	sei

	jmp 		loop
