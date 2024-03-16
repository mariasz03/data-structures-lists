#include <iostream>
#include "ArrayList.hpp"

int main() {
    bool loop = true;
    ArrayList array(10);
    for (int i = 0; i < 10; i++) {
        array.addLast(i);
    }
    while(loop) {
        std::cout << "Rozmiar tablicy: " << array.getSize() << "/" << array.getCapacity() << std::endl;
        array.display();
        std::cout << std::endl << "____________________________________________" << std::endl<< "Co chcesz zrobic?" << std::endl;
        std::cout << "1. Pokaz rozmiar i pojemnosc tablicy." << std::endl;
        std::cout << "2. Wyswietl element tablicy." << std::endl;
        std::cout << "3. Wyswietl cala tablice." << std::endl;
        std::cout << "4. Dodaj element na poczatek." << std::endl;
        std::cout << "5. Dodaj element na koniec." << std::endl;
        std::cout << "6. Dodaj element na pozycji." << std::endl;
        std::cout << "7. Usun element z konca tablicy." << std::endl;
        std::cout << "8. Usun element z poczatku tablicy." << std::endl;
        std::cout << "9. Usun element na pozycji." << std::endl;
        std::cout << "10. Zakoncz." << std::endl;
        int option;
        int element;
        int index;
        std::cin >> option;
        switch (option)
        {
        case 1:
            std::cout << "Rozmiar tablicy: " << array.getSize() << "/" << array.getCapacity() << std::endl;
            break;
        
        case 2:
            int index;
            std::cout << "Podaj index elementu: ";
            std::cin >> index;
            std::cout << "Element " << index << ": " << array.getElement(index) << std::endl;
            break;
        case 3:
            array.display();
            break;
        case 4:
            std::cout << "Podaj element ktory chcesz dodac na poczatek tablicy: ";
            std::cin >> element;
            array.addFirst(element);
            std::cout << "Pomyslnie dodano element " << element << " na poczatek tablicy.";
            break;
        case 5:
            std::cout << "Podaj element ktory chcesz dodac na koniec tablicy: ";
            std::cin >> element;
            array.addLast(element);
            std::cout << "Pomyslnie dodano element " << element << " na koniec tablicy.";
            break;
        case 6:
            std::cout << "Podaj element ktory chcesz dodac: ";
            std::cin >> element;
            std::cout << "Podaj index na ktory chcesz dodac element: ";
            std::cin >> index;
            array.addAt(index, element);
            std::cout << "Pomyslnie dodano element " << element << " na index." << index << std::endl;
            break;
        case 7:
            array.removeLast();
            std::cout << "Pomyslnie usunieto element." << std::endl;
            break;
        case 8:
            array.removeFirst();
            std::cout << "Pomyslnie usunieto element." << std::endl;
            break;
        case 9:
            std::cout << "Podaj index elementu ktorego chcesz usunac z tablicy: ";
            std::cin >> index;
            array.removeFrom(index);
            std::cout << "Pomyslnie usunieto element."<< std::endl;
            break;
        case 10:
            loop = false;
            break;
        }
    }
}