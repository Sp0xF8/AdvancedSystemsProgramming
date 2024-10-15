#include "Bumper.hpp"
#include "../Task2/Testing/simpletest.h"
#include <iostream>

#include <chrono>
#include <intrin.h>


char const * groups[] = {
    "UpBump",
    "DownBump",
};


#define BEGINTIMER uint64_t begin = __rdtsc();

#define ENDTIMER uint64_t end = __rdtsc();

#define LOG_TIMETAKEN(begin, end)                                                                       \
    uint64_t numCycles = (end) - (begin);                                                               \
    double cycle_ratio = 1.0 / static_cast<double>(std::chrono::high_resolution_clock::period::den);    \
    uint64_t duration = static_cast<uint64_t>((static_cast<double>(numCycles) * cycle_ratio) * 1e9);    \
    std::cout << "Time taken: " << duration << " ns" << std::endl;


DEFINE_TEST_G(DownBump_SingleIntTest, DownBump){
    DownBump dallocator(1024);
    int err_number = 0;
    //allocate an integer

    BEGINTIMER
    int* a = dallocator.allocate<int>(1, err_number);
    ENDTIMER


    TEST_MESSAGE(a != nullptr, "Failed to allocate memory");

    if(a != nullptr){
        *a = 5;

        std::cout << "Value of a: " << *a << std::endl;
        std::cout << "Address of a: " << a << std::endl;

        TEST_MESSAGE(*a == 5, "Failed to set value of allocated memory");

        std::cout << std::endl;

        LOG_TIMETAKEN(begin, end)
    } 

    //deallocate memory
    dallocator.deallocate<int>(a);
}

DEFINE_TEST_G(UpBump_SingleIntTest, UpBump){
    UpBump uallocator(1024);
    int err_number = 0;
    //allocate an integer

    BEGINTIMER
    int* a = uallocator.allocate<int>(1, err_number);
    ENDTIMER

    TEST_MESSAGE(a != nullptr, "Failed to allocate memory");

    if(a != nullptr){
        *a = 5;
        TEST_MESSAGE(*a == 5, "Failed to set value of allocated memory");

        std::cout << std::endl;
        
        LOG_TIMETAKEN(begin, end)
    } 

    //deallocate memory
    uallocator.deallocate<int>(a);
}


DEFINE_TEST_G(DownBump_MultipleIntTest, DownBump){
    DownBump dallocator(1024);
    int err_number = 0;
    //allocate multiple integers

    BEGINTIMER
    int* a = dallocator.allocate<int>(1, err_number);
    int* b = dallocator.allocate<int>(1, err_number);
    int* c = dallocator.allocate<int>(1, err_number);
    ENDTIMER

    TEST_MESSAGE(a != nullptr, "Failed to allocate memory");
    TEST_MESSAGE(b != nullptr, "Failed to allocate memory");
    TEST_MESSAGE(c != nullptr, "Failed to allocate memory");

    if(a != nullptr && b != nullptr && c != nullptr){
        *a = 5;
        *b = 10;
        *c = 15;
        TEST_MESSAGE(*a == 5, "Failed to set value of allocated memory");
        TEST_MESSAGE(*b == 10, "Failed to set value of allocated memory");
        TEST_MESSAGE(*c == 15, "Failed to set value of allocated memory");

        std::cout << std::endl;

        LOG_TIMETAKEN(begin, end)
        
    } 

    //deallocate memory
    dallocator.deallocate<int>(a);
    dallocator.deallocate<int>(b);
    dallocator.deallocate<int>(c);
}

