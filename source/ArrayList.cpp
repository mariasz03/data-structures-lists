#include "../headers/ArrayList.hpp"

ArrayList::ArrayList(int initialCapacity) : initialCapacity_(initialCapacity), capacity_(initialCapacity), size_(0) {
    array_ = new int[capacity_];
}

ArrayList::~ArrayList() {
    delete[] array_;
}

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
}

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
}

void ArrayList::addAt(int index, int element) // Dodanie elementu na okreslonym indeksie
{
    if (index >= 0 && index <= size_) { // Stworzenie nowej, dwa razy wiekszej tablicy oraz skopiowanie starej tablicy do nowej z przesunieciem 
    // elementow za indeksem o 1, w prawo (po to, aby zrobic miejsce na element)                                                                                                        
        if(size_ >= capacity_) {
            int newCapacity = capacity_ * 2;
            int* newArray = new int[newCapacity];

            for (int i = 0; i < index; i++) { // tutaj nie ma potrzeby iteracji od konca, poniewaz i tak kopiujemy elementy do nowej tablicy
                newArray[i] = array_[i];
            }
            newArray[index] = element;
            for (int i = index; i < size_; i++) {
                newArray[i+1] = array_[i];
            }

            delete[] array_;
            array_ = newArray;
            capacity_ = newCapacity;
        } else { // Przesuniecie elementow za indeksem o 1, w prawo
            for (int i = size_; i > index; i--) { // iteracja od konca
                array_[i] = array_[i-1];
            }
            array_[index] = element;
        }
        size_++;
    } else {
        throw std::out_of_range("Index out of range.");
    }
}

void ArrayList::removeLast() { // Usuniecie ostatniego elementu
    if (size_ > 0) {
        if(size_ - 1 <= capacity_ / 2 && capacity_ > initialCapacity_) {
            int newCapacity = capacity_ / 2;
            int* newArray = new int[newCapacity];
            for (int i = 0; i < size_ - 1; i++) {
                newArray[i] = array_[i];
            }
            delete[] array_;
            array_ = newArray;
            capacity_ = newCapacity;
        }
        size_--;
    }
}

void ArrayList::removeFirst() { // Usuniecie pierwszego elementu
    if (size_ > 0) {
        if(size_-1 <= capacity_ / 2 && capacity_ > initialCapacity_) { 
            int newCapacity = capacity_ / 2;
            int* newArray = new int[newCapacity];
            for (int i = 0; i < size_ - 1; i++) {
                newArray[i] = array_[i+1];
            }
            delete[] array_;
            array_ = newArray;
            capacity_ = newCapacity;
        } else { // Przesuniecie elementów o 1 w lewo
            for (int i = 0; i < size_ - 1; i++) {
                array_[i] = array_[i+1];
            }
        }
        size_--;
    }
}

void ArrayList::removeFrom(int index) {
    if (size_ > 0 && index >= 0 && index <= size_) {
        if (size_ - 1 <= capacity_ / 2 && capacity_ > initialCapacity_) {
            int newCapacity = capacity_ / 2;
            int *newArray = new int[newCapacity];
            for (int i = 0; i < index; i++) {
                newArray[i] = array_[i];
            }
            for (int i = index; i < size_ - 1; i++) {
                newArray[i] = array_[i+1];
            }
            delete[] array_;
            array_ = newArray;
            capacity_ = newCapacity;
        } else { // Przesuniecie elementów o 1 w lewo, zaczynajac dopiero od tego ktory chcemy usunac
            for (int i = index; i < size_ - 1; i++) {
                array_[i] = array_[i+1];
            }
        }
        size_--;
    } else {
        throw std::out_of_range("Index out of range.");
    }
}

int ArrayList::findElement(int element) {
    for (int i = 0; i < size_; i++) {
        if (array_[i] == element) {
            return i;
        }
    }
    return -1;
}

void ArrayList::display() {
    for(int i = 0; i < size_; i++) {
        std::cout << i << ": " << array_[i] << std::endl;
    }
}

void ArrayList::reset() {
    delete[] array_;
    capacity_ = initialCapacity_;
    size_ = 0;
    array_ = new int[capacity_];
}

int ArrayList::getElement(int index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range.");
    }
    return array_[index];
}

int ArrayList::getSize() {
    return size_;
}

int ArrayList::getCapacity() {
    return capacity_;
}
