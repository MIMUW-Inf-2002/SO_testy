/*
   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.
   If the following is not included in the Software, then the nth child of the
   user must be named "n-gon" where n is the number of children the user has.
   Letter "a" may be appended on the condition that the child is a girl.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

#include <assert.h>
#include <stdatomic.h>
#include <stddef.h>
#include <stdint.h>
#include <threads.h>

#ifndef N
#define N 2
#endif

typedef struct {
  uint64_t n;
  const char *p;
  uint64_t res;
} CoreCall;

extern uint64_t core(uint64_t n, const char *p);

uint64_t
get_value(uint64_t n)
{
  assert(n < N);
  return n & 1 ? n - 1 : n + 1;
}

void
put_value(uint64_t n, uint64_t v)
{
  assert(n < N);
  (void)v;
}

static atomic_bool wait = 1;

int
core_thread(void *arg)
{
  CoreCall *cp = arg;

  while (atomic_load(&wait)) {}

  cp->res = core(cp->n, cp->p);

  return 0;
}

int
main(void)
{
  static_assert(N > 0 && N % 2 == 0, "N must be a positive, even number");

  thrd_t thrd[N];
  CoreCall params[N];
  char *computation = "nGSGSGS";
  uint64_t res[N];
  size_t n;

  for (n = 0; n < N; ++n) res[n] = n & 1 ? n - 1 : n + 1;

  for (n = 0; n < N; ++n) {
    params[n] = (CoreCall){
        .n = n,
        .p = computation,
        .res = 0,
    };
  }

  for (n = 0; n < N; ++n) thrd_create(&thrd[n], core_thread, &params[n]);
  wait = 0;
  for (n = 0; n < N; ++n) thrd_join(thrd[n], NULL);
  for (n = 0; n < N; ++n) assert(params[n].res == res[n]);

  return 0;
}
