		LDA 00A0H
		MOV B,A
		MVI C,64H
		CALL MULTIPLY
		MOV E,B
		LDA 00A1H
		MOV D,A
		ANI 0F0H
		ADI 00H
		RAR
		RAR
		RAR
		RAR
		MOV B,A
		MVI C,0AH
		CALL MULTIPLY
		MOV A,E
		ADD B
		MOV E,A
		MOV A,D
		ANI 0FH
		ADD E
		STA 00B0H
		HLT

;Input  : B,C 
;Output : B
MULTIPLY:	SUB A
MUL_LOOP:	ADD B
		DCR C
		JNZ MUL_LOOP
		MOV B,A
		RET