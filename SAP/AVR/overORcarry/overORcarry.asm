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

	; Set numbers
	ldi r16, 0x00
	ldi r17, 0x00
	ldi r18, 0x00
	ldi r19, 0x80
	ldi r20, 0x00
	ldi r21, 0x00
	ldi r22, 0x00
	ldi r23, 0x80

	; Is there a sign? 
	jmp signed
	jmp unsigned

unsigned:
	add r16, r20
	adc r17, r21
	adc r18, r22
	adc r19, r23
	brcs carry
	jmp good

signed:
	tst r19
	brmi signed_neg1

signed_cont1:
	tst r23
	brmi signed_neg2

signed_cont2:
	add r16, r20
	adc r17, r21
	adc r18, r22
	adc r19, r23
	
	mov r25, r19
	andi r25, 0x80
	cpi r25, 0x80
	breq overflow
	jmp good

signed_neg1:
	ldi r25, 0xFF
	eor r16, r25
	eor r17, r25
	eor r18, r25
	eor r19, r25
	ldi r25, 0x01
	ldi r26, 0x00
	adc r16, r25
	adc r17, r26
	adc r18, r26
	adc r19, r26
	mov r25, r19
	andi r25, 0x80
	tst r25
	breq signed_cont1
	jmp overflow

signed_neg2:
	ldi r25, 0xFF
	eor r20, r25
	eor r21, r25
	eor r22, r25
	eor r23, r25
	ldi r25, 0x01
	ldi r26, 0x00
	adc r20, r25
	adc r21, r26
	adc r22, r26
	adc r23, r26
	mov r25, r23
	andi r25, 0x80
	tst r25
	breq signed_cont2
	jmp overflow
	
carry:
	ldi r16, 'C'
	ldi r17, 2
	call show_char
	ldi r16, 'A'
	ldi r17, 3
	call show_char
	ldi r16, 'R'
	ldi r17, 4
	call show_char
	ldi r16, 'R'
	ldi r17, 5
	call show_char
	ldi r16, 'Y'
	ldi r17, 6
	call show_char
	jmp main

overflow:
	ldi r16, 'O'
	ldi r17, 2
	call show_char
	ldi r16, 'V'
	ldi r17, 3
	call show_char
	ldi r16, 'E'
	ldi r17, 4
	call show_char
	ldi r16, 'R'
	ldi r17, 5
	call show_char
	jmp main

good:
	ldi r16, 'G'
	ldi r17, 2
	call show_char
	ldi r16, 'O'
	ldi r17, 3
	call show_char
	ldi r16, 'O'
	ldi r17, 4
	call show_char
	ldi r16, 'D'
	ldi r17, 5
	call show_char
	jmp main

main:
	rjmp PC


