	LDA 00A0H
	MOV B,A
	RAR			;4 bit right shift
	RAR
	RAR
	RAR
	ANI 0FH
	XRA B
	MOV B,A
	RAR			;2 bit right shift
	RAR
	ANI 3FH
	XRA B
	MOV B,A
	RAR			;1 bit right shift
	ANI 7FH
	XRA B
	STA 00B0H
	HLT