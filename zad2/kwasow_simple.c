#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>

/* ================================= SETUP ================================== */
#ifndef N
#define N 2
#endif

uint64_t core_test(uint64_t n, char const *p);
uint64_t get_value(uint64_t n) {
  assert(n < N);
  return n + 1;
}
void put_value(uint64_t n, uint64_t v) {
  assert(n < N);
  assert(v == n + 4);
}

/* ================================== TEST ================================== */
int main(void) {
  // Basic, single operation tests
  assert(core_test(0, "9") == 9);
  assert(core_test(0, "934") == 4);
  printf("[0-9] passed\n");

  assert(core_test(0, "12+") == 3);
  printf("+     passed\n");

  assert(core_test(0, "12*") == 2);
  assert(core_test(0, "22*") == 4);
  assert(core_test(0, "34*") == 12);
  assert(core_test(0, "4827*") == 14);
  assert(core_test(0, "48*27**") == 448);
  printf("*     passed\n");

  assert(core_test(0, "0-") == 0);
  assert(core_test(0, "1-") == UINT64_MAX);
  assert(core_test(0, "3-") == UINT64_MAX - 2);
  assert(core_test(0, "19-") == UINT64_MAX - 8);
  assert(core_test(0, "19-8+") == UINT64_MAX);
  assert(core_test(0, "19-9+") == 0);
  printf("-     passed\n");

  assert(core_test(0, "n") == 0);
  assert(core_test(12, "n") == 12);
  assert(core_test(UINT64_MAX, "n") == UINT64_MAX);
  printf("n     passed\n");

  assert(core_test(0, "12C") == 1);
  assert(core_test(0, "1243C") == 4);
  assert(core_test(0, "123CCC9") == 9);
  printf("C     passed\n");

  assert(core_test(0, "1DC") == 1);
  assert(core_test(0, "1D2") == 2);
  assert(core_test(0, "1D4D") == 4);
  assert(core_test(0, "1298DC") == 8);
  assert(core_test(0, "98DCDCDCDC") == 8);
  assert(core_test(0, "98DCDCDCDCC") == 9);
  printf("D     passed\n");

  assert(core_test(0, "12E") == 1);
  assert(core_test(0, "1243E") == 4);
  assert(core_test(0, "1243EC") == 3);
  assert(core_test(0, "1243ECC") == 2);
  assert(core_test(0, "1243ECCC") == 1);
  printf("E     passed\n");

  assert(core_test(0, "G") == 1);
  assert(core_test(1, "G") == 2);
  printf("G     passed\n");

  assert(core_test(0, "10B") == 1);
  assert(core_test(0, "41B") == 4);
  assert(core_test(0, "451B0*") == 20);
  assert(core_test(0, "55B000002*") == 10);
  printf("B     passed\n");
}