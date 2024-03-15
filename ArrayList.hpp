#include <iostream>
#pragma once

class ArrayList {
private:
    int* array_;
    int capacity_;
    int size_;

public:
    ArrayList(int capacity = 10);
    ~ArrayList();

    void addLast(int element);
    void addFirst(int element);
    void addAt(int index, int element);

    void removeLast();
    void removeFirst();
    void removeFrom();

    void display();
    int get(int index);
    int getSize();
    int getCapacity();
};