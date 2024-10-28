#include <iostream>
#include "context.hpp"
#include "fibers.hpp"


void foo(){
    std::cout << "you called foo" << std::endl;
    std::exit(0);

}




int main()
{

    Fiber f((void*)&foo);

    Context c = f.ret_context();

    std::cout << "rip: " << c.rip << std::endl;
    std::cout << "rsp: " << c.rsp << std::endl;

    set_context(&c); // set the context using the macro (platform independant context switching)
   
    

    return 0;
}