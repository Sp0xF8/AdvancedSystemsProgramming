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
        Context c = fiber->ret_context();

        set_context(&c);
    }
}

void Scheduler::fiber_exit(){
    fibers_.pop_front();
    set_context(&context);
}

void Scheduler::yeild(){
    int x = 0;
    Context c;
    Fiber* fiber = fibers_.front();

    get_context(&c);

    fibers_.pop_front();
    fiber->update_context(&c);
    fibers_.push_back(fiber);

    if (x == 0) {
        x += 1;
        set_context(&context);
    }

    return;
}