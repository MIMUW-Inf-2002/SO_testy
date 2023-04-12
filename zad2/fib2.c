#include <assert.h>
#include <stdatomic.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <threads.h>

#ifndef N
#define N 3
#endif

typedef struct {
  uint64_t n;
  const char *p;
  uint64_t res;
} CoreCall;

extern uint64_t core_test(uint64_t n, const char *p);

uint64_t
get_value(uint64_t n)
{
  assert(n < N);
  return N - 2;
}

void
put_value(uint64_t n, uint64_t v)
{
  assert(n < N);
  (void)v;
}

int
core_thread(void *arg)
{
  CoreCall *cc = arg;
  cc->res = core_test(cc->n, cc->p);
  return 0;
}

int
main(void)
{
  static_assert(N > 2, "N must be greater than 2");

  thrd_t thrd[2];
  CoreCall cc[2] = {
      (CoreCall){
          .n = 0,
          .p = "0GE1SE1-+39+-BC",
      },
      (CoreCall){
          .n = 1,
          .p = "1GED0S+E1-+77+-BC",
      },
  };

  thrd_create(thrd + 0, &core_thread, cc + 0);
  thrd_create(thrd + 1, &core_thread, cc + 1);

  uint64_t a = 0, b = 1, c;
  for (size_t i = 2; i < N; i++) {
    c = b;
    b += a;
    a = c;
  }

  thrd_join(thrd[0], NULL);
  thrd_join(thrd[1], NULL);

  assert(a == cc[0].res && "Wrong (N-1)-st Fibonacci number\n");
  assert(b == cc[1].res && "Wrong N-th Fibonacci number\n");

  fprintf(stderr, "%d-th Fibonacci number is %zu\n", N, cc[1].res);

  return 0;
}
