;Add N 8 bit numbers
;Input	: 00A0H <- N
;	  00A1H <- list start
;Output	: 00B0H <- sum
	LXI H, 00A0H
	MOV C, M
	MVI D, 00H
	MVI E, 00H
LOOP:	INX H
	MOV A, M
	ADD E
	MOV E, A
	MVI A, 00H
	ADC D
	MOV D, A
	DCR C
	JNZ LOOP
	STA 00B1H
	MOV A, E
	STA 00B0H
	HLT