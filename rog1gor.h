/* Autor - Igor Kamiński */
/* UWAGA: część kodu została zapożyczona z pliku rentib.h oraz testów dołączonych do zadania */
#ifndef ROG1GOR_H_
#define ROG1GOR_H_

#include "inverse_permutation.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TESTS_COUNT 1000000

//? Wartość używana do określania maksymalnej wielkości tablicy
//? Testowane będa tablice z zakresu od 1 do SIZE_OF_ARRAY_BOUND
//? Można odkomentować maksymalną wielkość tablicy, jednak testy działają długo
//? Polecam zdecydowanie zmniejszyć liczbę testów podczas testowania na dużych tablicach
#define SIZE_OF_ARRAY_BOUND 1000
//! #define SIZE_OF_ARRAY_BOUND 2147483647 //? Wielkość tablicy musi być mniejsza lub równa niż ta wartość

//? Sprawdzenie czy permutacja została poprawnie odwrócona
static bool check_reverse(size_t n, int const *p1, int const *p2) {
    for (size_t i = 0; i < n; ++i) {
        if ((size_t)p2[p1[i]] != i)
            return false;
    }
    return true;
}

//? Sprawdzenie czy tablica pozostała bez zmian
static bool is_untouched(size_t n, int const *p1, int const *p2) {
    for (size_t i = 0; i < n; ++i) {
        if (p1[i] != p2[i])
            return false;
    }
    return true;
}

//? Generuje losowego inta
static int random_integer() {
    int random_int = rand();
    //? 25% szans na wygenerowanie liczby ujemnej
    //? Przypadek z liczbą poza zakresem jest prostszy niż przypadek z powtarzającą się wartością
    if (rand() % 4 == 0) {
        random_int *= -1;
    }
    return random_int;
}

//? Wypisuje podane tablice.
//! Używane w przypadku nie przejścia testów w celu pokazania różnicy
static void print_arrays(size_t failed_num, size_t n, int const *p1, int const *p2) {
    printf("Failed test number %zu:\n", failed_num);
    printf("Inversed:");
    for (size_t i = 0; i < n; i++)
        printf(" %d,", p1[i]);
    printf("\nOriginal:");
    for (size_t i = 0; i < n; i++)
        printf(" %d,", p2[i]);
    printf("\n");
}

//? Sposób działania testów:
//?     1. Generowanie losowej permutacji
//?     2. Losowo wybieranie czy na wejściu ma być poprawna permutacja, czy nie:
//?
//?         a)  Jeśli permutacja ma być poprawna - puszcza inverse_permutation i
//?             sprawdza czy permutacja została poprawnie odwrócona
//?
//?         b)  Jeśli permutacja ma być niepoprawna - losowo wybiera indeks w tablicy
//?             i zmienia jego wartość na inną niż dotychczasowa, tak żeby zaburzyc permutacje.
//?             Następnie puszcza inverse_permutation i oczekuje zwrócenia false
int rog1gor_test(unsigned int seed) {
    size_t n, i, j, array_size;
    srand(seed);

    for (n = 0; n < TESTS_COUNT; ++n) {
        //? Generowanie losowej tablicy
        array_size = (rand() % SIZE_OF_ARRAY_BOUND) + 1;
        int *p = (int *) malloc(array_size * sizeof(int)),
            *q = (int *) malloc(array_size * sizeof(int));

        if (n % 50000 == 0)  //? Częstotliwość wypisywania progresu
            printf("%zu tests passed!\n", n);

        for (i = 0; i < array_size; i++)
            q[i] = i;

        for (i = array_size; i; i--) {
            j = rand() % i;
            p[i - 1] = q[j];
            q[j] = q[i - 1];
        }

        //? Losowanie czy chcemy testować poprawną czy niepoprawną permutację
        bool test_correct_permutation = rand() % 2 == 0;
        
        //? Jeśli testujemy niepoprawną permutację to trzeba zabużyć naszą permutację
        if (!test_correct_permutation) {
            size_t index_to_change = rand() % array_size;
            int new_value = p[index_to_change];
            while (new_value == p[index_to_change]) {
                new_value = random_integer();
            }
            p[index_to_change] = new_value;
        }

        //? Zapamiętanie permutacji wejściowej
        memcpy(q, p, array_size * sizeof(int));
        bool check_result = inverse_permutation(array_size, p);
        if (test_correct_permutation) {
            if (!check_result || !check_reverse(array_size, p, q)) {
                printf("XX:ret:%d, size:%ld", check_result, array_size);
                print_arrays(n, array_size, p, q);
                
                free(p);
                free(q);
                break;
            }
        } else {
            if (check_result || !is_untouched(array_size, p, q)) {
                printf("YY:%d", check_result);
                print_arrays(n, array_size, p, q);
                
                free(p);
                free(q);
                break;
            }
        }
        free(p);
        free(q);
    }

    if (n == TESTS_COUNT)
        printf("Passed all tests!\n");

    return 0;
}

#endif
