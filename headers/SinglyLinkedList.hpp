#include <iostream>
#pragma once

class Node {
public:
    int element;
    Node* next;

    Node(int element);
};

class SinglyLinkedList {
private:
    Node* head;
public:
    SinglyLinkedList();
    ~SinglyLinkedList();

    void addLast(int element);
    void addFirst(int element);
    void addAt(int index, int element);

    void removeLast();
    void removeFirst();
    void removeFrom(int index);

    int findElement(int element);

    void display();
    int getElement(int index);
    int getSize();
};