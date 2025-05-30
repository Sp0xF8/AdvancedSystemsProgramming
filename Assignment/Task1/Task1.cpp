#include <iostream>
#include "context.hpp"

void foo(){
    std::cout << "you called foo" << std::endl;
    std::exit(0);
}


int main()
{
   
    char data[4096] = {0};

    //log addres for data
    std::cout << "data:                     " << &data << std::endl;

    void* data_ptr = data;

    void* sp = (void*)((uintptr_t)data_ptr + sizeof(data));

    //log values
    std::cout << "sp with size addition:    " << sp << std::endl;
    std::cout << "foo:                      " << foo << std::endl;

    #ifndef _WIN32 //Linux specific code as the red zone doesnt exist within the windows ABI
        sp = (void*)((uintptr_t)sp - 128);

        std::cout << "sp:                       " << sp << std::endl;
    #endif
    
    sp = (void*)((uintptr_t)sp & -16L); //Align the stack to 16 bytes, this is required by both ABI's

    //log
    std::cout << "sp: after allignment:     " << sp << std::endl;



    Context c = {0};

    c.rsp = sp;
    c.rip = (void*)foo;

    set_context(&c);

    std::cout << "Direction unchanged" << std::endl;

    return 0;
}