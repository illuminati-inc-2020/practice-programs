;Add N 16 bit numbers
;Input	: 00A0H <- N
;	  00A1H <- list start
;Output	: 00B0H <- sum
	LXI H, 00A0H
	MOV C, M
	MVI B, 00H
	MVI D, 00H
	MVI E, 00H
LOOP:	INX H
	MOV A, M
	ADD E
	MOV E, A
	INX H
	MOV A, M
	ADC D
	MOV D, A
	MVI A, 00H
	ADC B
	MOV B, A
	DCR C
	JNZ LOOP
	STA 00B2H
	MOV A, D
	STA 00B1H
	MOV A, E
	STA 00B0H
	HLT