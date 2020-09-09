;Add 2 N-byte numbers
;Input	: 00A0H <- N
;	: 00B0H <- first number
;	: 00C0H <- second number
;Output : 00D0h <- sum
	LDA 00A0H
	MOV C, A
	LXI SP, 0FFFFH
	LXI H, 00D0H
	PUSH H
	LXI H, 00B0H
	LXI D, 00C0H
	SUB A
LOOP:	RAR
	MOV A, M
	INX H
	XCHG
	ADC M
	INX H
	XTHL
	MOV M, A
	INX H
	XTHL
	RAL
	DCR C
	JNZ LOOP
	XTHL
	ANI 01H
	MOV M, A
	HLT