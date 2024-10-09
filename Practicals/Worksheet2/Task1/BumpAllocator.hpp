#pragma once

#include <cstdint>

//memory allocator that allocates memory in chunks
class BumpAllocator {
public:
    BumpAllocator(size_t reservation_size);
    ~BumpAllocator();

    template<typename T>
    T* allocate(size_t number_of_objects = 1, int &err_number = -1);

    void reset();

private:
    void* reservedChunk;
    void* currentChunk;
    size_t allocations;
    size_t allocated;
    size_t reservationSize;
};


