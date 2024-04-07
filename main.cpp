#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdint>
#include <random>
#include "headers\ArrayList.hpp"
#include "headers\SinglyLinkedList.hpp"
#include "headers\SinglyLinkedListTail.hpp"
#include "headers\DoublyLinkedList.hpp"
#include "headers\Timer.hpp"
#include "source\generate_random_data.cpp"

template<typename T>
void performOperations(T& dataStructure) {
    int operationMenu = 0;
    int element, index;

    while (true) {
        std::cout << "Wybierz operacje:" << std::endl;
        std::cout << "1. Dodaj na koncu." << std::endl;
        std::cout << "2. Dodaj na poczatku." << std::endl;
        std::cout << "3. Dodaj na indeksie." << std::endl;
        std::cout << "4. Usun z konca." << std::endl;
        std::cout << "5. Usun z poczatku." << std::endl;
        std::cout << "6. Usun z indeksu." << std::endl;
        std::cout << "7. Znajdz element." << std::endl;
        std::cout << "8. Wyswietl dane." << std::endl;
        std::cout << "9. Powrot do menu glownego." << std::endl;
        std::cout << "Wybierz: ";
        std::cin >> operationMenu;

        switch (operationMenu) {
            case 1:
                std::cout << "Podaj element do dodania na koncu: ";
                std::cin >> element;
                dataStructure.addLast(element);
                break;
            case 2:
                std::cout << "Podaj element do dodania na poczatku: ";
                std::cin >> element;
                dataStructure.addFirst(element);
                break;
            case 3:
                std::cout << "Podaj indeks: ";
                std::cin >> index;
                std::cout << "Podaj element do dodania na indeksie " << index << ": ";
                std::cin >> element;
                dataStructure.addAt(index, element);
                break;
            case 4:
                dataStructure.removeLast();
                break;
            case 5:
                dataStructure.removeFirst();
                break;
            case 6:
                std::cout << "Podaj indeks do usuniecia: ";
                std::cin >> index;
                dataStructure.removeFrom(index);
                break;
            case 7:
                std::cout << "Podaj element do znalezienia: ";
                std::cin >> element;
                std::cout << "Indeks pierwszego wystapienia elementu: " << dataStructure.findElement(element) << std::endl;
                break;
            case 8:
                std::cout << "Wyswietlanie danych:" << std::endl;
                dataStructure.display();
                break;
            case 9:
                return; // Powrot do menu glownego
            default:
                std::cout << "Niepoprawny wybor operacji." << std::endl;
                break;
        }
    }
}

int main() {

   while (true) {
        int structureMenu = 0;
        std::cout << "Wybierz strukture danych:" << std::endl;
        std::cout << "1. ArrayList" << std::endl;
        std::cout << "2. Singly Linked List" << std::endl;
        std::cout << "3. Singly Linked List (tail)" << std::endl;
        std::cout << "4. Doubly Linked List" << std::endl;
        std::cout << "5. Wyjscie" << std::endl;
        std::cout << "Wybierz: ";
        std::cin >> structureMenu;

        switch (structureMenu) {
            case 1: {
                ArrayList arrayList;
                performOperations(arrayList);
                break;
            }
            case 2: {
                SinglyLinkedList singlyLinkedList;
                performOperations(singlyLinkedList);
                break;
            }
            case 3: {
                SinglyLinkedListTail singlyLinkedListTail;
                performOperations(singlyLinkedListTail);
                break;
            }
            case 4: {
                DoublyLinkedList doublyLinkedList;
                performOperations(doublyLinkedList);
                break;
            }
            case 5:
                return 0; // Wyjscie z programu
            default:
                std::cout << "Niepoprawny wybor struktury danych." << std::endl;
                break;
        }
    }
}
    // std::ofstream outputTime("measured_times/output.txt");

    // ArrayList arrayList;
    // SinglyLinkedList list;
    // int dataSetsSize[8] = {5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000};
    // generateRandomData(arrayList, dataSetsSize[1]);
    // uint32_t randNum = generateRandomNumber();
    // TimerClock timer;
    // list.addLast(randNum);
    // double elapsed = timer.elapsed();
    // arrayList.removeLast();
    // std::cout << "Time: " << elapsed << "[ns]" << std::endl;
    

    // return 0;
