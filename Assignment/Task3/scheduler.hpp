#pragma once

#include "fibers.hpp"
#include <deque>

class Scheduler {
    public:
        Scheduler();
        ~Scheduler();
        void spawn(Fiber* fiber);
        void do_it();
        void fiber_exit();
        void yeild();
    private:
        std::deque<Fiber*> fibers_;
        Context context;
};