SYSWRITE = 4
STDOUT = 1
SYSEXIT = 1
EXIT_CODE = 0

.section .data
liczba1:
	.long 0x10304008, 0x701100FF, 0x45100020, 0x08570030
liczba2:
	.long 0xF040500C, 0x00220026, 0x321000CB, 0x04520031

liczba1_len = .-liczba1
liczba2_len = .-liczba2

.global _start
_start:
	mov $4, %edx
	clc

exit:
	mov $SYSEXIT, %eax
	mov $EXIT_CODE, %ebx
	int $0x80
