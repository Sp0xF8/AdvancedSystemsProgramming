#include <iostream>
#include "scheduler.hpp"


Scheduler s;

void func1(){
    std::cout << "fiber 1" << std::endl;

    int* p = Fiber::get_data<int>();

    //log the value at the address

    #ifndef _WIN32
        std::cout << "fiber 1: " << *p << std::endl;

    #endif

    *p += 1;

    s.fiber_exit();
}


void func2(){
    int* p = Fiber::get_data<int>();
    //log the value at the address

    std::cout << "fiber 2";
    #ifndef _WIN32
        std::cout << ": " << *p << std::endl;
    #else 
        std::cout << std::endl;
    #endif
    
    s.fiber_exit();
}


int main()
{

    #ifdef _WIN32
        std::cout << "Windows" << std::endl;
    #else
        std::cout << "Linux" << std::endl;
    #endif

    int d = 10;
    int* p = &d;

    //log address that isbeing passed
    std::cout << "Address: " << p << std::endl;
    std::cout << "Value: " << *p << std::endl;

    Fiber f2((void*)&func2, p);
    Fiber f1((void*)&func1, p);

    s.spawn(&f1);
    s.spawn(&f2);

    s.do_it();

    std::cout << "Program Finished" << std::endl;
    std::cout << "Value: " << d << std::endl;

    return 0;
}