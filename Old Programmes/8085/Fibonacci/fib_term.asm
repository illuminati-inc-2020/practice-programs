;PRINT N-TH FIBONACCI TERM
;INPUT	: 00A0H
;OUTPUT	: 00B0H
	LDA 00A0H
	MOV C, A
	MVI D, 00H
	MVI E, 01H
LOOP:	DCR C
	JZ END
	MOV A, D
	ADD E
	MOV D, E
	MOV E, A
	JMP LOOP
END:	MOV A, D
	STA 00B0H
	HLT