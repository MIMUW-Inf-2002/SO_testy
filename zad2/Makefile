N = 10
CFLAGS = -z noexecstack -pedantic -Wall -Wextra -Werror -std=c17 -lpthread -DN=$(N)
CC = gcc

TESTS = kwasow_simple basic_sync fib fib2 sync

all: options solve $(TESTS:=.o)
	for i in $(TESTS); do $(CC) $(CFLAGS) -o $$i $$i.o core.o; done
	for i in $(TESTS); do echo "Running $$i"; ./$$i; if [ $$? -eq 0 ]; then echo "\e[42mPassed\e[0m"; else echo "\e[31mFailed\e[0m"; fi; done

options:
	@echo "build options:"
	@echo "CFLAGS = $(CFLAGS)"
	@echo "CC     = $(CC)"
	@echo "N      = $(N)"

solve: core.asm
	nasm -DN=$(N) -f elf64 -w+all -w+error -o core.o core.asm

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TESTS)
