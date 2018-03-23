all: carryAdder clear

carryAdder: carryAdder.o
	ld -o carryAdder carryAdder.o -m elf_i386
carryAdder.o: carryAdder.s
	as --32 -o carryAdder.o -g carryAdder.s

clear:
	rm -f *.o
