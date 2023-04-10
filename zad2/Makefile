N = 1000
CFLAGS = -pedantic -Wall -Wextra -Werror -std=c17 -lpthread -DN=$(N)
CC = gcc

TESTS = rentib

all: options solve $(TESTS:=.o)
	for i in $(TESTS); do $(CC) $(CFLAGS) -o $$i $$i.o core.o; done
	for i in $(TESTS); do echo "Running $$i"; ./$$i; echo "Passed"; done

options:
	@echo "build options:"
	@echo "CFLAGS = $(CFLAGS)"
	@echo "CC     = $(CC)"
	@echo "N      = $(N)"

solve: core.asm
	nasm -DN=$(N) -f elf64 -w+all -w+error -o core.o core.asm
	
fib: core.o fib.o
	gcc -z noexecstack -pthread -o fib core.o fib.o

fib.o: fib.c
	gcc -c -Wall -Wextra -std=c17 -O2 -o fib.o fib.c

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TESTS)
