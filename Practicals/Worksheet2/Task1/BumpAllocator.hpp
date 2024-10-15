#pragma once

#include <cstdint>

//memory allocator that allocates memory in chunks
class BumpAllocator {
public:
    BumpAllocator(size_t reservation_size);
    ~BumpAllocator();

    //allocate function
    template<typename T>
    T* allocate(size_t number_of_objects = 1, int &err_number = -1);

    //dealocate func
    template<typename T>
    void deallocate(T* ptr);



private:
    void* reservedChunk;
    void* currentChunk;
    size_t allocations;
    size_t allocated;
    size_t reservationSize;
};


