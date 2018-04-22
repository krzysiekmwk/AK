all: lab4 lab4cAsm clear

lab4: lab4.c
	gcc -o lab4 -g lab4.c -mmmx -msse2
	
lab4cAsm: lab4cAsm.c
	gcc -o lab4cAsm -g lab4cAsm.c -mmmx -msse2

clear:
	rm -f *.o
