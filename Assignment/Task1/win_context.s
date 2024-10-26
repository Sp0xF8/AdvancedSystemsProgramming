#
# Author: Callum P.W. Hornblower
# Module: Advanced Systems Programming
#
# C API (defined in context.hpp)
# 
# struct Context {
#   void *rip, *rsp;
#   void *rbx, *rbp, *r12, *r13, *r14, *r15, *rdi, *rsi;
#   __m128i xmm6, xmm7, xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15;
# };
# extern "C" void get_context(Context *c);
# extern "C" void set_context(Context *c);
# extern "C" void swap_context(Context *out, Context *in);
#
# We are dependent here on the Sys V x86-64 ABI:
#   https://learn.microsoft.com/en-us/cpp/build/x64-software-conventions?view=msvc-170
#
# Derived from the excellent blog post: https://graphitemaster.github.io/fibers/
#

# extern "C" void get_context_wnd(Context *c);
.global get_context
get_context:
  # Save the return address and stack pointer.
  movq (%rsp), %r8
  movq %r8, 8*0(%rdx) // RIP
  leaq 8(%rsp), %r8
  movq %r8, 8*1(%rdx) // RSP

  # Save preserved registers.
  movq %rbx, 8*2(%rdx)
  movq %rbp, 8*3(%rdx)
  movq %r12, 8*4(%rdx)
  movq %r13, 8*5(%rdx)
  movq %r14, 8*6(%rdx)
  movq %r15, 8*7(%rdx)
  movq %rdi, 8*8(%rdx)
  movq %rsi, 8*9(%rdx)
  movups %xmm6, 8*10+16*0(%rdx)
  movups %xmm7, 8*10+16*1(%rdx)
  movups %xmm8, 8*10+16*2(%rdx)
  movups %xmm9, 8*10+16*3(%rdx)
  movups %xmm10, 8*10+16*4(%rdx)
  movups %xmm11, 8*10+16*5(%rdx)
  movups %xmm12, 8*10+16*6(%rdx)
  movups %xmm13, 8*10+16*7(%rdx)
  movups %xmm14, 8*10+16*8(%rdx)
  movups %xmm15, 8*10+16*9(%rdx)

  # Return.
  xorl %eax, %eax
  ret

# extern "C" void set_context_linux(Context *c);  
.global set_context
set_context:
  # Should return to the address set with {get, swap}_context.
  movq 8*0(%rdx), %r8

  # Load new stack pointer.
  movq 8*1(%rdx), %rsp

  # Load preserved registers.
  movq 8*2(%rdx), %rbx
  movq 8*3(%rdx), %rbp
  movq 8*4(%rdx), %r12
  movq 8*5(%rdx), %r13
  movq 8*6(%rdx), %r14
  movq 8*7(%rdx), %r15
  movq 8*8(%rdx), %rdi
  movq 8*9(%rdx), %rsi
  movups 8*10+16*0(%rdx), %xmm6
  movups 8*10+16*1(%rdx), %xmm7
  movups 8*10+16*2(%rdx), %xmm8
  movups 8*10+16*3(%rdx), %xmm9
  movups 8*10+16*4(%rdx), %xmm10
  movups 8*10+16*5(%rdx), %xmm11
  movups 8*10+16*6(%rdx), %xmm12
  movups 8*10+16*7(%rdx), %xmm13
  movups 8*10+16*8(%rdx), %xmm14
  movups 8*10+16*9(%rdx), %xmm15

  # Push RIP to stack for RET.
  pushq %r8

  # Return.
  xorl %eax, %eax
  ret

# extern "C" void swap_context_linux(Context *out, Context *in);
.global swap_context
swap_context:
  # Save the return address.
  movq (%rsp), %r8
  movq %r8, 8*0(%rdx) // RIP
  leaq 8(%rsp), %r8
  movq %r8, 8*1(%rdx) // RSP

  # Save preserved registers.
  movq %rbx, 8*2(%rdx)
  movq %rbp, 8*3(%rdx)
  movq %r12, 8*4(%rdx)
  movq %r13, 8*5(%rdx)
  movq %r14, 8*6(%rdx)
  movq %r15, 8*7(%rdx)
  movq %rdi, 8*8(%rdx)
  movq %rsi, 8*9(%rdx)
  movups %xmm6, 8*10+16*0(%rdx)
  movups %xmm7, 8*10+16*1(%rdx)
  movups %xmm8, 8*10+16*2(%rdx)
  movups %xmm9, 8*10+16*3(%rdx)
  movups %xmm10, 8*10+16*4(%rdx)
  movups %xmm11, 8*10+16*5(%rdx)
  movups %xmm12, 8*10+16*6(%rdx)
  movups %xmm13, 8*10+16*7(%rdx)
  movups %xmm14, 8*10+16*8(%rdx)
  movups %xmm15, 8*10+16*9(%rdx)

  # Should return to the address set with {get, swap}_context.
  movq 8*0(%rcx), %r8

  # Load new stack pointer.
  movq 8*1(%rcx), %rsp

  # Load preserved registers.
  movq 8*2(%rcx), %rbx
  movq 8*3(%rcx), %rbp
  movq 8*4(%rcx), %r12
  movq 8*5(%rcx), %r13
  movq 8*6(%rcx), %r14
  movq 8*7(%rcx), %r15
  movq 8*8(%rcx), %rdi
  movq 8*9(%rcx), %rsi
  movups 8*10+16*0(%rcx), %xmm6
  movups 8*10+16*1(%rcx), %xmm7
  movups 8*10+16*2(%rcx), %xmm8
  movups 8*10+16*3(%rcx), %xmm9
  movups 8*10+16*4(%rcx), %xmm10
  movups 8*10+16*5(%rcx), %xmm11
  movups 8*10+16*6(%rcx), %xmm12
  movups 8*10+16*7(%rcx), %xmm13
  movups 8*10+16*8(%rcx), %xmm14
  movups 8*10+16*9(%rcx), %xmm15

  # Push RIP to stack for RET.
  pushq %r8

  # Return.
  xorl %eax, %eax
  ret



