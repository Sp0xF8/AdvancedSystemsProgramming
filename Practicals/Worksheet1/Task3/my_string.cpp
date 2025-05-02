#include "my_string.hpp"


#ifndef _WIN32

    #include <cstring>
    #define strncpy_s(s1, l1, s2, l2) strncpy(s1, s2, l1)
#endif



my_string::my_string(){
    this->string = nullptr;
    this->references = new uint64_t(1);
}



my_string::my_string(const char* cStr) {

    size_t len = strlen(cStr);
    len += 1; // null terminal

    this->string = new char[len];

    strncpy_s(this->string, len, cStr, len);
    this->references = new uint64_t(1);
}

my_string::my_string(my_string const& s){

    size_t len = strlen(s.string);
    len += 1; // null terminal

    this->string = new char[len];

    strncpy_s(this->string, len, s.string, len);

    this->references = s.references;
    *this->references += 1;
}

my_string& my_string::operator= (my_string const& s) {

    if (this->string != nullptr) {
        delete this->string;
    }

    size_t len = strlen(s.string);
    len += 1; // null terminal

    this->string = new char[len];

    strncpy_s(this->string, len, s.string, len);

    this->references = s.references;
    *this->references += 1;

    return *this;
}

my_string::~my_string(){
    *this->references -= 1;

    if (*this->references == 0) {
        std::cout << "Deleting object, out of scope" << std::endl;

        if(this->string != nullptr) {

            delete this->string;
        }
        
        delete this->references;
    }
}

char my_string::getChar(const int& i) const {
    if (i > strlen(this->string) && i >= 0 && this->string != nullptr) { return '\0'; }

    return this->string[i];
}

void my_string::setChar(const int& i, const char& c) {
    if (i > strlen(this->string) && i >= 0 && this->string != nullptr) { return; }

    this->string[i] = c;
}

void my_string::print() const {
    if(this->string == nullptr) { return; }
    std::cout << this->string << "[" << *this->references << "]" << std::endl;
}