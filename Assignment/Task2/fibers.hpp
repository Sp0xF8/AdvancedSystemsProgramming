#pragma once
#include "context.hpp"

class Fiber {
    public:
        Fiber(void* func);


        Fiber(void* func, void* _pArg);


        ~Fiber();
        Context ret_context();

    private:
        Context context_;
        char* stack_bottom;
        char* stack_top;

        
 
        void* pArg;

};