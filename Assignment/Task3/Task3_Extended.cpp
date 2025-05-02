#include <iostream>
#include "scheduler.hpp"


/*

    plan of devlopment:

    1. add the tic tac toe game
    2. add the bump down allocator 
    3. pass bump allocator to the funcs
    4. make moves and yeild to simulate a fake game between two players


*/

Scheduler s;

void func1(){
    std::cout << "fiber 1 before" << std::endl;

    s.yeild();

    std::cout << "fiber 1 after" << std::endl;


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