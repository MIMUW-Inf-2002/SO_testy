#!/bin/sh

nasm -f elf64 -w+all -w+error -o inverse_permutation.o inverse_permutation.asm && \
gcc -c -Wall -Wextra -std=c17 -o main.o main.c && \
gcc -z noexecstack -o main main.o inverse_permutation.o
