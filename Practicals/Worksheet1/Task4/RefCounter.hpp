#pragma once

#include <cstdint>

template <class T>
class RefCounter
{
public:

    RefCounter(T* object);

    RefCounter(const RefCounter& other);
    RefCounter& operator=(const RefCounter& other);

    ~RefCounter();

    T* getObject();

    uint64_t getReferences();

    void printRefs();


private:
    T* object;
    uint64_t* references;
};