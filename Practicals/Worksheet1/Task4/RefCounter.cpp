#include "RefCounter.hpp"
#include <iostream>



template <typename T>
RefCounter<T>::RefCounter(T* object) {
    this->object = object;
    this->references = new uint64_t(1);
}

template <typename T>
RefCounter<T>::RefCounter(const RefCounter& other) {
    this->object = other.object;
    this->references = other.references;
    *this->references += 1;
}

template <typename T>
RefCounter<T>& RefCounter<T>::operator=(const RefCounter& other) {
    if (this->object != nullptr) {
        delete this->object;
    }

    this->object = other.object;
    this->references = other.references;
    *this->references += 1;

    return *this;
}

template <typename T>
RefCounter<T>::~RefCounter() {
    *this->references -= 1;

    if (*this->references == 0) {
        std::cout << "Deleting object, out of scope" << std::endl;
        delete this->object;
        delete this->references;
    }
}

template <typename T>
T* RefCounter<T>::getObject() {
    return this->object;
}


template <typename T>
uint64_t RefCounter<T>::getReferences() {
    return *this->references;
}

template <typename T>
void RefCounter<T>::printRefs() {
    std::cout << "XRefs [" << *this->references << "]" << std::endl;
}


#include "../Task3/my_string.hpp"
template class RefCounter<my_string>;