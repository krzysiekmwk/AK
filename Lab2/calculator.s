.code32

.data
liczba1:
	.long 0xF0000002, 0x00000003, 0xF0000004, 0x00000001
liczba2:
        .long 0xF0000002, 0x00000001, 0x10000002, 0x00000001


SYSEXIT = 1
EXIT_SUCCESS = 0

.text
.global _start
_start:

	mov $3, %edx
	clc
	pushf

loop:
	mov liczba1(,%edx,4), %eax
	mov liczba2(,%edx,4), %ebx
	sub $1, %edx

	popf
	adcl %ebx, %eax
	push %eax
	pushf
	cmp $0, %edx
	jne loop

exit:
	mov $SYSEXIT, %eax
	mov $EXIT_SUCCESS, %ebx
	int $0x80
