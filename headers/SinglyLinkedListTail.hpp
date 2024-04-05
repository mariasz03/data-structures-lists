#include <iostream>
#pragma once

class Node {
public:
    int element;
    Node* next;

    Node(int element);
};

class SinglyLinkedListTail {
private:
    Node* head;
    Node* tail;
public:
    SinglyLinkedListTail(); 
    ~SinglyLinkedListTail();

    void addLast(int element); // Dodawanie na koncu
    void addFirst(int element); // Dodawanie na poczatku
    void addAt(int index, int element); // Dodawanie na indeksie

    void removeLast(); // Usuwanie z konca
    void removeFirst(); // Usuwanie z poczatku
    void removeFrom(int index); // Usuwanie z indeksu

    int findElement(int element); // Wyszukiwanie pierwszego elementu o podanej wartosci i zwrocenie indeksu na ktorym sie znajduje

    void display(); // Wyswietlanie calej listy
    int getElement(int index); // Zwraca wartosc elementu na podanym indeksie
    int getSize(); // Zwraca rozmiar listy
};