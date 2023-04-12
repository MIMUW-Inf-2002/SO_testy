#include <assert.h>
#include <inttypes.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>

/* ================================= SETUP ================================== */
#define N 1

// Same interface as core(), but checks preserved registers
uint64_t core_test(uint64_t n, char const *p);
// These functions are defined in kwasow_advanced1.asm
// uint64_t get_value(uint64_t n);
// void put_value(uint64_t n, uint64_t v);

/* ================================== TEST ================================== */
int main(void) {
  // Test if stack is aligned on call and if values stored in "unsafe" registers
  // are saved before call
  assert(core_test(0, "G") == 10);
  assert(core_test(0, "123+") == 5);
  assert(core_test(0, "123+G") == 10);
  assert(core_test(0, "123+G+") == 15);
  assert(core_test(0, "123+G3+") == 13);
  assert(core_test(0, "123+G123+") == 5);
  assert(core_test(0, "123+G123+G123+") == 5);
  printf("G passed\n");

  printf("Running P test - if no confirmation then test failed...\n");
  assert(core_test(0, "35*") == 15);
  assert(core_test(0, "135*P") == 1);
  assert(core_test(0, "135*P135*P") == 1);
  assert(core_test(0, "135*P135*P135*") == 15);
  printf("P passed\n");
}