/*
 * Author: Benedict R. Gaster
 * Module: Advanced Systems Programming
 *
 * Derived from the excellent blog post: https://graphitemaster.github.io/fibers/
 */
#pragma once


#ifdef _WIN32
  #include <xmmintrin.h>
  #include <emmintrin.h>
  struct Context {
    void *rip, *rsp;
    void *rbx, *rbp, *r12, *r13, *r14, *r15, *rdi, *rsi;
    __m128i xmm6, xmm7, xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15;
  };
#else
  struct Context {
    void *rip, *rsp;
    void *rbx, *rbp, *r12, *r13, *r14, *r15;
  };
#endif






extern "C" int get_context(Context *c);
extern "C" void set_context(Context *c);
extern "C" void swap_context(Context *out, Context *in);

