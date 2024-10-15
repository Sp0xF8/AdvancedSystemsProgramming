#include "BumpAllocator.hpp"
#include <cstdlib>
#include <iostream>


BumpAllocator::BumpAllocator(size_t reservation_size) {
    //allocate memory for the first chunk
    reservedChunk = malloc(reservation_size);
    //set the current chunk to the beginning of the reserved chunk
    currentChunk = reservedChunk;
    //set the size of the chunk
    reservationSize = reservation_size;
    //set the number of allocations to 0 as there are no allocations yet
    allocations = NULL;
    allocated = NULL;

    // std::cout << "Reserved chunk: " << reservedChunk << std::endl;
    // std::cout << "Current chunk: " << currentChunk << std::endl;
    // std::cout << "Reservation size: " << reservationSize << std::endl;
    // std::cout << "Allocations: " << allocations << std::endl;
    // std::cout << "Allocated: " << allocated << std::endl;
}

BumpAllocator::~BumpAllocator() {

    free(reservedChunk);
}


template<typename T>
T* BumpAllocator::allocate(size_t number_of_objects, int &err_number) {
    //calculate the size of the allocation
    size_t allocationSize = number_of_objects * sizeof(T);

    //check if the allocation fits in the chunk
    if (allocated + allocationSize > reservationSize) {
        //if the allocation does not fit, return nullptr
        err_number = 1;
        return nullptr;
    }

    //calculate the address of the allocation
    this->currentChunk = reinterpret_cast<T*>((uintptr_t)currentChunk + (ptrdiff_t)allocated);

    //update the current chunk and the number of allocations
    allocated += allocationSize;
    allocations++;

    return (T*)currentChunk;
}

template<typename T>
void BumpAllocator::deallocate(T* ptr) {

    //if the pointer is null then return
    if (ptr == nullptr) {
        return;
    }

    //if the pointer is not in the reserved chunk then return
    if (ptr < reservedChunk || ptr > (void*)((uintptr_t)reservedChunk + reservationSize)) {
        return;
    }

    // std::cout << "Deallocating pointer: " << ptr << std::endl;

    allocations--;

    //if the allocations is null then se  t reset the stack
    if (allocations == NULL) {
        currentChunk = reservedChunk;
        allocated = NULL;
        // std::cout << "Resetting the stack" << std::endl;
    }

}


//explicit instantiations allocate
template int* BumpAllocator::allocate<int>(size_t number_of_objects, int &err_number);
template float* BumpAllocator::allocate<float>(size_t number_of_objects, int &err_number);
template double* BumpAllocator::allocate<double>(size_t number_of_objects, int &err_number);
template char* BumpAllocator::allocate<char>(size_t number_of_objects, int &err_number);
template long* BumpAllocator::allocate<long>(size_t number_of_objects, int &err_number);
template long long* BumpAllocator::allocate<long long>(size_t number_of_objects, int &err_number);


//explicit instantiations deallcoate
template void BumpAllocator::deallocate<int>(int* ptr);
template void BumpAllocator::deallocate<float>(float* ptr);
template void BumpAllocator::deallocate<double>(double* ptr);
template void BumpAllocator::deallocate<char>(char* ptr);
template void BumpAllocator::deallocate<long>(long* ptr);
template void BumpAllocator::deallocate<long long>(long long* ptr);







