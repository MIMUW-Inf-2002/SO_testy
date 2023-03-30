#include "rentib.h"
#include "kwasow.h"
#include "rog1gor.h"

#include <stdio.h>

int main(void) {
  printf("\n=> Running Kwasow tests\n");
  kwasow_test();
  
  printf("=> Running Rentib tests\n");
  unsigned int rentib_seed = 213742069;
  rentib_test(rentib_seed);

  unsigned int rog1gor_seed = 146543;
  printf("=> Running rog1gor tests\n");
  rog1gor_test(rog1gor_seed);
}
