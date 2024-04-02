#include <iostream>
#pragma once

class ArrayList {
private:
    int* array_;
    int initialCapacity_;
    int capacity_;
    int size_;

public:
    ArrayList(int capacity = 10);
    ~ArrayList();

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
    int getCapacity(); // Zwraca pojemnosc tablicy
};