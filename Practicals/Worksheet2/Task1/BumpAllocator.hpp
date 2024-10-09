#pragma once

#include <cstdint>

//memory allocator that allocates memory in chunks
class BumpAllocator {
public:
    BumpAllocator(size_t chunkSize);
    ~BumpAllocator();

    void* allocate(size_t size);
    void reset();
};