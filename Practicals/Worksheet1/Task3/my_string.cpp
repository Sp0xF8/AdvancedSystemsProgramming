#include "my_string.hpp"


my_string::my_string(){
    this->string = nullptr;
    this->references = 0;
}




my_string::my_string(const char* cStr) {

    size_t len = strlen(cStr);
    len += 1; // null terminal

    this->string = new char[len];

    strncpy_s(this->string, len, cStr, len);
    this->references = new uint64_t(1);
}

my_string::my_string(my_string const& s){

    this->string = s.string;
    this->references = s.references;
    *this->references += 1;
}

my_string& my_string::operator= (my_string const& s) {

    if (this->string != nullptr) {
        delete this->string;
    }

    this->string = s.string;
    this->references = s.references;
    *this->references += 1;

    return *this;
}

my_string::~my_string(){
    *this->references -= 1;

    if (*this->references == 0) {
        std::cout << "Deleting object, out of scope" << std::endl;
        delete this->string;
        delete this->references;
    }
}




char my_string::getChar(const int& i) const {
    return this->string[i];
}

void my_string::setChar(const int& i, const char& c) {
   this->string[i] = c;
}

void my_string::print() const {
    std::cout << this->string << "[" << *this->references << "]" << std::endl;
}