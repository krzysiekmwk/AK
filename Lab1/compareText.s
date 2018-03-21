SYSEXIT = 1
EXIT_SUCCESS = 0

SYSWRITE = 4
STDOUT = 1

SYSREAD = 3
STDIN = 0

.text
msg: .ascii "Write text (5): \n"
msg_len = .-msg

msg2: .ascii "Written text: "
msg2_len = .-msg2

newline: .ascii "\n"
newline_len = .-newline

const: .ascii "test1"
const_len = .-const

alert: .ascii "NOT EQUAL!\n"
alert_len = .-alert

.data
buf: .ascii "     "
buf_len = .-buf

.global _start
_start:

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $msg, %ecx
mov $msg_len, %edx
int $0x80

mov $SYSREAD, %eax
mov $STDIN, %ebx
mov $buf, %ecx
mov $buf_len, %edx
int $0x80

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $msg2, %ecx
mov $msg2_len, %edx
int $0x80

mov $SYSWRITE, %eax
mov $STDOUT, %ebx
mov $buf, %ecx
mov $buf_len, %edx
int $0x80

MOV $SYSWRITE, %eax
MOV $STDOUT, %ebx
MOV $newline, %ecx
MOV $newline_len, %edx
int $0x80

#mov $buf, %esi
#mov $const, %edi
#mov $const_len, %ecx
#cld
#repe cmpsb
#jecxz _end
#cmp %ebx, %eax
#JNE _notEqual
#jmp _end

mov $0, %esi
mov $0, %cl
loop:
	mov const(,%esi,1), %al
	mov buf(,%esi,1), %bl
	inc %esi
	cmp %al, %bl
	jne _notEqual
	inc %cl
	cmp $buf_len, %cl
	jmp _end
	jmp loop

_notEqual:
MOV $SYSWRITE, %eax
MOV $STDOUT, %ebx
MOV $alert, %ecx
MOV $alert_len, %edx
int $0x80
jmp _end

_end:
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
