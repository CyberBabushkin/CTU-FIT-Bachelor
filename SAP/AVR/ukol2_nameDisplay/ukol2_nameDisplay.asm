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
	ldi r16, 'A'	; znak
	ldi r17, 2
	call show_char
	ldi r16, 'N'
	ldi r17, 3
	call show_char
	ldi r16, 'D'
	ldi r17, 4
	call show_char
	ldi r16, 'R'
	ldi r17, 5
	call show_char
	ldi r16, 'E'
	ldi r17, 6
	call show_char
	ldi r16, 'Y'
	ldi r17, 7
	call show_char

	; Zastavime program - nekonecna smycka
	rjmp PC
