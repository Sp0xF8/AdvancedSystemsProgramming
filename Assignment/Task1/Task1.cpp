#include <iostream>
#include "context.hpp"

Context returningContext = {0};

void foo(){
    std::cout << "you called foo" << std::endl;

    set_context(&returningContext);
}

void goo(){
    std::cout << "you called goo" << std::endl;
    
    set_context(&returningContext);
}




int main()
{
   
    char fooStack[4096] = {0};
    char gooStack[4096] = {0};

    //log addres for data
    std::cout << "fooStack:                     " << &fooStack << std::endl;
    std::cout << "gooStack:                     " << &gooStack << std::endl;

    void* fooStackPtr = fooStack;
    void* gooStackPtr = gooStack;

    void* fooSP = (void*)((uintptr_t)fooStackPtr + sizeof(fooStack));
    void* gooSP = (void*)((uintptr_t)gooStackPtr + sizeof(gooStack));

    //log values
    std::cout << "fooSP with size addition:    " << fooSP << std::endl;
    std::cout << "gooSP with size addition:    " << gooSP << std::endl;
    std::cout << "foo:                      " << foo << std::endl;
    std::cout << "goo:                      " << goo << std::endl;

    #ifndef _WIN32 //Linux specific code as the red zone doesnt exist within the windows ABI
        fooSP = (void*)((uintptr_t)fooSP - 128);
        gooSP = (void*)((uintptr_t)gooSP - 128);

        std::cout << "fooSP:                       " << fooSP << std::endl;
        std::cout << "gooSP:                       " << gooSP << std::endl;
    #endif
    
    fooSP = (void*)((uintptr_t)fooSP & -16L); //Align the stack to 16 bytes, this is required by both ABI's
    gooSP = (void*)((uintptr_t)gooSP & -16L); //Align the stack to 16 bytes, this is required by both ABI's

    //log
    std::cout << "fooSP: after allignment:     " << fooSP << std::endl;
    std::cout << "gooSP: after allignment:     " << gooSP << std::endl;


    Context fooContext = {0};
    Context gooContext = {0};

    fooContext.rsp = fooSP;
    fooContext.rip = (void*)foo;

    gooContext.rsp = gooSP;
    gooContext.rip = (void*)goo;


    int x = 0;

    get_context(&returningContext);

    if(x == 0){
        x++;
        set_context(&fooContext);
    }
    
    if(x == 1){
        x++;
        set_context(&gooContext);
    }


    std::cout << "Execution Finished" << std::endl;

    return 0;
}