DEFINE_TEST_G(UpBump_MultipleIntTest, UpBump){
    UpBump uallocator(1024);
    int err_number = 0;
    //allocate multiple integers

    BEGINTIMER
    int* a = uallocator.allocate<int>(1, err_number);
    int* b = uallocator.allocate<int>(1, err_number);
    int* c = uallocator.allocate<int>(1, err_number);
    ENDTIMER

    TEST_MESSAGE(a != nullptr, "Failed to allocate memory");
    TEST_MESSAGE(b != nullptr, "Failed to allocate memory");
    TEST_MESSAGE(c != nullptr, "Failed to allocate memory");

    if(a != nullptr && b != nullptr && c != nullptr){
        *a = 5;
        *b = 10;
        *c = 15;
        TEST_MESSAGE(*a == 5, "Failed to set value of allocated memory");
        TEST_MESSAGE(*b == 10, "Failed to set value of allocated memory");
        TEST_MESSAGE(*c == 15, "Failed to set value of allocated memory");

        std::cout << std::endl;

        LOG_TIMETAKEN(begin, end)
        
    } 

    //deallocate memory
    uallocator.deallocate<int>(a);
    uallocator.deallocate<int>(b);
    uallocator.deallocate<int>(c);
}



DEFINE_TEST_G(DownBump_IntArray, DownBump){
    DownBump dallocator(1024);
    int err_number = 0;
    //allocate an array of integers

    BEGINTIMER
    int* a = dallocator.allocate<int>(10, err_number);
    ENDTIMER

    TEST_MESSAGE(a != nullptr, "Failed to allocate memory");

    if(a != nullptr){
        for (int i = 0; i < 10; i++){
            a[i] = i;
        }

        for (int i = 0; i < 10; i++){
            TEST_MESSAGE(a[i] == i, "Failed to set value of allocated memory");
        }

        std::cout << std::endl;

        LOG_TIMETAKEN(begin, end)
   
    } 

    //deallocate memory
    dallocator.deallocate<int>(a);
}


DEFINE_TEST_G(UpBump_IntArray, UpBump){
    UpBump uallocator(1024);
    int err_number = 0;
    //allocate an array of integers

    BEGINTIMER
    int* a = uallocator.allocate<int>(10, err_number);
    ENDTIMER

    TEST_MESSAGE(a != nullptr, "Failed to allocate memory");

    if(a != nullptr){
        for (int i = 0; i < 10; i++){
            a[i] = i;
        }

        for (int i = 0; i < 10; i++){
            TEST_MESSAGE(a[i] == i, "Failed to set value of allocated memory");
        }

        std::cout << std::endl;
    
        LOG_TIMETAKEN(begin, end)
    } 

    //deallocate memory
    uallocator.deallocate<int>(a);
}



DEFINE_TEST_G(DownBump_StringTest, DownBump){
    DownBump dallocator(1024);
    int err_number = 0;
    //allocate a string

    BEGINTIMER
    char* a = dallocator.allocate<char>(10, err_number);
    ENDTIMER

    TEST_MESSAGE(a != nullptr, "Failed to allocate memory");

    if(a != nullptr){
        for (int i = 0; i < 9; i++){
            a[i] = 'a';
        }
        a[9] = '\0';

        TEST_MESSAGE(a[0] == 'a' && a[8] == 'a' && a[9] == '\0', "Failed to set value of allocated memory");

        std::cout << std::endl;

        LOG_TIMETAKEN(begin, end)
     
    } 

    //deallocate memory
    dallocator.deallocate<char>(a);
}

DEFINE_TEST_G(UpBump_StringTest, UpBump){
    UpBump uallocator(1024);
    int err_number = 0;
    //allocate a string

    BEGINTIMER
    char* a = uallocator.allocate<char>(10, err_number);
    ENDTIMER

    TEST_MESSAGE(a != nullptr, "Failed to allocate memory");

    if(a != nullptr){
        for (int i = 0; i < 9; i++){
            a[i] = 'a';
        }
        a[9] = '\0';

        TEST_MESSAGE(a[0] == 'a' && a[8] == 'a' && a[9] == '\0', "Failed to set value of allocated memory");

        std::cout << std::endl;

        LOG_TIMETAKEN(begin, end)

    } 

    //deallocate memory
    uallocator.deallocate<char>(a);
}


