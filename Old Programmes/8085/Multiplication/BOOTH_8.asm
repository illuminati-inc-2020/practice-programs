	MVI B,00H		;B=0
	LDA 00A1H
	MOV D,A			;D=multiplicand
	MVI E,08H		;E=8
	LDA 00A0H
	MOV C,A			;C=multiplier
LOOP:	ANI 01H
	MOV A,B
	JZ SHIFT		;if C0=0 shift
	ADD D			;else B=B+D and shift
SHIFT:	RAR
	MOV B,A
	MOV A,C
	RAR
	MOV C,A			;shift right (carry,B,C)
	DCR E			;E=E-1
	JNZ LOOP		;loop while E<0
	STA 00B0H		;B,C=solution
	MOV A,B
	STA 00B1H
	HLT