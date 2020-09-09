		LDA 00A0H		
		MVI B,64H
		MOV C,A
		CALL DIVISION		;Division by 100
		MOV A,C
		STA 00B0H
		MOV C,B
		MVI B,0AH
		CALL DIVISION		;Division by 10
		ADI 00H
		MOV A,C
		RLC
		RLC
		RLC
		RLC
		ORA B
		STA 00B1H
		HLT

; Input  : B = divider, C = dividend
; Output : B = remainder, C = quotient
DIVISION:	MOV A,C				;4
		MVI C,00H			;7
DIV_LOOP:	CMP B				;4
		JC DIV_END			;10
		SUB B				;4
		INR C				;4
		JMP DIV_LOOP			;10
DIV_END:	MOV B,A				;4
		RET				;10
;4+7+(4+7+4+4+10)*q+4+10+4+10