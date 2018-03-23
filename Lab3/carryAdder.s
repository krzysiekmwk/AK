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

	FLD liczba1	#Wepchniecie na STOS FPU ST1
	FLD liczba2	#Wepchniecie na STOS FPU ST0, poprzedni sie przesunie na ST1
	FST %st(2)	#Skopiowania ST0 na STOS FPU ST2

	#Wyswietlanie: info float - moze byc przydatne, ale nie do konca poprawnie wyswietla
	#p $st0 - wyswietla dokladnie dana komorke

add:	#Dodawanie
	FXCH %st(2)	#zamiana ST0 z ST2
	FST %st(2)	#Skopiowanie ST0 do ST2
	FADD %st(1), %st(0)	#ST0 = liczba2 + liczba1; zrodlo -> cel; cel = cel + zrodlo
	FST %st(3)	#Skopiowanie wyniku na ST3

sub:	#Odejmowanie
	FXCH %st(2)	#zamiana ST0 z ST2
	FST %st(2)	#Skopiowanie ST0 do ST2
	FSUB %st(1), %st(0)	#ST0 = liczba2 - liczba1; zrodlo -> cel; cel = cel - zrodlo
	FST %st(4)	#Skopiowanie wyniku na ST4

mul:	#mnozenie
	FXCH %st(2)	#zamiana ST0 z ST2
	FST %st(2)	#Skopiowanie ST0 do ST2
	FMUL %st(1), %st(0)	#ST0 = liczba2 - liczba1; zrodlo -> cel; cel = cel * zrodlo
	FST %st(5)	#Skopiowanie wyniku na ST5

div:	#dzielenie
	FXCH %st(2)	#zamiana ST0 z ST2
	FST %st(2)	#Skopiowanie ST0 do ST2
	FDIV %st(1), %st(0)	#ST0 = liczba2 - liczba1; zrodlo -> cel; cel = cel / zrodlo
	FST %st(6)	#Skopiowanie wyniku na ST6

sqrt:	#pierwiastek - dobre do wygenerowania NaN sqrt(-1)
	
exit:
	MOV $SYSEXIT, %eax
	MOV $EXIT_SUCCESS, %ebx
	INT $0x80
