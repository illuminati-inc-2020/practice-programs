;Multiplication of 2 2byte numbers using repeatative addition
;Input		: 00A0H, 00A1H <- Multiplier
;		: 00B0H, 00B1H <- Multiplicand
;Output		: 00C0H, 00C1H, 00C2H, 00C3H <- Product
	LHLD 00A0H
	SPHL		;SP <- multiplier
	LHLD 00B0H
	MOV D, H
	MOV E, L	;DE <- multiplicand
	MVI H, 00H
	MOV L, H	;HLDE <- product
	MVI C, 10H	;C <- counter
LOOP:	MOV A, E
	ANI 01H
	JZ SHIFT
	DAD SP
SHIFT:	MOV A, H
	RAR
	MOV H, A
	MOV A, L
	RAR
	MOV L, A
	MOV A, D
	RAR
	MOV D, A
	MOV A, E
	RAR
	MOV E, A
	DCR C
	JNZ LOOP
	SHLD 00C2H
	MOV H, D
	MOV L, E
	SHLD 00C0H
	HLT