.include "m169def.inc"
.org 0x1000
.include "print.inc"

.org 0

str: .db "SOME STRING MOVING ", 0

.dseg
ctr: .byte 3
.cseg

jmp start

.org 0x100

clock:
	ldi r16, 0
	sts ctr, r16
	sts ctr+1, r16
	sts ctr+2, r16

	incr0:
		lds r16, ctr
		inc r16
		tst r16
		sts ctr, r16
		breq incr1
		jmp incr0

	incr1:
		lds r16, ctr+1	
		inc r16
		tst r16
		sts ctr+1, r16
		breq incr2
		jmp incr0

	incr2:
		lds r16, ctr+2
		inc r16	
		cpi r16, 0x02
		sts ctr+2, r16
		brne incr0

	ret

showString:
	ldi r30, low( str << 1 )
	ldi r31, high( str << 1 )
	add r30, r18
	call a1
	lpm
	mov r16, r0
	ldi r17, 2
	call show_char

	ldi r30, low( str << 1 )
	ldi r31, high( str << 1 )
	add r30, r19
	call a1
	lpm
	mov r16, r0
	ldi r17, 3
	call show_char

	ldi r30, low( str << 1 )
	ldi r31, high( str << 1 )
	add r30, r20
	call a1
	lpm
	mov r16, r0
	ldi r17, 4
	call show_char

	ldi r30, low( str << 1 )
	ldi r31, high( str << 1 )
	add r30, r21
	call a1
	lpm
	mov r16, r0
	ldi r17, 5
	call show_char

	ldi r30, low( str << 1 )
	ldi r31, high( str << 1 )
	add r30, r22
	call a1
	lpm
	mov r16, r0
	ldi r17, 6
	call show_char

	ldi r30, low( str << 1 )
	ldi r31, high( str << 1 )
	add r30, r23
	call a1
	lpm
	mov r16, r0
	ldi r17, 7
	call show_char

	ret
	
	a1: 
		brcs a0
		ret
	a0: inc r31
		clc
		jmp a1
	

getLen:
	ldi r25, 0
	ldi r30, low( str << 1 )
	ldi r31, high( str << 1 )

	moveSym:
		inc r25
		lpm
		adiw r30, 1
		tst r0
		brne moveSym
	dec r25
	ret		

mainLoop:
	
	call showString

	inc r18
	inc r19
	inc r20
	inc r21
	inc r22
	inc r23

	cp r18, r25
	breq mL18
	mL0:
	cp r19, r25
	breq mL19
	mL1:
	cp r20, r25
	breq mL20
	mL2:
	cp r21, r25
	breq mL21
	mL3:
	cp r22, r25
	breq mL22
	mL4:
	cp r23, r25
	breq mL23
	mL5:
	call clock
	jmp mainLoop

	mL18:
		ldi r18, 0
		jmp mL0
	mL19:
		ldi r19, 0
		jmp mL1
	mL20:
		ldi r20, 0
		jmp mL2
	mL21:
		ldi r21, 0
		jmp mL3
	mL22:
		ldi r22, 0
		jmp mL4
	mL23:
		ldi r23, 0
		jmp mL5
	

start:
	ldi r16, 0xFF
	out SPL, r16
	ldi r16, 0x04
	out SPH, r16

	call init_disp

	call getLen

	ldi r18, 0
	ldi r19, 1
	ldi r20, 2
	ldi r21, 3
	ldi r22, 4
	ldi r23, 5

	call mainLoop

	rjmp PC

