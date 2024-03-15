#include "ArrayList.hpp"

ArrayList::ArrayList(int initialCapacity) : capacity_(initialCapacity), size_(0) {
    array_ = new int[capacity_];
};

ArrayList::~ArrayList() {
    delete[] array_;
};

void ArrayList::addLast(int element) { // Dodanie elementu na koniec tablicy
    if(size_ >= capacity_) { // Stworzenie nowej, dwa razy wiekszej tablicy oraz skopiowanie starej tablicy do nowej
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

void ArrayList::addFirst(int element) { // Dodanie elementu na poczatek tablicy
    if(size_ >= capacity_) { // Stworzenie nowej, dwa razy wiekszej tablicy oraz skopiowanie starej tablicy do nowej z przesunieciem elementow o 1 w prawo
        int newCapacity = capacity_ * 2;
        int* newArray = new int[newCapacity];
        for (int i = 0; i < size_; i++) {
            newArray[i+1] = array_[i];
        }
        delete[] array_;
        array_ = newArray;
        capacity_ = newCapacity;
    } else { // Przesuniecie elementów o 1 w prawo
        for (int i = size_; i > 0; i--) {
            array_[i] = array_[i-1];
        }
    }
    array_[0] = element;
    size_++;
};

void ArrayList::addAt(int index, int element) // Dodanie elementu na okreslonym indeksie
{
    if (index >= 0 || index <= size_) { // Stworzenie nowej, dwa razy wiekszej tablicy oraz skopiowanie starej tablicy do nowej z przesunieciem 
    // elementow za indeksem o 1, w prawo (po to, aby zrobic miejsce na element)                                                                                                        
        if(size_ >= capacity_) {
            int newCapacity = capacity_ * 2;
            int* newArray = new int[newCapacity];

            int j = 0;
            for (int i = 0; i < size_; i++) {
                if (i == index) {
                    newArray[i] = element;
                } else {
                    newArray[i] = array_[j++];
                }
            }

            delete[] array_;
            array_ = newArray;
            capacity_ = newCapacity;
        } else { // Przesuniecie elementow za indeksem o 1, w prawo
            for (int i = size_-1; i > index; i--) {
                array_[i] = array_[i-1];
            }
            array_[index] = element;
        }
        size_++;
    } else {
        std::cout << "Niepoprawny index.";
    }

};

void ArrayList::removeLast() {
    
}



void ArrayList::display() {
    for(int i = 0; i < size_; i++) {
        std::cout << i << ": " << array_[i] << std::endl;
    }
};

int ArrayList::get(int index) {
    if (index < 0 || index >= size_) {
        return -1;
    }
    return array_[index];
}

int ArrayList::getSize() {
    return size_;
};

int ArrayList::getCapacity() {
    return capacity_;
};