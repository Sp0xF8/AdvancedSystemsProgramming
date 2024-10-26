/*
 * Author: Benedict R. Gaster & Callum P.W. Hornblower
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





extern "C" int get_linux_context(Context *c);
extern "C" void set_linux_context(Context *c);
extern "C" void swap_linux_context(Context *out, Context *in);

extern "C" int get_windows_context(Context *c);
extern "C" void set_windows_context(Context *c);
extern "C" void swap_windows_context(Context *out, Context *in);

//macros depending on the platform
#ifdef _WIN32
  #define get_context(c) get_windows_context(c)
  #define set_context(c) set_windows_context(c)
  #define swap_context(out, in) swap_windows_context(out, in)
#else
  #define get_context(c) get_linux_context(c)
  #define set_context(c) set_linux_context(c)
  #define swap_context(out, in) swap_linux_context(out, in)
#endif





