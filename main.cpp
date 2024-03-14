#include <iostream>
#include "ArrayList.hpp"

int main() {
    ArrayList array(10);
    std::cout << std::endl << "Tablica po dodaniu elementów na koniec: " << std::endl;
    for (int i = 0; i < 5; i++) {
        array.addLast(i+1);
    }
    array.display();

    for (int i = 0; i < 7; i++) {
        array.addFirst((i+1)*1000);
    }
    std::cout << std::endl << "Tablica po dodaniu elementów na początek: " << std::endl;
    array.display();
}