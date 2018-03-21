all: calculator clear

calculator: calculator.o
	ld -o calculator calculator.o -m elf_i386
calculator.o: calculator.s
	as --32 -o calculator.o -g calculator.s

clear:
	rm -f *.o
