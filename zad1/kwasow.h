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
  printf("Test2 passed\n");

  int test3[] = {-1, 2, 0};
  assert(inverse_permutation(3, test3) == false);
  printf("Test3 passed\n");

  int test4[] = {1, 2, 3};
  assert(inverse_permutation(3, test4) == false);
  printf("Test4 passed\n");

  int test5[] = {1, 1, 3};
  assert(inverse_permutation(3, test5) == false);
  printf("Test5 passed\n");

  int test6[] = {0, 0, 3};
  assert(inverse_permutation(3, test6) == false);
  printf("Test6 passed\n");

  size_t size1 = INT_MAX;
  size1 += 2;
  int *test7 = (int *) calloc(size1, sizeof(int));
  if (test7 != NULL) {
    assert(inverse_permutation(size1, test7) == false);
    printf("Test7 passed\n");
    free(test7);
  } else {
    printf("Failed to allocate memory for test7. Skipping...\n");
  }

  int test8[] = {0, 1, 2};
  assert(inverse_permutation(3, test8) == true);
  printf("Test8 passed\n");

  printf("Preparing test...\n");
  size_t size2 = INT_MAX;
  size2 += 1;
  int *test9 = (int *) calloc(size2, sizeof(int));
  if (test9 != NULL) {
    for (size_t i = 0; i < size2; i++) {
      test9[i] = i;
    }

    printf("Starting test9 - should be very fast");
    assert(inverse_permutation(size2, test9) == true);
    printf("Test9 passed\n");
    free(test9);
  } else {
    printf("Failed to allocate memory for test9. Skipping...\n");
  }
}

#endif
