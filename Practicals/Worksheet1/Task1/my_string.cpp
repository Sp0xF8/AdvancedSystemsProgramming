#include "my_string.hpp"


my_string::my_string(){
    this->string = nullptr;
}




my_string::my_string(const char* cStr) {

    size_t len = strlen(cStr);
    len += 1; // null terminal

    this->string = new char[len];

    strncpy_s(this->string, len, cStr, len);
}

my_string::my_string(my_string const& s){
    this->string = s.string;
}

my_string& my_string::operator= (my_string const& s) {

    if (this->string != nullptr) {
        delete this->string;
    }
    this->string = s.string;

    return *this;
}

my_string::~my_string(){

}



char my_string::getChar(const int& i) const {
    return this->string[i];
}

void my_string::setChar(const int& i, const char& c) {
   this->string[i] = c;
}

void my_string::print() const {
    std::cout << this->string << std::endl;
}