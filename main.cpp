#include <iostream>
#include "headers/ArrayList.hpp"
#include "headers/SinglyLinkedList.hpp"

int main() {
    SinglyLinkedList list;
    for (int i = 0; i < 100; i++) {
        list.addLast(i);
    }
    list.display();
    std::cout << list.getElement(99);
}