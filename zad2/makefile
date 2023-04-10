fib: core.o fib.o
	gcc -z noexecstack -pthread -o fib core.o fib.o

fib.o: fib.c
	gcc -c -Wall -Wextra -std=c17 -O2 -o fib.o fib.c

core.o: core.asm
	nasm -DN=3 -f elf64 -w+all -w+error -o core.o core.asm
