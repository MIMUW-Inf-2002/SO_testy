N = 10
CFLAGS = -z noexecstack -pedantic -Wall -Wextra -Werror -std=c17 -pthread -DN=$(N)
CC = gcc

TESTS = kwasow_simple basic_sync fib fib2 sync

all: options solve $(TESTS:=.o) kwasow_advanced
	for i in $(TESTS); do $(CC) $(CFLAGS) -o $$i $$i.o core.o; done
	for i in $(TESTS); do echo "Running $$i"; ./$$i; if [ $$? -eq 0 ]; then echo "\e[42mPassed\e[0m"; else echo "\e[31mFailed\e[0m"; fi; done
	@echo "Running kwasow_advanced"
	@./kwasow_advanced
	@echo "\e[1;43mCheck output to see if passed\e[0m"

options:
	@echo "build options:"
	@echo "CFLAGS = $(CFLAGS)"
	@echo "CC     = $(CC)"
	@echo "N      = $(N)"

solve: core.asm
	nasm -DN=$(N) -f elf64 -w+all -w+error -o core.o core.asm

kwasow_advanced: kwasow_advanced.c kwasow_advanced.asm solve
	nasm -DN=1 -f elf64 -w+all -w+error -o kwasow_advanced_asm kwasow_advanced.asm
	gcc -c -Wall -Wextra -std=c17 -g -o kwasow_advanced_c kwasow_advanced.c
	gcc -g -z noexecstack -o kwasow_advanced kwasow_advanced_c core.o kwasow_advanced_asm

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TESTS)
