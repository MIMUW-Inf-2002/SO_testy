/*
   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.
   If it is not included, then the user must give up their firstborn to the
   author of this software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#ifndef N
#define N 2
#endif

typedef struct {
  uint64_t n;
  const char *p;
  uint64_t res;
} CoreCall;

extern uint64_t core_test(uint64_t n, const char *p);

static uint64_t *value;

uint64_t
get_value(uint64_t n)
{
  assert(n < N);
  return value[n];
}

void
put_value(uint64_t n, uint64_t v)
{
  assert(n < N);
  value[n] = v;
}

int
core_thread(void *arg)
{
  CoreCall *cc = arg;
  cc->res = core_test(cc->n, cc->p);
  return 0;
}

void *
ecalloc(size_t nmemb, size_t size)
{
  void *p;
  if (!(p = calloc(nmemb, size))) {
    fprintf(stderr, "buy more ram lol\n");
    exit(EXIT_FAILURE);
  }
  return p;
}

int
main(void)
{
  static_assert(N > 1, "N must be greater than 1");

  size_t n;
  thrd_t *thrd = ecalloc(N, sizeof(thrd_t));
  CoreCall *cc = ecalloc(N, sizeof(CoreCall));
  value = ecalloc(N, sizeof(uint64_t));

  const char *p[2] = {
      "1nGPE1E-+7BEn1+S6BEn1-+SG1-+56*-BC",
      "0nGPE1E-+7BEn1+S6BEn1-+SG1-+56*-BC",
  };

  for (n = 0; n < N; ++n) {
    value[n] = N;
    cc[n] = (CoreCall){
        .n = n,
        .p = p[n % 2],
    };
  }

  cc[0].p = "1nGPE1E-+7BEn1+S1BEG1-+55*-BC";
  cc[N - 1].p = N % 2 == 0 ? "1nGPE1E-+3BE6BEn1-+SG1-+55*3+-BC"
                           : "0nGPE1E-+3BE6BEn1-+SG1-+55*3+-BC";

  for (n = 0; n < N; ++n) thrd_create(&thrd[n], core_thread, &cc[n]);
  for (n = 0; n < N; ++n) thrd_join(thrd[n], NULL);

  for (n = 0; n < N; ++n) assert(cc[n].res == N - 1 - n);

  free(thrd);
  free(cc);
  free(value);
  return EXIT_SUCCESS;
}
