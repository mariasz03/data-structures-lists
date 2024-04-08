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

enum Function {
    ADD_LAST,
    ADD_FIRST,
    ADD_AT,
    REMOVE_LAST,
    REMOVE_FIRST,
    REMOVE_FROM,
    FIND_ELEMENT
};

enum Structure {
    ARRAY_LIST,
    SINGLY_LINKED_LIST,
    SINGLY_LINKED_LIST_TAIL,
    DOUBLY_LINKED_LIST
};
uint32_t generateRandomNumberInRange(uint32_t seed, uint32_t max_value) {
    std::mt19937 gen(seed);
    std::uniform_int_distribution<uint32_t> dis(0, max_value);
    return dis(gen);
}

uint32_t generateRandomNumberFromSeed(uint32_t seed) {
    std::mt19937 gen(seed); 
    std::uniform_int_distribution<uint32_t> dis(0, std::numeric_limits<uint32_t>::max()); 

    return dis(gen);
}

uint32_t generateRandomNumber(std::mt19937 &gen) {
    std::uniform_int_distribution<uint32_t> dis(0, std::numeric_limits<uint32_t>::max());
    return dis(gen);
}

template<typename T>
void generateRandomData(T &container, int dataSetSize, uint32_t seed) {
    std::mt19937 gen(seed); 
    container.reset();
    for (int i = 0; i < dataSetSize; i++) {
        container.addLast(generateRandomNumber(gen)); 
    }
}

template<typename T>
double measure(T& container, int32_t number, int index, int32_t elementToFind, Function func) {
    TimerClock timer;
    switch (func) {
        case ADD_LAST:
            container.addLast(number);
            break;
        case ADD_FIRST:
            container.addFirst(number);
            break;
        case ADD_AT:
            container.addAt(index, number);
            break;
        case REMOVE_LAST:
            container.removeLast();
            break;
        case REMOVE_FIRST:
            container.removeFirst();
            break;
        case REMOVE_FROM:
            container.removeFrom(index);
            break;
        case FIND_ELEMENT:
            container.findElement(elementToFind);
            break;
        
    }
    return timer.elapsed();
}

template<typename T>
double measureAverage(T &container, Function func, uint32_t seed[], int repetitions, int size) {
    double avg;
    int sum = 0;
    for (int i = 0; i < repetitions; i++) {
        uint32_t number = generateRandomNumberFromSeed(seed[i]);
        int index = generateRandomNumberInRange(seed[i], size);
        int indexofElementToFind = generateRandomNumberInRange(seed[i], size);
        generateRandomData(container, size, seed[i]);
        uint32_t elementToFind = container.getElement(indexofElementToFind);
        double averageTime = measure(container, number, index, elementToFind, func);
        sum = sum + averageTime;
    }
    avg = sum / repetitions;
    return avg;
}

template<typename T>
void measureAndSave(T& container, Function func, uint32_t seed[], int dataSetsSize[], int repetitions, std::string fileName)
{
    std::ofstream output;
    output.open("measured_times/" + fileName);
    
    for (int i = 0; i < 8; i++) {
        double average = measureAverage(container, func, seed, repetitions, dataSetsSize[i]);
        output << dataSetsSize[i] << ", " << average << std::endl;
    }
    output.close();
} 


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
        std::cout << "9. Zmierz operacje. " << std::endl;
        std::cout << "10. Powrot do menu glownego." << std::endl;
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
                return;
            default:
                std::cout << "Niepoprawny wybor operacji." << std::endl;
                break;
        }
    }
}

