#include <iostream>

#ifdef _WIN32
    #include <Windows.h>     // For Windows-specific context handling
#endif
#include "context.hpp"   // Custom context, make sure it’s Windows-compatible

void foo(){
    std::cout << "You called foo" << std::endl;
    std::exit(0);
}

int main() {
    

    #ifdef _WIN32
    std::cout << "Windows" << std::endl;
    #else
    std::cout << "Linux" << std::endl;
    #endif

    return 0;
}
