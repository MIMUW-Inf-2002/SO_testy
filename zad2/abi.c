#define _GNU_SOURCE
#include <assert.h>
#include <immintrin.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

uint64_t core(uint64_t n, const char *p);

#define ASSERT_FRAME_ALIGNED \
  assert((uintptr_t)(__builtin_frame_address(0)) % 16 == 0)

static void
mess_up_registers()
{
  __asm__ volatile(
      "movaps (%0), %%xmm4\n"
      "mov $2137, %%eax\n"
      "mov $2137, %%ecx\n"
      "mov $2137, %%edx\n"
      "mov $2137, %%esi\n"
      "mov $2137, %%edi\n"
      "mov $2137, %%r8d\n"
      "mov $2137, %%r9d\n"
      "mov $2137, %%r10d\n"
      "mov $2137, %%r11d\n"
      "pxor %%xmm0, %%xmm0\n"
      "pxor %%xmm1, %%xmm1\n"
      "pxor %%xmm2, %%xmm2\n"
      "pxor %%xmm3, %%xmm3\n"
      "pxor %%xmm4, %%xmm4\n"
      "pxor %%xmm5, %%xmm5\n"
      "pxor %%xmm6, %%xmm6\n"
      "pxor %%xmm7, %%xmm7\n"
      :
      : "r"(__builtin_frame_address(0))
      : "rax", "rcx", "rdx", "rsi", "rdi", "r8", "r9", "r10", "r11", "xmm0",
        "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7");
}

uint64_t
get_value(uint64_t n)
{
  ASSERT_FRAME_ALIGNED;
  assert(n < N);
  mess_up_registers();
  return n + 1;
}

void
put_value(uint64_t n, uint64_t v)
{
  ASSERT_FRAME_ALIGNED;
  assert(n < N);
  assert(v == 1);
  mess_up_registers();
}

static void *
format_prog(const char *program)
{
  size_t pgsz = sysconf(_SC_PAGESIZE);
  char *page =
      (char *)mmap((void *)0x213700000000, pgsz, PROT_READ | PROT_WRITE,
                   MAP_ANONYMOUS | MAP_SHARED, -1, 0);
  memset(page, '1', pgsz);
  size_t program_size = strlen(program) + 1;
  memcpy(page + pgsz - program_size, program, program_size);
  mprotect(page, pgsz, PROT_READ);
  return page;
}

int
main()
{
  static const char computation[] =
      "88*8*8*8*8*8*8*8*8*8*4B1-0BGP233789+****5-+";
  void *prog = format_prog(computation);
  uint64_t result = core(0, prog);
  assert(result == 2137);
}