int main() {
    srand((unsigned)time(NULL)); 
//    while (true) {
//         int structureMenu = 0;
//         std::cout << "Wybierz strukture danych:" << std::endl;
//         std::cout << "1. ArrayList" << std::endl;
//         std::cout << "2. Singly Linked List" << std::endl;
//         std::cout << "3. Singly Linked List (tail)" << std::endl;
//         std::cout << "4. Doubly Linked List" << std::endl;
//         std::cout << "5. Wyjscie" << std::endl;
//         std::cout << "Wybierz: ";
//         std::cin >> structureMenu;

//         switch (structureMenu) {
//             case 1: {
//                 ArrayList arrayList;
//                 performOperations(arrayList);
//                 break;
//             }
//             case 2: {
//                 SinglyLinkedList singlyLinkedList;
//                 performOperations(singlyLinkedList);
//                 break;
//             }
//             case 3: {
//                 SinglyLinkedListTail singlyLinkedListTail;
//                 performOperations(singlyLinkedListTail);
//                 break;
//             }
//             case 4: {
//                 DoublyLinkedList doublyLinkedList;
//                 performOperations(doublyLinkedList);
//                 break;
//             }
//             case 5:
//                 return 0; // Wyjscie z programu
//             default:
//                 std::cout << "Niepoprawny wybor struktury danych." << std::endl;
//                 break;
//         }
//     }
    // uint32_t seed[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // int dataSetsSize[8] = {5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000}; 
    // ArrayList arrayList;
    // SinglyLinkedList singlyLinkedList;
    // SinglyLinkedListTail singlyLinkedListTail;
    // DoublyLinkedList doublyLinkedList;
    // measureAndSave(singlyLinkedList, ADD_LAST, seed, dataSetsSize, "ArrayList_AddLast");


    // std::ofstream output("measured_times/output.txt");
    ArrayList arrayList;
    SinglyLinkedList singlyLinkedList;
    SinglyLinkedListTail singlyLinkedListTail;
    DoublyLinkedList doublyLinkedList;
    uint32_t seed[3] = {1, 2, 3};
    int dataSetsSize[8] = {5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000};


    measureAndSave(arrayList, ADD_FIRST, seed, dataSetsSize, 3, "ArrayList_AddAt.txt");
    measureAndSave(arrayList, ADD_LAST, seed, dataSetsSize, 3, "ArrayList_AddLast.txt");
    measureAndSave(arrayList, ADD_AT, seed, dataSetsSize, 3, "ArrayList_AddAt.txt");
    measureAndSave(arrayList, REMOVE_FIRST, seed, dataSetsSize, 3, "ArrayList_RemoveFirst.txt");
    measureAndSave(arrayList, REMOVE_LAST, seed, dataSetsSize, 3, "ArrayList_RemoveLast.txt");
    measureAndSave(arrayList, FIND_ELEMENT, seed, dataSetsSize, 3, "ArrayList_Find");

    measureAndSave(singlyLinkedList, ADD_FIRST, seed, dataSetsSize, 3, "SinglyLinkedList_AddFirst.txt");
    measureAndSave(singlyLinkedList, ADD_LAST, seed, dataSetsSize, 3, "SinglyLinkedList_AddLast.txt");
    measureAndSave(singlyLinkedList, ADD_AT, seed, dataSetsSize, 3, "SinglyLinkedList_AddAt.txt");
    measureAndSave(singlyLinkedList, REMOVE_FIRST, seed, dataSetsSize, 3, "SinglyLinkedList_RemoveFirst.txt");
    measureAndSave(singlyLinkedList, REMOVE_LAST, seed, dataSetsSize, 3, "SinglyLinkedList_RemoveLast.txt");
    measureAndSave(singlyLinkedList, FIND_ELEMENT, seed, dataSetsSize, 3, "SinglyLinkedList_Find.txt");

    measureAndSave(singlyLinkedListTail, ADD_FIRST, seed, dataSetsSize, 3, "SinglyLinkedListTail_AddFirst.txt");
    measureAndSave(singlyLinkedListTail, ADD_LAST, seed, dataSetsSize, 3, "SinglyLinkedListTail_AddLast.txt");
    measureAndSave(singlyLinkedListTail, ADD_AT, seed, dataSetsSize, 3, "SinglyLinkedListTail_AddAt.txt");
    measureAndSave(singlyLinkedListTail, REMOVE_FIRST, seed, dataSetsSize, 3, "SinglyLinkedListTail_RemoveFirst.txt");
    measureAndSave(singlyLinkedListTail, REMOVE_LAST, seed, dataSetsSize, 3, "SinglyLinkedListTail_RemoveLast.txt");
    measureAndSave(singlyLinkedListTail, FIND_ELEMENT, seed, dataSetsSize, 3, "SinglyLinkedListTail_Find.txt");

    measureAndSave(doublyLinkedList, ADD_FIRST, seed, dataSetsSize, 3, "DoublyLinkedList_AddFirst.txt");
    measureAndSave(doublyLinkedList, ADD_LAST, seed, dataSetsSize, 3, "DoublyLinkedList_AddLast.txt");
    measureAndSave(doublyLinkedList, ADD_AT, seed, dataSetsSize, 3, "DoublyLinkedList_AddAt.txt");
    measureAndSave(doublyLinkedList, REMOVE_FIRST, seed, dataSetsSize, 3, "DoublyLinkedList_RemoveFirst.txt");
    measureAndSave(doublyLinkedList, REMOVE_LAST, seed, dataSetsSize, 3, "DoublyLinkedList_RemoveLast.txt");
    measureAndSave(doublyLinkedList, FIND_ELEMENT, seed, dataSetsSize, 3, "DoublyLinkedList_Find.txt");
}



