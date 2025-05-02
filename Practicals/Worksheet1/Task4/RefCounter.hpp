#pragma once

#include <cstdint>

template <typename T>
class RefCounter
{
    public:

        RefCounter(T* object);
        RefCounter(const RefCounter& other);

        RefCounter& operator=(const RefCounter& other);

        ~RefCounter();

        T* getObject();
        uint64_t getReferences() const;

        void printRefs() const;

    private:
        T* object;
        uint64_t* references;
};