	LDA 00A0H
	MOV B,A		;B=Number of data
	LXI SP,0FFFFH
	LXI H,00C0H
	PUSH H		;Stack Top=Output address=00C0H
	MVI A,00H	;A=Data
LOOP1:	LXI H,00B0H	;HL=Input address=00B0H
	MOV C,B		;C=Counter
	CALL FREQ
	MOV E,A		;E=Temp for data
	MOV A,D
	CPI 00H
	JZ FREQ0
	XTHL
	MOV M,E
	INX H
	MOV M,D
	INX H
	XTHL
FREQ0:	MOV A,E
	DCR A
	JNZ LOOP1
	HLT

;FREQUENCY SUBROUTINE
;A,C,D,H,L Registers affected
;Input	:	C=Number of data
;		A=Data
;		HL=Base address of list
;Output	:	D=Frequency

FREQ:		MVI D,00H
FREQ_LOOP:	CMP M
		JNZ FREQ_ENDIF
		INR D
FREQ_ENDIF:	INX H
		DCR C
		JNZ FREQ_LOOP
		RET