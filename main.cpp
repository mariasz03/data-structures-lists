#include <iostream>
#include "headers/ArrayList.hpp"
#include "headers/SinglyLinkedList.hpp"
#include "headers/SinglyLinkedListTail.hpp"
#include "headers/DoublyLinkedList.hpp"

int main() {
    SinglyLinkedList list;
    ArrayList arrayList;
    DoublyLinkedList tailList;
    for (int i = 0; i < 100; i++) {
        tailList.addLast(i);
    }
    tailList.addAt(21, 777);
    tailList.display();
}