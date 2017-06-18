.include "m169def.inc"
.org 0x1000
.include "print.inc"

.org 0
jmp start

.org 0x100
start:

	ldi r16, 0x01
	subi r16, 0x01
	ldi r16, 0xFF
	out SPL, r16
	ldi r16, 0x04
	out SPH, r16
	call init_disp
; Set registers
	ldi r16, 0x0A
	ldi r17, 0x0C
	ldi r18, 0x64
; r16 * 4
	ldi r19, 0x04
	muls r16, r19
	mov r20, r1
	mov r21, r0
; + r17 * 3
	ldi r19, 0x03
	mul r17, r19
	add r21, r0
	adc r20, r1
; - r18
	sub r21, r18
	brcc noMove
	subi r20, 1

noMove:
; / 8
	mov r25, r20
	mov r26, r21

; fract byte
	mov r28, r21
	lsl r28
	lsl r28
	lsl r28
	lsl r28
	lsl r28
	mov r22, r28

; lower byte
	lsr r26
	lsr r26
	lsr r26
	mov r27, r25
	lsl r27
	lsl r27
	lsl r27
	lsl r27
	lsl r27
	or r26, r27
	mov r21, r26

; higher byte
	asr r25
	asr r25
	asr r25
	mov r20, r25

	; cycle counter
	ldi r30, 0x00
	mov r25, r20
	ldi r17, 2
	jmp printNum
cont1:
	mov r25, r21
	ldi r30, 0x01
	jmp printNum
cont2:
	mov r25, r22
	ldi r30, 0x03
	jmp printNum
	

printNum:
	mov r16, r25
	mov r18, r25

	; Mask registers
	lsr r16
	lsr r16
	lsr r16
	lsr r16
	andi r18, 0b00001111
	
	; Compare registers
firstCond:
	mov r25, r16
	cpi r25, 0x0A
	ldi r26, 0x00
	brge ifA
	brlt if0
secondCond:
	mov r16, r25
	mov r25, r18
	cpi r25, 0x0A
	ldi r26, 0x01
	brge ifA
	brlt if0
continue:
	cpi r26, 0x00
	breq secondCond
	call show_char
	mov r16, r25
	subi r17, -1
	call show_char	
	subi r17, -1
	cpi r30, 0x00
	breq cont1
	cpi r30, 0x01
	breq cont2
	rjmp PC

ifA:
	subi r25, 0x0A
    subi r25, -65
	jmp continue
if0:
	subi r25, -48
	jmp continue
