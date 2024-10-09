#include "BumpAllocator.hpp"
#include <cstdlib>


BumpAllocator::BumpAllocator(size_t reservation_size) {
    // allocate memory for the first chunk
    reservedChunk = malloc(reservation_size);
    // set the current chunk to the beginning of the reserved chunk
    currentChunk = reservedChunk;
    // set the size of the chunk
    reservationSize = reservation_size;
    // set the number of allocations to 0 as there are no allocations yet
    allocations, allocated = 0;
}

BumpAllocator::~BumpAllocator() {
    free(reservedChunk);
}

void BumpAllocator::reset() {
    // reset the allocator to the beginning of the chunk
    currentChunk = reservedChunk;
    allocations, allocated = 0;
}

template<typename T>
T* BumpAllocator::allocate(size_t number_of_objects, int &err_number) {
    // calculate the size of the allocation
    size_t allocationSize = number_of_objects * sizeof(T);

    // check if the allocation fits in the chunk
    if (allocated + allocationSize > reservationSize) {
        // if the allocation does not fit, return nullptr
        err_number = 1;
        return nullptr;
    }

    // calculate the address of the allocation
    T* allocation = reinterpret_cast<T*>((uintptr_t)currentChunk + (ptrdiff_t)allocated);

    // update the current chunk and the number of allocations
    allocated += allocationSize;
    allocations++;

    return allocation;
}


//explicit instantiations
template int* BumpAllocator::allocate<int>(size_t number_of_objects, int &err_number);
template float* BumpAllocator::allocate<float>(size_t number_of_objects, int &err_number);
template double* BumpAllocator::allocate<double>(size_t number_of_objects, int &err_number);
template char* BumpAllocator::allocate<char>(size_t number_of_objects, int &err_number);
template long* BumpAllocator::allocate<long>(size_t number_of_objects, int &err_number);
template long long* BumpAllocator::allocate<long long>(size_t number_of_objects, int &err_number);





