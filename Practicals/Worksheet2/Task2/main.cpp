#include "../Task1/BumpAllocator.hpp"
#include "Testing/simpletest.h"
#include <cstring>

char const * groups[] = {
    "BumpAllocator",
};


DEFINE_TEST_G(BumpAllocator_SingleIntTest, BumpAllocator){
    BumpAllocator allocator(1024);
    int err_num = 0;
    //allocate an integer
    int* a = allocator.allocate<int>(1, err_num);
    TEST_MESSAGE(a != nullptr, "Failed to allocate memory");

    if(a != nullptr){
        *a = 5;
        TEST_MESSAGE(*a == 5, "Failed to set value of allocated memory");
    } 
}

DEFINE_TEST_G(BumpAllocator_IntArrayTest, BumpAllocator){
    BumpAllocator allocator(1024);
    int err_num = 0;
    //allocate an array of 10 integers
    int* b = allocator.allocate<int>(10, err_num);
    TEST_MESSAGE(b != nullptr, "Failed to allocate memory");

    if(b != nullptr){
        for (int i = 0; i < 10; i++) {
            b[i] = i;
        }
        bool pass = true;
        for (int i = 0; i < 10; i++) {
            pass &= b[i] == i;
        }
        TEST_MESSAGE(pass, "Failed to set value of allocated memory");
    }

}

DEFINE_TEST_G(BumpAllocator_FloatTest, BumpAllocator){
    BumpAllocator allocator(1024);
    int err_num = 0;
    //allocate a float
    float* c = allocator.allocate<float>(1, err_num);
    TEST_MESSAGE(c != nullptr, "Failed to allocate memory");

    if(c != nullptr){
        *c = 3.14f;
        TEST_MESSAGE(*c == 3.14f, "Failed to set value of allocated memory");
    }
}

DEFINE_TEST_G(BumpAllocator_DoubleTest, BumpAllocator){
    BumpAllocator allocator(1024);
    int err_num = 0;
    //allocate a double
    double* d = allocator.allocate<double>(1, err_num);
    TEST_MESSAGE(d != nullptr, "Failed to allocate memory");

    if(d != nullptr){
        *d = 3.14159;
        TEST_MESSAGE(*d == 3.14159, "Failed to set value of allocated memory");
    }
}

DEFINE_TEST_G(BumpAllocator_CharTest, BumpAllocator){
    BumpAllocator allocator(1024);
    int err_num = 0;
    //allocate a char
    char* e = allocator.allocate<char>(1, err_num);
    TEST_MESSAGE(e != nullptr, "Failed to allocate memory");

    if(e != nullptr){
        *e = 'A';
        TEST_MESSAGE(*e == 'A', "Failed to set value of allocated memory");
    }
}

DEFINE_TEST_G(BumpAllocator_StringTest, BumpAllocator){
    BumpAllocator allocator(1024);
    int err_num = 0;
    //allocate a string
    char* f = allocator.allocate<char>(6, err_num);
    TEST_MESSAGE(f != nullptr, "Failed to allocate memory");

    if(f != nullptr){
        f[0] = 'H';
        f[1] = 'e';
        f[2] = 'l';
        f[3] = 'l';
        f[4] = 'o';
        f[5] = '\0';
        TEST_MESSAGE(!strcmp(f, "Hello"), "Failed to set value of allocated memory"); // can use the ! operator becasue strcmp returns true or false, false being a match.
    }
}

DEFINE_TEST_G(BumpAllocator_LongLongTest, BumpAllocator){
    BumpAllocator allocator(1024);
    int err_num = 0;
    //allocate a long long
    long long* g = allocator.allocate<long long>(1, err_num);
    TEST_MESSAGE(g != nullptr, "Failed to allocate memory");

    if(g != nullptr){
        *g = 1234567890123456789;
        TEST_MESSAGE(*g == 1234567890123456789, "Failed to set value of allocated memory");
    }
}


DEFINE_TEST_G(BumpAllocator_1023CharsTest, BumpAllocator){
    BumpAllocator allocator(1024);
    int err_num = 0;
    //allocate to 1023 chars
    char* h = allocator.allocate<char>(1023, err_num);
    TEST_MESSAGE(h != nullptr, "Failed to allocate memory");

    if(h != nullptr){
        for (int i = 0; i < 1022; i++) {
            h[i] = 'A';
        }
        h[1022] = '\0';
        TEST_MESSAGE(h[0] == 'A' && h[1021] == 'A' && h[1022] == '\0', "Failed to set value of allocated memory");
    }
}

DEFINE_TEST_G(BumpAllocator_1024CharsTest, BumpAllocator){
    BumpAllocator allocator(1024);
    int err_num = 0;
    //allocate to 1024 chars
    char* i = allocator.allocate<char>(1024, err_num);
    TEST_MESSAGE(i != nullptr, "Failed to allocate memory");

    if(i != nullptr){
        for (int x = 0; x < 1023; x++) {
            i[x] = 'A';
        }
        i[1023] = '\0';
        TEST_MESSAGE(i[0] == 'A' && i[1022] == 'A' && i[1023] == '\0', "Failed to set value of allocated memory");
    }
}

DEFINE_TEST_G(BumpAllocator_1025CharsTest, BumpAllocator){
    BumpAllocator allocator(1024);
    int err_num = 0;
    //allocate to 1025 chars
    char* j = allocator.allocate<char>(1025, err_num);
    TEST_MESSAGE(j != nullptr, "Successfully failed to allocate memory");

    if(j != nullptr){
        for (int x = 0; x < 1024; x++) {
            j[x] = 'A';  
        }
        j[1024] = '\0';
        TEST_MESSAGE(j[0] == 'A' && j[1023] == 'A' && j[1024] == '\0', "Failed to set value of allocated memory and probabaly sigfaulted");
    }
}

DEFINE_TEST_G(BumpAllocator_1023CharsResetTest, BumpAllocator){
    BumpAllocator allocator(1024);
    int err_num = 0;
    //allocate to 1024 chars
    char* h = allocator.allocate<char>(1023, err_num);
    TEST_MESSAGE(h != nullptr, "Failed to allocate memory");

    if(h != nullptr){
        for (int i = 0; i < 1023; i++) {
            h[i] = 'A';
        }
        h[1023] = '\0';
        TEST_MESSAGE(h[0] == 'A' && h[1022] == 'A' && h[1023] == '\0', "Failed to set value of allocated memory");
    }

    //reset and allocate to 1024 chars
    allocator.reset();
    char* k = allocator.allocate<char>(1023, err_num);
    TEST_MESSAGE(k != nullptr, "Failed to allocate memory");

    if(k != nullptr){
        for (int i = 0; i < 1023; i++) {
            k[i] = 'B';
        }
        k[1023] = '\0';
        TEST_MESSAGE(k[0] == 'B' && k[1022] == 'B' && k[1023] == '\0', "Failed to set value of allocated memory");
    }
}


int main() {
    bool pass = true;
    for (auto group : groups) {
        pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);
    }
    return pass ? 0 : 1;
}