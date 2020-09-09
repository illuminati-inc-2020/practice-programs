		LDA 00A0H
		CPI 02H
		JC NOT_PRIME		;if n<2 not prime
		JZ PRIME		;if n=2 prime
		MOV D,A			;D=n
		ANI 01H
		JZ NOT_PRIME		;if n|2 not prime
		MOV B,D
		CALL SQRT
		INR B
		MOV E,B			;E=SQRT(n)+1
		MVI H,03H		;H=counter
LOOP:		MOV C,D
		MOV B,H
		CALL DIVISION
		MOV A,B			;A=n%counter
		CPI 00H
		JZ NOT_PRIME		;n|counter not prime
		INR H
		INR H
		MOV A,H
		CMP E
		JC LOOP
PRIME:		MVI A,01H
		STA 00B0H
		HLT
NOT_PRIME:	MVI A,00H
		STA 00B0H
		HLT

; Input  : B = divider, C = dividend
; Output : B = remainder, C = quotient
DIVISION:	MOV A,C
		MVI C,00H
DIV_LOOP:	CMP B
		JC DIV_END
		SUB B
		INR C
		JMP DIV_LOOP
DIV_END:	MOV B,A
		RET

; Input  : B
; Output : B
SQRT:		MOV A,B
		MVI C,01H
		MVI B,00H
SQRT_LOOP:	CMP C
		JC SQRT_END
		SUB C
		INR C
		INR C
		INR B
		JMP SQRT_LOOP
SQRT_END:	RET