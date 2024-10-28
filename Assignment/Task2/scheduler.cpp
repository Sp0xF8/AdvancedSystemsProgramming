#include "scheduler.hpp"


Scheduler::Scheduler(){
    fibers_ = std::deque<Fiber*>();
}

Scheduler::~Scheduler(){
    for (auto fiber : fibers_){
        delete fiber;
    }
}


void Scheduler::spawn(Fiber* fiber){
    fibers_.push_back(fiber);
}

void Scheduler::do_it(){
    get_context(&context);

    if (!fibers_.empty()){
        Fiber* fiber = fibers_.front();
        fibers_.pop_front();

        Context c = fiber->ret_context();

        set_context(&c);

       
    }
}

void Scheduler::fiber_exit(){
    set_context(&context);
}