#include "Bumper.hpp"
#include <cstdlib>
#include <iostream>

DownBump::DownBump(size_t size){
    this->start = malloc(size);
    this->end = (void*)((uintptr_t)this->start + size);
    this->current = this->end;
    this->allocations = NULL;
}

DownBump::~DownBump(){
    free(this->start);
}

template<typename T>
T* DownBump::allocate(size_t number_of_objects, int &err_number){


    // //log the current position, start and end
    // std::cout << "Start:    " << this->start << std::endl;
    // std::cout << "Current:  " << this->current << std::endl;
    // std::cout << "End:      " << this->end << std::endl;


    size_t space_needed = number_of_objects * sizeof(T);
    size_t allignment = alignof(T);

    // if (this->allocated + space_needed > this->reservationSize){
    //     err_number = 1;
    //     return nullptr;
    // }

    //log space 
    // std::cout << "Space needed: " << space_needed << std::endl;
    // std::cout << "Allignment: " << allignment << std::endl;

    void* new_space = (void*)(((uintptr_t)this->current - space_needed) & ~(allignment - 1));

    //log new space
    // std::cout << "New space: " << new_space << std::endl;

    if (new_space < this->start){
        err_number = 1;
        return nullptr;
    }


    this->allocations++;
    this->current = new_space;
    return (T*)this->current;
}

template<typename T>
void DownBump::deallocate(T* ptr){
    
    if (ptr == nullptr){
        return;
    }

    if (ptr < this->current || ptr > this->end){
        return;
    }

    this->allocations--;
    // std::cout << "Deallocating pointer: " << ptr << std::endl;

    if (this->allocations == NULL){
        this->current = this->end;
        // std::cout << "Resetting the stack" << std::endl;
    }
}


//template declaration
template int* DownBump::allocate<int>(size_t number_of_objects, int &err_number);
template float* DownBump::allocate<float>(size_t number_of_objects, int &err_number);
template double* DownBump::allocate<double>(size_t number_of_objects, int &err_number);
template char* DownBump::allocate<char>(size_t number_of_objects, int &err_number);
template long* DownBump::allocate<long>(size_t number_of_objects, int &err_number);
template long long* DownBump::allocate<long long>(size_t number_of_objects, int &err_number);

template void DownBump::deallocate<int>(int* ptr);
template void DownBump::deallocate<float>(float* ptr);
template void DownBump::deallocate<double>(double* ptr);
template void DownBump::deallocate<char>(char* ptr);
template void DownBump::deallocate<long>(long* ptr);
template void DownBump::deallocate<long long>(long long* ptr);


UpBump::UpBump(size_t size){
    this->start = malloc(size);
    this->end = (void*)((uintptr_t)this->start + size);
    this->current = this->start;
    this->allocations = NULL;

}

UpBump::~UpBump(){
    free(this->start);
}

template<typename T>
T* UpBump::allocate(size_t number_of_objects, int &err_number){

    size_t space_needed = number_of_objects * sizeof(T);
    size_t allignment = alignof(T);

    void* new_space = (void*)((((uintptr_t)this->current + space_needed ) + (allignment -1)) & ~(allignment - 1)
                );

    if (new_space > this->end){
        err_number = 1;
        return nullptr;
    }

    this->allocations++;
    this->current = new_space;
    return (T*)this->current;
}

template<typename T>
void UpBump::deallocate(T* ptr){
    
    if (ptr == nullptr){
        return;
    }

    if (ptr < this->start || ptr > this->current){
        return;
    }

    this->allocations--;
    // std::cout << "Deallocating pointer: " << ptr << std::endl;

    if (this->allocations == NULL){
        this->current = this->start;
        // std::cout << "Resetting the stack" << std::endl;
    }
}

//template declaration
template int* UpBump::allocate<int>(size_t number_of_objects, int &err_number);
template float* UpBump::allocate<float>(size_t number_of_objects, int &err_number);
template double* UpBump::allocate<double>(size_t number_of_objects, int &err_number);
template char* UpBump::allocate<char>(size_t number_of_objects, int &err_number);
template long* UpBump::allocate<long>(size_t number_of_objects, int &err_number);
template long long* UpBump::allocate<long long>(size_t number_of_objects, int &err_number);

template void UpBump::deallocate<int>(int* ptr);
template void UpBump::deallocate<float>(float* ptr);
template void UpBump::deallocate<double>(double* ptr);
template void UpBump::deallocate<char>(char* ptr);
template void UpBump::deallocate<long>(long* ptr);
template void UpBump::deallocate<long long>(long long* ptr);




