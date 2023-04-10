/**
 * Autor: Leonardo Fibonacci z Pizy & Deparchator z Discorda
 *
 * Program oblicza k-tą liczbę Fibonacciego mod 2^64.
 * Wartość k jest argumentem wywołania programu (np. ./fib 42).
 * Program wykorzystuje do obliczenia 3 zsynchronizowane rdzenie.
 *
 * Wynik jest weryfikowany z wynikiem funkcji
 * uint64_t fib(uint64_t k) napisanej poniżej w C.
 *
 * Na standardowym wyjściu znajdzie się wynik programu oraz komunikat
 * o poprawności wyniku.
 *
 * Czy wiesz, że...
 * Liczby Fibonacciego pomagają przeliczać mile na kilometry.
 * Np. 5 mi = 8 km, 8 mi = 13 km, 13 mi = 21 km, ...
 */

#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#define N 3

uint64_t core(uint64_t n, char const *p);

uint64_t get_value(uint64_t n) {
    assert(n < N);
    return n + 1;
}

void put_value(uint64_t n, uint64_t v) {
    assert(n < N);
    assert(v == n + 4);
}

typedef struct {
    uint64_t n, result;
    char const *p;
} core_call_t;

static volatile int wait = 0;

static void * core_thread(void *params) {
    core_call_t *cp = (core_call_t*)params;
    while (wait == 0);
    cp->result = core(cp->n, cp->p);
    return NULL;
}

uint64_t fib(uint64_t k) {
    if (k <= 1)
        return k;

    uint64_t a = 1;
    uint64_t b = 1;

    while (k > 2) {
        uint64_t c = b;
        b = a + b;
        a = c;
        k--;
    }

    return b;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Użycie: ./fib k, gdzie k >= 0.\n");
        exit(1);
    }

    uint64_t k = strtoull(argv[1], NULL, 10);
    static pthread_t tid[N];
    static core_call_t params[N];
    char *computation[N];
    size_t pref_len = k == 0 ? 1 : k + k - 1;
    char suf[] = "0C78+B11SC12SC192*1+B1-+01SC02SC148*7+-BC";
    size_t suf_len = strlen(suf);

    computation[0] = (char *)malloc((pref_len + suf_len + 1) * sizeof(char));

    if (k == 0) {
        computation[0][0] = '0';
    } else {
        for (uint64_t i = 0; i < k; i++)
            computation[0][i] = '1';

        for (uint64_t i = k; i < pref_len; i++)
            computation[0][i] = '+';
    }

    memcpy(computation[0] + pref_len, suf, suf_len + 1);
    computation[1] = "000S8BC2S76+-BC";
    computation[2] = "100S52*BCD1S+89+-BC";

    // Kod programu
    // printf("Core 0: %s\nCore 1: %s\nCore 2: %s\n", computation[0], computation[1], computation[2]);

    for (size_t n = 0; n < N; ++n) {
        params[n].n = n;
        params[n].result = 0;
        params[n].p = computation[n];
    }

    for (size_t n = 0; n < N; ++n)
        assert(0 == pthread_create(&tid[n], NULL, &core_thread, (void*)&params[n]));

    wait = 1;

    for (size_t n = 0; n < N; ++n)
        assert(0 == pthread_join(tid[n], NULL));

    printf("%lu", params[1].result);

    uint64_t res = fib(k);

    if (params[1].result == res)
        printf(" \x1b[32mOK\n");
    else
        printf(" \x1b[31mWRONG\nExpected %lu, but got %lu.\n", res, params[1].result);

    printf("\x1b[0m");

    free(computation[0]);

    return 0;
}