//large tests
DEFINE_TEST_G(DownBump_LargeTest, DownBump){
    DownBump dallocator(1024);
    int err_number = 0;
    //allocate a ton of chars

    BEGINTIMER
    for (int i = 0; i < 1000; i++){
        char* a = dallocator.allocate<char>(1, err_number);
        dallocator.deallocate<char>(a);
    }
    ENDTIMER

    std::cout << std::endl;

    LOG_TIMETAKEN(begin, end)

}

DEFINE_TEST_G(UpBump_LargeTest, UpBump){
    UpBump uallocator(1024);
    int err_number = 0;
    //allocate a ton of chars

    BEGINTIMER
    for (int i = 0; i < 1000; i++){
        char* a = uallocator.allocate<char>(1, err_number);
        uallocator.deallocate<char>(a);
    }
    ENDTIMER

    std::cout << std::endl;

    LOG_TIMETAKEN(begin, end)

}


DEFINE_TEST_G(DownBump_LargeTest2, DownBump){
    DownBump dallocator(1024);
    int err_number = 0;
    //allocate a ton of ints

    BEGINTIMER
    for (int i = 0; i < 1000; i++){
        int* a = dallocator.allocate<int>(1, err_number);
        dallocator.deallocate<int>(a);
    }
    ENDTIMER

    std::cout << std::endl;

    LOG_TIMETAKEN(begin, end)

}

DEFINE_TEST_G(UpBump_LargeTest2, UpBump){
    UpBump uallocator(1024);
    int err_number = 0;
    //allocate a ton of ints

    BEGINTIMER
    for (int i = 0; i < 1000; i++){
        int* a = uallocator.allocate<int>(1, err_number);
        uallocator.deallocate<int>(a);
    }
    ENDTIMER

    std::cout << std::endl;

    LOG_TIMETAKEN(begin, end)

}

//extra large tests
DEFINE_TEST_G(DownBump_ExtraLargeTest, DownBump){
    DownBump dallocator(1024);
    int err_number = 0;
    //allocate a ton of chars

    BEGINTIMER
    for (int i = 0; i < 1000; i++){
        char* a = dallocator.allocate<char>(1023, err_number);
        dallocator.deallocate<char>(a);
    }
    ENDTIMER

    std::cout << std::endl;

    LOG_TIMETAKEN(begin, end)

}

DEFINE_TEST_G(UpBump_ExtraLargeTest, UpBump){
    UpBump uallocator(1024);
    int err_number = 0;
    //allocate a ton of chars

    BEGINTIMER
    for (int i = 0; i < 1000; i++){
        char* a = uallocator.allocate<char>(1023, err_number);
        uallocator.deallocate<char>(a);
    }
    ENDTIMER

    std::cout << std::endl;

    LOG_TIMETAKEN(begin, end)

}

DEFINE_TEST_G(DownBump_ExtraLargeTest2, DownBump){
    DownBump dallocator(1024);
    int err_number = 0;
    //allocate a ton of ints

    BEGINTIMER
    for (int i = 0; i < 1000; i++){
        int* a = dallocator.allocate<int>(256, err_number);
        dallocator.deallocate<int>(a);
    }
    ENDTIMER

    std::cout << std::endl;

    LOG_TIMETAKEN(begin, end)

}

DEFINE_TEST_G(UpBump_ExtraLargeTest2, UpBump){
    UpBump uallocator(1024);
    int err_number = 0;
    //allocate a ton of ints

    BEGINTIMER
    for (int i = 0; i < 1000; i++){
        int* a = uallocator.allocate<int>(256, err_number);
        uallocator.deallocate<int>(a);
    }
    ENDTIMER

    std::cout << std::endl;

    LOG_TIMETAKEN(begin, end)

}

int main(){

    std::cout << "Steady clock precision: " << std::chrono::steady_clock::period::num << "/"
              << std::chrono::steady_clock::period::den << " seconds" << std::endl;


    bool pass = true;
    for (auto group : groups) {
        pass &= TestFixture::ExecuteTestGroup(group, TestFixture::Verbose);
        std::cout << std::endl;
    }
    return pass ? 0 : 1;
}