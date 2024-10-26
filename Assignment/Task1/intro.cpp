#include <iostream>

#include "context.hpp"

int main() {

    #ifdef _WIN32
    std::cout << "Windows" << std::endl;
    #else
    std::cout << "Linux" << std::endl;
    #endif
    
    int x = 0;
    Context c;

    get_context(&c);

    //log all values of context
    std::cout << "rip: " << c.rip << std::endl;
    std::cout << "rsp: " << c.rsp << std::endl;
    std::cout << "rbx: " << c.rbx << std::endl;
    std::cout << "rbp: " << c.rbp << std::endl;
    std::cout << "r12: " << c.r12 << std::endl;
    std::cout << "r13: " << c.r13 << std::endl;
    std::cout << "r14: " << c.r14 << std::endl;
    std::cout << "r15: " << c.r15 << std::endl;

    std::cout << "a message" << std::endl;

    if (x == 0) {
        x += 1;
        set_context(&c);
    }


    return 0;
}