	LXI H,00A0H
	MOV C,M
	MVI B,00H
	DAD B
	LXI D,00B0H
LOOP:	MOV A,M
	XCHG
	MOV M,A
	XCHG
	DCX H
	INX D
	DCR C
	JNZ LOOP
	HLT