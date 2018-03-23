all: carryAdder borrowSubtract clear

carryAdder: carryAdder.o
	ld -o carryAdder carryAdder.o -m elf_i386
carryAdder.o: carryAdder.s
	as --32 -o carryAdder.o -g carryAdder.s

borrowSubtract: borrowSubtract.o
	ld -o borrowSubtract borrowSubtract.o -m elf_i386
borrowSubtract.o: borrowSubtract.s
	as --32 -o borrowSubtract.o -g borrowSubtract.s

clear:
	rm -f *.o
