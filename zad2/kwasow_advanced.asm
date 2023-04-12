section .data
test_string db '245+*', 0

section .rodata
error_msg db 'kwasow_advanced failed', 0
error_msg_len equ 19

section .text
global get_value, put_value, advanced_test
extern core

%macro fail_test 0
  ; Print error
  mov eax, 1                    ; Set syscall number for write()
  mov edi, 1                    ; Set file descriptor for stdout
  lea rsi, [rel error_msg]      ; Set address of error message string
  mov rdx, error_msg_len        ; Set length of error message string
  syscall                       ; Call write()
  ; Exit program
  mov eax, 1
  xor ebx, ebx
  inc ebx                       ; Set error code to 1
  int 0x80                      ; Exit program
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
