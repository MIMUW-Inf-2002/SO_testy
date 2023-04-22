section .data
test_string db '245+*', 0

section .rodata
error_msg db 'core_test failed - registers not preserved', 10
error_msg_len equ 43

section .text
global core_test
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

; uint64_t core_test(uint64_t n, char const *p);
; Same interface as core
core_test:
  ; Save on stack
  push  rbp
  push  rbx
  push  r12
  push  r13
  push  r14
  push  r15
  sub   rsp, 0x8
  ; Call
  ; rdi and rsi are already set
  call  core
  add   rsp, 0x8
  ; Test
  cmp   r15, [rsp]
  jne   .error
  pop   r15
  cmp   r14, [rsp]
  jne   .error
  pop   r14
  cmp   r13, [rsp]
  jne   .error
  pop   r13
  cmp   r12, [rsp]
  jne   .error
  pop   r12
  cmp   rbx, [rsp]
  jne   .error
  pop   rbx
  cmp   rbp, [rsp]
  jne   .error
  pop   rbp
  ret
.error:
  fail_test