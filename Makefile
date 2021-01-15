NASM = nasm -g -f elf32
GCC = gcc -m32 -Wall -g
ALL_NAMES = main.o root.o integral.o funct.o funct_test.o

.PHONY: all clean

all: square

square: $(ALL_NAMES)
	$(GCC) $^ -o square -lm

main.o: main.c funct.h math_module.h
	$(GCC) -c $<

root.o: root.c
	$(GCC) -c $^

integral.o: integral.c
	$(GCC) -c $^

funct.o: funct.asm
	$(NASM) $^

funct_test.o: funct_test.c
	$(GCC) -c $^ 

clean:
	rm -rf *.o
