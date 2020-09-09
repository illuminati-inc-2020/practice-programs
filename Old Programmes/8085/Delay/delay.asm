	MVI C,01H
	CALL DELAY
	HLT


; Delay Subroutine
; Create delays in second for 3MHz microprocessor
; Input from register C
; Destroys A,C,H,L
DELAY:	LXI H,0F424H
LOOP:	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	DCX H
	MOV A,H
	ORA L
	JNZ LOOP
	DCR C
	JNZ DELAY
	RET