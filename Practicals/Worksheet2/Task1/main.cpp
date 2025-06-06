#include "BumpAllocator.hpp"

#include <iostream>

int main() {
    BumpAllocator allocator(1024);

    int err_num;

    //allocate an integer
    int* a = allocator.allocate<int>(1, err_num);
    if (a == nullptr) {
        std::cout << "Allocation failed with error number: " << err_num << std::endl;
    } else {
        *a = 5;
        std::cout << "Allocated integer: " << *a << std::endl;
    }

    //allocate an array of 10 integers
    int* b = allocator.allocate<int>(10, err_num);
    if (b == nullptr) {
        std::cout << "Allocation failed with error number: " << err_num << std::endl;
    } else {
        for (int i = 0; i < 10; i++) {
            b[i] = i;
        }
        std::cout << "Allocated array of integers: ";
        for (int i = 0; i < 10; i++) {
            std::cout << b[i] << " ";
        }
        std::cout << std::endl;
    }


    //allocate a float
    float* c = allocator.allocate<float>(1, err_num);
    if (c == nullptr) {
        std::cout << "Allocation failed with error number: " << err_num << std::endl;
    } else {
        *c = 3.14f;
        std::cout << "Allocated float: " << *c << std::endl;
    }

    //allocate a double
    double* d = allocator.allocate<double>(1, err_num);
    if (d == nullptr) {
        std::cout << "Allocation failed with error number: " << err_num << std::endl;
    } else {
        *d = 3.14159;
        std::cout << "Allocated double: " << *d << std::endl;
    }

    //reset the allocator
    allocator.deallocate(a);
    allocator.deallocate(b);
    allocator.deallocate(c);
    allocator.deallocate(d);

    //allocate a char
    char* e = allocator.allocate<char>(1, err_num);
    if (e == nullptr) {
        std::cout << "Allocation failed with error number: " << err_num << std::endl;
    } else {
        *e = 'A';
        std::cout << "Allocated char: " << *e << std::endl;
    }

    //allocate a string
    char* f = allocator.allocate<char>(6, err_num);
    if (f == nullptr) {
        std::cout << "Allocation failed with error number: " << err_num << std::endl;
    } else {
        f[0] = 'H';
        f[1] = 'e';
        f[2] = 'l';
        f[3] = 'l';
        f[4] = 'o';
        f[5] = '\0';
        std::cout << "Allocated string: " << f << std::endl;
    }

    //allocate a long long
    long long* g = allocator.allocate<long long>(1, err_num);
    if (g == nullptr) {
        std::cout << "Allocation failed with error number: " << err_num << std::endl;
    } else {
        *g = 1234567890123456789;
        std::cout << "Allocated long long: " << *g << std::endl;
    }

    allocator.deallocate(e);
    allocator.deallocate(f);
    allocator.deallocate(g);
    
    //allocate 1023 chars and 1 null terminator to fill the allocator
    char* h = allocator.allocate<char>(1023, err_num);
    if (h == nullptr) {
        std::cout << "Allocation failed with error number: " << err_num << std::endl;
    } else {
        for (int i = 0; i < 1023; i++) {
            h[i] = 'A';
        }
        h[1023] = '\0';
        std::cout << "Allocated 1023 chars & 1 null terminator: " << h << std::endl;
    }

    //allocate one more char to show that the allocator is full
    char* i = allocator.allocate<char>(1, err_num);
    if (i == nullptr) { 
        std::cout << "Allocation failed with error number: " << err_num << std::endl;
    } else {
        *i = 'B';
        std::cout << "Allocated 1 char: " << *i << std::endl;
    }


    allocator.deallocate(h);

    allocator.deallocate(i); //does nothing since the allocator was full when the allocation was attempted

    //retry the previously failed allocation
    int* j = allocator.allocate<int>(1, err_num);
    if (j == nullptr) {
        std::cout << "Allocation failed with error number: " << err_num << std::endl;
    } else {
        *j = 10;
        std::cout << "Allocated integer: " << *j << std::endl;
    }

    return 0;

}