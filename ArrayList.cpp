#include "ArrayList.hpp"

ArrayList::ArrayList(int initialCapacity) : capacity_(initialCapacity), size_(0) {
    array_ = new int[capacity_];
};

ArrayList::~ArrayList() {
    delete[] array_;
};

void ArrayList::addLast(int element) {
    if(size_ >= capacity_) {
        int newCapacity = capacity_ * 2;
        int* newArray = new int[newCapacity];
        for (int i = 0; i < size_; i++) {
            newArray[i] = array_[i];
        }
        delete[] array_;
        array_ = newArray;
        capacity_ = newCapacity;
    }
    array_[size_] = element;
    size_++;
};

void ArrayList::addFirst(int element) {
    int* newArray;
    if (size_ >= capacity_) {
        int newCapacity = capacity_ * 2;
        newArray = new int[newCapacity];
        capacity_ = newCapacity;
    } else {
        newArray = new int[capacity_];
    }
    
    for (int i = 0; i < size_; i++) {
        newArray[i+1] = array_[i];
    }
    newArray[0] = element;
    size_++;
    delete[] array_;
    array_ = newArray;
};

void ArrayList::display() {
    std::cout << "Rozmiar: "  << getSize() << std::endl << "Pojemnosc: " << getCapacity() << std::endl;
    for(int i = 0; i < size_; i++) {
        std::cout << array_[i] << std::endl;
    }
};

int ArrayList::getSize() {
    return size_;
};

int ArrayList::getCapacity() {
    return capacity_;
};