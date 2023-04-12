N = 10
CFLAGS = -z noexecstack -pedantic -Wall -Wextra -Werror -std=c17 -lpthread -DN=$(N)
CC = gcc

TESTS = kwasow_simple basic_sync fib fib2 sync

all: options solve core_test $(TESTS:=.o) kwasow_advanced
	for i in $(TESTS); do $(CC) $(CFLAGS) -o $$i $$i.o core_test.o core.o; done
	for i in $(TESTS) kwasow_advanced; do echo "Running $$i"; ./$$i; if [ $$? -eq 0 ]; then echo "\e[42mPassed\e[0m"; else echo "\e[31mFailed\e[0m"; fi; done

options:
	@echo "build options:"
	@echo "CFLAGS = $(CFLAGS)"
	@echo "CC     = $(CC)"
	@echo "N      = $(N)"

solve: core.asm
	nasm -DN=$(N) -f elf64 -w+all -w+error -o core.o core.asm

core_test: solve core_test.asm
	nasm -f elf64 -w+all -w+error -o core_test.o core_test.asm

kwasow_advanced: kwasow_advanced.c kwasow_advanced.asm solve core_test
	nasm -DN=1 -f elf64 -w+all -w+error -o kwasow_advanced_asm kwasow_advanced.asm
	gcc -c -Wall -Wextra -std=c17 -g -o kwasow_advanced_c kwasow_advanced.c
	gcc -g -z noexecstack -o kwasow_advanced kwasow_advanced_c core.o core_test.o kwasow_advanced_asm

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TESTS)
