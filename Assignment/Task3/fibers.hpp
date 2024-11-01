#pragma once
#include "context.hpp"

class Fiber {
    public:
        Fiber(void* func);

        template <typename T>
        Fiber(void* func, T* _pArg);


        ~Fiber();
        Context ret_context();
        void update_context(Context* c);

        template <typename T = void*>
        static T* get_data(); //better name might be get_arg

    private:
        Context context_;
        char* stack_bottom;
        char* stack_top;
 

};