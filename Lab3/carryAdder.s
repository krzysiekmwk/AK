.code32

.data
liczba1:
	.long 0xF0000002, 0x10000011, 0xF0000004, 0xF0000001
liczba2:
        .long 0xF0000002, 0x20000026, 0x90000002, 0x00000001


SYSEXIT = 1
EXIT_SUCCESS = 0

.text
.global _start
_start:

	MOV $3, %edx
	CLC
	PUSHF

loop:
	MOV liczba1(,%edx,4), %eax
	MOV liczba2(,%edx,4), %ebx

	POPF
	ADC %ebx, %eax
	PUSH %eax
	PUSHF
	SUB $1, %edx
	CMP $-1, %edx
	JNE loop
	POPF
	JNC mov0toEAX
	MOV $1, %eax
	JMP push

mov0toEAX:
	MOV $0, %eax
push:
	PUSH %eax
exit:
	MOV $SYSEXIT, %eax
	MOV $EXIT_SUCCESS, %ebx
	INT $0x80
