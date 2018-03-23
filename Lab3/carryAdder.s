.code32

.data
liczba1:
	.float 0.05	#inicjalizacja liczb zmiennym przecinkiem
			#jego dokladnosc ustawia sie w PC (precision control)
liczba2:
        .float 0.25

control_word: .short 0	#latwiejsze odwolanie sie do zmiennej


SYSEXIT = 1		#potrzebne do zakonczenia poprawnie programu
EXIT_SUCCESS = 0

.text
.global _start		#start programu
_start:

setControlWord:
	FSTCW control_word	#Pobranie aktualnego rejestru kontrolnego
	FWAIT 	#Odczekanie FPU wykona swoje zadanie
	MOV control_word, %ax 	#Zapis w rejestrze 16 bitowy

	#Ustawienie precyzji
	AND $0xFCFF, %ax 	#1111 1100 1111 1111 - wyzerowanie PC
	OR $0x0000, %ax 	#SINGLE PRECISION - 32bit /24 REAL4
	#OR $0x0200, %ax 	#DOUBLE PRECISION - 64bit /53 REAL8
	#OR $0x0300, %ax 	#EXTENDED PRECISION - 80bit /64 REAL10

	#Ustawienie zaokraglen
	AND $0xF3FF, %ax 	#1111 1100 1111 1111 - wyzerowanie RC
	OR $0x0000, %ax 	#Zaokraglenie do najblizszej lub parzystej
	#OR $0x0400, %ax 	#Zaokraglenie w dol
	#OR $0x0800, %ax 	#Zaokraglenie w gore
	#OR $0x0C00, %ax 	#obciecie do 0

	MOV %ax, control_word
	FLDCW control_word	#Ustawienie wybranej precyzji

setNumbers:
	#FLDL liczba1	#Wrzucenie liczby DOUBLE
	#FLD liczba1	#Wrzucenie liczby FLOAT

	FLDL liczba1	#Wepchniecie na STOS FPU ST0
	FST %st(6)	#Przeniesienei na 1 pozycje (pozniej znajdzie sie na 2)
	FLDL liczba2	#Wepchniecie na STOS FPU ST0, poprzedni sie przesunie na ST1
	FST %st(6)	#Przeniesienei na 1 pozycje

add:	#Dodawanie
	
sub:	#Odejmowanie

mul:	#mnozenie

div:	#dzielenie

sqrt:	#pierwiastek - dobre do wygenerowania NaN sqrt(-1)
	
exit:
	MOV $SYSEXIT, %eax
	MOV $EXIT_SUCCESS, %ebx
	INT $0x80
