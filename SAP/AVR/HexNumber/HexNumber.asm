; definice pro nas typ procesoru
.include "m169def.inc"
; podprogramy pro praci s displejem
.org 0x1000
.include "print.inc"

; Zacatek programu - po resetu
.org 0
jmp start

; Zacatek programu - hlavni program
.org 0x100
start:
    ; Inicializace zasobniku
	ldi r16, 0xFF
	out SPL, r16
	ldi r16, 0x04
	out SPH, r16
    ; Inicializace displeje
	call init_disp

	; *** ZDE muzeme psat nase instrukce
	ldi r25, 0x1B
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
	ldi r17, 2
	call show_char
	mov r16, r25
	ldi r17, 3
	call show_char	

	; Zastavime program - nekonecna smycka
	rjmp PC

ifA:
	subi r25, 0x0A
    subi r25, -65
	jmp continue
if0:
	subi r25, -48
	jmp continue
