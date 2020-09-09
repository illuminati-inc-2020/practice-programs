;Multiplication of 2 2byte numbers using repeatative addition
;Input		: 00A0H, 00A1H <- Multiplicand
;		: 00B0H, 00B1H <- Multiplier
;Output		: 00C0H, 00C1H, 00C2H, 00C3H <- Product
	LHLD 00A0H
	MOV B, H
	MOV C, L
	LHLD 00B0H
	LXI SP, 00D0H
	XTHL
	MVI D, 00H
	MOV E, D
	MOV H, E
	MOV L, H
LOOP:	SUB A
	DAD B
	ADC E
	ADC D
	XTHL
	DCX H
	MOV A, H
	ORA L
	XTHL
	JNZ LOOP
	SHLD 00C0H
	MOV H, D
	MOV L, E
	SHLD 00C2H
	HLT