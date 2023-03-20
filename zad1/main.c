#include "rentib.h"
#include "kwasow.h"

#include <stdio.h>

int main(void) {
  printf("=> Running Rentib tests\n");
  unsigned int rentib_seed = 213742069;
  rentib_test(rentib_seed);

  printf("\n=> Running Kwasow tests\n");
  kwasow_test();
}