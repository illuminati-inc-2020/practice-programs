;Input		: 00A0H <- divider
;		  00B0H <- dividend
;Output		: 00C0H <- remainder
;		  00D0H <- quotient
	LHLD 00A0H
	XCHG 			;DE <- divider/remainder
	LHLD 00B0H		;HL <- dividend
	LXI B, 0000H		;BC <- quotient
LOOP:	MOV A, H
	CMP D
	JC END			;if H<D break
	JNZ CONT		;if H>D continue
	MOV A, L
	CMP E
	JC END			;if L<E break
CONT:	MOV A, L
	SUB E
	MOV L, A
	MOV A, H
	SBB D
	MOV H, A
	INX B
	JMP LOOP
END:	SHLD 00C0H
	MOV H, B
	MOV L, C
	SHLD 00D0H
	HLT