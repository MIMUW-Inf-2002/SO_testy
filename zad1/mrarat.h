/* Test głównie pełni rolę benchmarku, ale sprawdza też poprawność. */

#ifndef MRARAT_H_
#define MRARAT_H_

#include "inverse_permutation.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

bool inverse_permutation(size_t n, int *p);

static bool check_inverse_permutation_mrarat(size_t n, int const *p1, int const *p2) { // _mrarat jest dodane aby uniknąć kolizji nazw
  for (size_t i = 0; i < n; ++i)
    if ((size_t)p2[p1[i]] != i)
      return false;
  return true;
}

void permute(size_t n, int p1[], int p2[]) {
  for (size_t i = 0; i < n; i++) {
    p1[i] = i;
    p2[i] = i;
  }

  for (int i = n-1; i >= 0; --i){
    int j = rand() % (i+1);
    p2[j] = p1[i];
    p1[i] = p1[j];
    p1[j] = p2[j];
    p2[i] = p1[i];
  }
}

void mrarat_test(void)
{ 
  srand(9274);

  const size_t n = ((size_t)INT_MAX + 1) / 200;

  int* p1 = malloc(n * sizeof(int));
  int* p2 = malloc(n * sizeof(int));

  if (p1 == NULL || p2 == NULL) {
    fprintf(stderr, "ERROR: Failed to allocate %lu MB.\n", n * 2 * sizeof(int) / (1024 * 1024));
    return;
  } else
    printf("Succesfully allocated %lu MB.\n", n * 2 * sizeof(int) / (1024 * 1024));

  fflush(stdout);

  double time_total = 0.0;
  for (size_t t = 1; t <= 16; t++) {
    permute(n, p1, p2);

    double time_start = (double)clock() / CLOCKS_PER_SEC;
    inverse_permutation(n, p1);
    double time_end = (double)clock() / CLOCKS_PER_SEC;

    time_total += time_end - time_start;

    if(check_inverse_permutation_mrarat(n, p1, p2)) 
      printf("Test %lu PASSED, time : %f s\n", t, time_end - time_start);
    else 
      printf("Test %lu FAILED, time : %f s\n", t, time_end - time_start);

    fflush(stdout);
  }

  free(p1);
  free(p2);

  printf("Time total : %f s\n", time_total);
  fflush(stdout);
}

#endif // MRARAT_H_