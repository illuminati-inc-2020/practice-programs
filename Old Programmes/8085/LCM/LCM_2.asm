;LCM OF 2 NUMBERS
;INPUT			: 00A0H, 00A1H
;OUTPUT			: 00B0H
		LXI H, 00A0H
		MOV D, M
		INX H
		MOV E, M
		MOV B, D
		MOV C, E
		CALL MUL
		MOV H, B
		MOV B, D
		MOV C, E
		CALL GCD
		MOV C, H
		CALL DIV
		MOV A, C
		STA 00B0H
		HLT
		
;MULTIPLICATION OF 2 NUMBERS
;INPUT			: B, C
;OUTPUT			: B
;REGISTERS AFFECTED	: A, B, C
MUL:		SUB A
MUL_LOOP:	ADD B
		DCR C
		JNZ MUL_LOOP
		MOV B, A
		RET

;GCD OF 2 NUMBERS
;INPUT			: B, C
;OUTPUT			: B
;REGISTERS AFFECTED	: A, B, C
GCD:		MOV A, B
		CMP C 
		JC GCD_ELSE
		SUB C
		MOV B, A
		JMP GCD_ENDIF
GCD_ELSE:	MOV A, C
		SUB B
		MOV C, A
GCD_ENDIF:	MOV A, B
		CMP C
		JNZ GCD
		MOV B,A
		RET

;DIVISION
;INPUT  		: B=DIVIDER, C=DIVIDEND
;OUTPUT			: B=REMAINDER, C=QUOTIENT
;REGISTERS AFFECTED	: A, B, C
DIV:		MOV A,C
		MVI C,00H
DIV_LOOP:	CMP B
		JC DIV_END
		SUB B
		INR C
		JMP DIV_LOOP
DIV_END:	MOV B,A
		RET

