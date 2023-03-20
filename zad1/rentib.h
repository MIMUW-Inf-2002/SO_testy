/* Licencja MIT */
/* Autor - Stanisław Bitner */
#ifndef RENTIB_H_
#define RENTIB_H_

#include "inverse_permutation.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TESTS_NO 1000000

static bool check_inverse_permutation(size_t n, int const *p1, int const *p2) {
  for (size_t i = 0; i < n; ++i)
    if ((size_t)p2[p1[i]] != i)
      return false;
  return true;
}

int rentib_test(unsigned int seed) {
  size_t n, i, j;
  int *p = (int *) malloc(TESTS_NO * sizeof(int)),
      *q = (int *) malloc(TESTS_NO * sizeof(int));

  srand(seed);

  for (n = 0; n < TESTS_NO; ++n) {
    printf("%zu\n", n);

    for (i = 0; i < n; i++)
      q[i] = i;

    for (i = n; i; i--) {
      j = rand() % i;
      p[i - 1] = q[j];
      q[j] = q[i - 1];
    }

    memcpy(q, p, n * sizeof(int));
    (void)inverse_permutation(n, q);
    if (!check_inverse_permutation(n, p, q))
      break;
  }

  if (n == TESTS_NO)
    printf("Passed all tests\n");
  else {
    printf("Failed test number %zu:\n", n);
    printf("Input:");
    for (i = 0; i < n; i++)
      printf(" %d", p[i]);
    printf("\nOutput:");
    for (i = 0; i < n; i++)
      printf(" %d", q[i]);
    printf("\n");
  }

  free(p);
  free(q);

  return 0;
}

#endif
