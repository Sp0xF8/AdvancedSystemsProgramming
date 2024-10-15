#pragma once

#include <cstddef> // Include the header for fixed-width integer types


class DownBump
{
    public:

        DownBump(size_t size);
        ~DownBump();

        template<typename T>
        T* allocate(size_t number_of_objects,  int &err_number = -1);

        template<typename T>
        void deallocate(T* ptr);

    private:
        void* start;
        void* end;
        void* current;
        size_t allocations;
};



class UpBump
{
    public:

        UpBump(size_t size);
        ~UpBump();

        template<typename T>
        T* allocate(size_t number_of_objects,  int &err_number = -1);

        template<typename T>
        void deallocate(T* ptr);

    private:
        void* start;
        void* end;
        void* current;
        size_t allocations;
};