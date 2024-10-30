#include "fibers.hpp"

#include <cstdint>


#ifndef _WIN32
    #define size_t std::size_t
#endif

Fiber::Fiber(void* func) {
    stack_bottom = new char[4096];
    stack_top = stack_bottom + 4096;



    void* stackPtr = stack_top;

    #ifndef _WIN32 //Linux specific code as the red zone doesnt exist within the windows ABI
        stackPtr = (void*)((uintptr_t)stackPtr - 128);
    #endif

    stackPtr = (void*)((uintptr_t)stackPtr & -16L); //Align the stack to 16 bytes, this is required by both ABI's


    context_.rsp = stackPtr;
    context_.rip = func;
    
}

template <typename T>
Fiber::Fiber(void* func, T* _pArg) {
    stack_bottom = new char[4096];
    stack_top = stack_bottom + 4096;



    void* stackPtr = stack_top;

    void* pArg = _pArg;


    size_t space_needed = sizeof(void*);
    size_t allignment = alignof(void*);

    stackPtr = (void*)(((uintptr_t)stackPtr - space_needed ) & ~(allignment - 1));

    /*
        Similar to the allocation in the wroksheets, we need to dereference the pointer to change its value, not its address.
    */
    *(void**)stackPtr = pArg;



    #ifndef _WIN32 //Linux specific code as the red zone doesnt exist within the windows ABI
        stackPtr = (void*)((uintptr_t)stackPtr - 128);
    #endif

    stackPtr = (void*)((uintptr_t)stackPtr & -16L); //Align the stack to 16 bytes, as required by both ABI's

    context_.rsp = stackPtr;
    context_.rip = func;



}

Fiber::~Fiber() {
    delete[] stack_bottom;
}

Context Fiber::ret_context() {
    return context_;
}



template <typename T>
T* Fiber::get_data() {
    Context c;
    get_context(&c);
    

    size_t red_zone = 0;

    #ifndef _WIN32
        red_zone = 128;
    #endif


    void* stackPtr = (void*)((uintptr_t)c.rsp + red_zone);

    // std::size_t space_needed = sizeof(void*);
    // std::size_t allignment = alignof(void*);

    #ifndef _WIN32
        stackPtr = (void*)((uintptr_t)stackPtr + 0x90);
    #else 
        stackPtr = (void*)((uintptr_t)stackPtr + 0x170);
    #endif

    void* pArg = *(void**)stackPtr;






    if (pArg != nullptr) {
        return (T*)pArg;
    }





    return nullptr;
}


//implicit instantiation of template
template Fiber::Fiber(void* func, int* _pArg);
template int* Fiber::get_data<int>();
