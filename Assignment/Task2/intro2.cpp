#include <iostream>
#include "scheduler.hpp"


Scheduler s;

void func1(){
    std::cout << "fiber 1" << std::endl;

    s.fiber_exit();
}


void func2(){
    std::cout << "fiber 2" << std::endl;
    
    s.fiber_exit();
}


int main()
{

    #ifdef _WIN32
        std::cout << "Windows" << std::endl;
    #else
        std::cout << "Linux" << std::endl;
    #endif

    Fiber f2((void*)&func2);
    Fiber f1((void*)&func1);

    s.spawn(&f1);
    s.spawn(&f2);

    s.do_it();

    std::cout << "Program Finished" << std::endl;

    return 0;
}