#ifndef KWASOW_H_
#define KWASOW_H_

#include "inverse_permutation.h"

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define assert(x)                       \
  if (!(x)) {                             \
    printf("Kwasow tests failed!\n");   \
    return;                             \
  }

void kwasow_test(void) {
  int test1[] = {};
  assert(inverse_permutation(0, test1) == false);
  printf("Test1 passed\n");

  int test2[] = {1, 3, 2};
  assert(inverse_permutation(3, test2) == false);
  assert(test2[0] == 1);
  assert(test2[1] == 3);
  assert(test2[2] == 2);
  printf("Test2 passed\n");

  int test3[] = {-1, 2, 0};
  assert(inverse_permutation(3, test3) == false);
  assert(test3[0] == -1);
  assert(test3[1] == 2);
  assert(test3[2] == 0);
  printf("Test3 passed\n");

  int test4[] = {1, 2, 3};
  assert(inverse_permutation(3, test4) == false);
  assert(test4[0] == 1);
  assert(test4[1] == 2);
  assert(test4[2] == 3);
  printf("Test4 passed\n");

  int test5[] = {1, 1, 2};
  assert(inverse_permutation(3, test5) == false);
  assert(test5[0] == 1);
  assert(test5[1] == 1);
  assert(test5[2] == 2);
  printf("Test5 passed\n");

  int test6[] = {0, 0, 2};
  assert(inverse_permutation(3, test6) == false);
  assert(test6[0] == 0);
  assert(test6[1] == 0);
  assert(test6[2] == 2);
  printf("Test6 passed\n");

  printf("Skipping test7 - see README\n");
  // printf("Preparing test7...\n");
  // Two more than size_max
  // size_t size1 = 2147483649;
  // int *test7 = calloc(size1, sizeof(int));
  // if (test7 != NULL) {
  //   // Tablica: [0, 1, 2, ..., MAX_INT, 0]
  //   for (size_t i = 0; i < INT_MAX + 1; i++) {
  //     test7[i] = i;
  //   }
  //   assert(inverse_permutation(size1, test7) == false);
  //   printf("Test7 passed\n");
  //   free(test7);
  // } else {
  //   printf("Failed to allocate memory for test7. Skipping...\n");
  // }

  int test8[] = {0, 1, 2};
  assert(inverse_permutation(3, test8) == true);
  assert(test8[0] == 0);
  assert(test8[1] == 1);
  assert(test8[2] == 2);
  printf("Test8 passed\n");

  printf("Skipping test9 - see README\n");
  // printf("Preparing test9...\n");
  // // One more than size_max
  // size_t size2 = 2147483648;
  // int *test9 = calloc(size2, sizeof(int));
  // if (test9 != NULL) {
  //   // Tablica: [0, 1, 2, ..., MAX_INT]
  //   for (size_t i = 0; i < size2; i++) {
  //     test9[i] = i;
  //   }

  //   assert(inverse_permutation(size2, test9) == true);
  //   printf("Test9 passed\n");
  //   free(test9);
  // } else {
  //   printf("Failed to allocate memory for test9. Skipping...\n");
  // }
}

#endif
