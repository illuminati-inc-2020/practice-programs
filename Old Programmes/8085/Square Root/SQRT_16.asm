;Square root of a 16 bit number
;Input		: 00A0H, 00A1H
;Output		: 00B0H
	LHLD 00A0H
	MVI C, 00H
	LXI D, 0001H
LOOP:	MOV A, L
	SUB E
	MOV L, A
	MOV A, H
	SBB D
	MOV H, A
	INX D
	INX D
	INR C
	MOV A, D
	CMP H
	JC LOOP		;if D<H continue
	JNZ END		;if D>H break
	MOV A, E
	CMP L
	JC LOOP		;if D=H and E<L continue
	JZ LOOP		;if D=H and E=L continue
END:	MOV A, C
	STA 00B0H
	HLT