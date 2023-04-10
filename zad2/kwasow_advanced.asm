section .data

test_string db '245+*', 0

section .text
global get_value, put_value, advanced_test
extern core

%macro fail_test 0
  mov eax, 1
  xor ebx, ebx
  inc ebx ; set error code to 1
  int 0x80
%endmacro

; uint64_t get_value(uint64_t n)
get_value:
  ; Check if stack is aligned
  add   rsp, 0x8
  test  rsp, 0xF          ; check if address is divisible by 16
  jz    .aligned
.not_aligned:
  sub   rsp, 0x8
  xor   rax, rax
  ret
.aligned:
  sub   rsp, 0x8
  cmp   rdi, 0x0          ; check if we got the correct argument
  je    .argument_correct
.argument_incorrect:
  xor   rax, rax
  ret
.argument_correct:
  ; Add anything to all caller-saved registers
  add   rcx, 0x101
  add   rdx, 0x102
  add   rdi, 0x103
  add   rsi, 0x104
  add   r8,  0x105
  add   r9,  0x106
  add   r10, 0x107
  add   r11, 0x108
  lea   rax, 0xA
  ret

; void put_value(uint64_t n, uint64_t v);
put_value:
  ; Check if stack is aligned
  add   rsp, 0x8
  test  rsp, 0xF          ; check if address is divisible by 16
  jz    .aligned
.not_aligned:
  sub   rsp, 0x8
  fail_test
.aligned:
  sub   rsp, 0x8
  cmp   rdi, 0x0          ; check if we got the correct argument
  jne   .argument_incorrect
  cmp   rsi, 0xF
  jne   .argument_incorrect
.argument_correct:
  ; Add anything to all caller-saved registers
  add   rax, 0x101
  add   rcx, 0x102
  add   rdx, 0x103
  add   rdi, 0x104
  add   rsi, 0x105
  add   r8,  0x106
  add   r9,  0x107
  add   r10, 0x108
  add   r11, 0x109
  ret
.argument_incorrect:
  fail_test

RBP_VALUE equ 0x817328
RBX_VALUE equ 0x10c9471
R12_VALUE equ 0x17283
R13_VALUE equ 0x19274
R14_VALUE equ 0x1284a
R15_VALUE equ 0x18f73d

advanced_test:
  ; Save on stack
  push  rbp
  push  rbx
  push  r12
  push  r13
  push  r14
  push  r15
  sub   rsp, 0x8
  ; Move values
  mov   ebp, RBP_VALUE
  mov   ebx, RBX_VALUE
  mov   r12d, R12_VALUE
  mov   r13d, R13_VALUE
  mov   r14d, R14_VALUE
  mov   r15d, R15_VALUE
  ; Call
  mov   rdi, 0x0
  lea   rsi, [rel test_string] ; Should be 18, but not checking
  call  core
  ; Test
  cmp   ebp, RBP_VALUE
  jne   .error
  cmp   ebx, RBX_VALUE
  jne   .error
  cmp   r12d, R12_VALUE
  jne   .error
  cmp   r13d, R13_VALUE
  jne   .error
  cmp   r14d, R14_VALUE
  jne   .error
  cmp   r15d, R15_VALUE
  jne   .error
  ; Restore values
  add   rsp, 0x8
  pop   r15
  pop   r14
  pop   r13
  pop   r12
  pop   rbx
  pop   rbp
  ret
.error:
  fail_test