#include "fibers.hpp"

#include <cstdint>

Fiber::Fiber(void* func) {
    stack_bottom = new char[4096];
    stack_top = stack_bottom + 4096;
    pArg = nullptr;


    void* stackPtr = stack_top;

    #ifndef _WIN32 //Linux specific code as the red zone doesnt exist within the windows ABI
        stackPtr = (void*)((uintptr_t)stackPtr - 128);
    #endif

    stackPtr = (void*)((uintptr_t)stackPtr & -16L); //Align the stack to 16 bytes, this is required by both ABI's


    context_.rsp = stackPtr;
    context_.rip = func;
    
}


Fiber::Fiber(void* func, void* _pArg) {
    stack_bottom = new char[4096];
    stack_top = stack_bottom + 4096;
    pArg = _pArg;


    void* stackPtr = stack_top;

    #ifndef _WIN32 //Linux specific code as the red zone doesnt exist within the windows ABI
        stackPtr = (void*)((uintptr_t)stackPtr - 128);
    #endif

    stackPtr = (void*)((uintptr_t)stackPtr & -16L); //Align the stack to 16 bytes, this is required by both ABI's


    context_.rsp = stackPtr;
    context_.rip = func;
}

Fiber::~Fiber() {
    delete[] stack_bottom;
}

Context Fiber::ret_context() {
    return context_;
}