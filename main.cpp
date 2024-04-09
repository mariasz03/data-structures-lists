#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdint>
#include <random>
#include "headers\ArrayList.hpp"
#include "headers\SinglyLinkedList.hpp"
#include "headers\SinglyLinkedListTail.hpp"
#include "headers\DoublyLinkedList.hpp"
#include "headers\TimerClock.hpp"

int dataSetsSize[8] = {5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000}; // Wielkosci zestawow danych do zmierzenia

enum Function {
    ADD_LAST,
    ADD_FIRST,
    ADD_AT,
    REMOVE_LAST,
    REMOVE_FIRST,
    REMOVE_FROM,
    FIND_ELEMENT
};

// Funkcja generujaca pseudolosowa liczbe z zakresu 0 do max_value
uint32_t generateRandomNumberInRange(uint32_t seed, uint32_t max_value) { 
    std::mt19937 gen(seed);
    std::uniform_int_distribution<uint32_t> dis(0, max_value);
    return dis(gen);
}

// Funkcja generujaca pseudolosowa liczbe z seeda
uint32_t generateRandomNumberFromSeed(uint32_t seed) { 
    std::mt19937 gen(seed); 
    std::uniform_int_distribution<uint32_t> dis(0, std::numeric_limits<uint32_t>::max()); 

    return dis(gen);
}

uint32_t generateRandomNumber(std::mt19937 &gen) { 
    std::uniform_int_distribution<uint32_t> dis(0, std::numeric_limits<uint32_t>::max());
    return dis(gen);
}

// Funkcja generujaca pseudolosowy zestaw liczb (o romiarze dataSetSize)
template<typename T>
void generateRandomData(T &container, int dataSetSize, uint32_t seed) { 
    std::mt19937 gen(seed); 
    container.reset();
    for (int i = 0; i < dataSetSize; i++) {
        container.addLast(generateRandomNumber(gen)); 
    }
}

// Funkcja mierzaca czas dzialania operacji (func) struktury (container). 
// number - element ktory ma zostac dodany, 
// index - index elementu na ktorym beda wykonywane operacje,
// elementToFind - element ktory ma byc szukany w strukturze
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

// Funkcja mierzaca sredni czas operacji
// container - struktura ktora ma byc mierzona
// func - mierzona operacja
// seed[] - tablica seedow zasilajaca elementy generowana losowo
// repetitions - liczba powtorzen, funkcji potrzebna do zmierzenia sredniej
// size - rozmiar struktury potrzebny do wygenerowania indeksu na ktory ma zostac dodany element
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

// Funkcja ktora mierzy czasy i zapisuje je do pliku. Argumenty te same co wyzej + nazwa pliku (fileName)
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

// Menu do wybrania operacji ktora chcemy przeprowadzic na wybranej wczesniej strukturze
template<typename T>
void performOperations(T& dataStructure) {
    int operationMenu;
    int element, index;

    while (true) {
        std::cout << std::endl << "Wybierz operacje:" << std::endl;
        std::cout << "1. Dodaj na koncu." << std::endl;
        std::cout << "2. Dodaj na poczatku." << std::endl;
        std::cout << "3. Dodaj na indeksie." << std::endl;
        std::cout << "4. Usun z konca." << std::endl;
        std::cout << "5. Usun z poczatku." << std::endl;
        std::cout << "6. Usun z indeksu." << std::endl;
        std::cout << "7. Wyczysc strukture." << std::endl;
        std::cout << "8. Znajdz element." << std::endl;
        std::cout << "9. Wyswietl dane." << std::endl;
        std::cout << "10. Zapisz strukture do pliku." << std::endl;
        std::cout << "11. Wczytaj strukture z pliku." << std::endl;
        std::cout << "12. Wygeneruj losowe dane. " << std::endl;
        std::cout << "13. Powrot do menu glownego." << std::endl;
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
                dataStructure.reset();
                std::cout << "Struktura wyczyszczona!";
                break;
            case 8: {
                std::cout << "Podaj element do znalezienia: ";
                std::cin >> element;
                int indexOfElement = dataStructure.findElement(element);
                if (indexOfElement != -1) {
                    std::cout << "Indeks pierwszego wystapienia elementu: " <<  indexOfElement << std::endl;
                } else {
                    std::cout << "Nie znaleziono elementu." << std::endl;
                }
                break;
            }
            case 9:
                std::cout << std::endl << "Wyswietlanie danych:" << std::endl;
                dataStructure.display();
                break;
            case 10:{
                std::ofstream output;
                std::string fileName;
                std::cout << "Podaj nazwe pliku w ktorym chcesz zapisac strukture: ";
                std::cin >> fileName;
                output.open("saved/" + fileName + ".txt");
                for(int i = 0; i < dataStructure.getSize(); i++)  {
                    output << dataStructure.getElement(i) << std::endl;
                }
                output.close();
                break;
            }
            case 11: {
                std::ifstream input;
                std::string fileName;
                while(!input.is_open()) {
                    std::cout << "Podaj nazwe pliku ktory chcesz wczytac: ";
                    std::cin >> fileName;
                    input.open("saved/" + fileName + ".txt");
                    if (!input.is_open()) std::cout << "Nie udalo sie otworzyc pliku!" << std::endl;
                }
                std::string line;
                while (std::getline(input, line)) {
                    dataStructure.addLast(std::stoi(line));
                }
                break;
            }
            case 12: {
                int seed = rand();
                int numberOfData;
                std::cout << "Podaj ile danych chcesz wygenerowac: ";
                std::cin >> numberOfData;
                generateRandomData(dataStructure, numberOfData, seed);
                break;
            }
            case 13:
                return;
            default:
                std::cout << "Niepoprawny wybor operacji." << std::endl;
                break;
        }
    }
}

int main() {
    srand((unsigned)time(NULL)); 
    // Menu wyboru struktury
    while (true) {
        int structureMenu;
        std::cout << std::endl << "Wybierz strukture danych:" << std::endl;
        std::cout << "1. ArrayList" << std::endl;
        std::cout << "2. Singly Linked List" << std::endl;
        std::cout << "3. Singly Linked List (tail)" << std::endl;
        std::cout << "4. Doubly Linked List" << std::endl;
        std::cout << "5. Wykonaj pomiary dla wszystkich struktur i zapisz wyniki do plikow." << std::endl;
        std::cout << "6. Wyjscie" << std::endl;
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
            case 5: { 
                ArrayList arrayList;
                SinglyLinkedList singlyLinkedList;
                SinglyLinkedListTail singlyLinkedListTail;
                DoublyLinkedList doublyLinkedList;
                int numberOfIterations;
                std::cout << "Ile chcesz wykonac iteracji pomiaru kazdej wielkosci? ";
                std::cin >> numberOfIterations;
                uint32_t seed[numberOfIterations]; // Tablica losowo generowanych seedow - potrzebna do tego, by kazda z operacji byla mierzona na tym samym zestawie danych
                for (int i = 0; i < numberOfIterations; i++) {
                    seed[i] = rand();
                }
                measureAndSave(arrayList, ADD_FIRST, seed, dataSetsSize, numberOfIterations, "ArrayList_AddFirst.txt");
                measureAndSave(arrayList, ADD_LAST, seed, dataSetsSize, numberOfIterations, "ArrayList_AddLast.txt");
                measureAndSave(arrayList, ADD_AT, seed, dataSetsSize, numberOfIterations, "ArrayList_AddAt.txt");
                measureAndSave(arrayList, REMOVE_FIRST, seed, dataSetsSize, numberOfIterations, "ArrayList_RemoveFirst.txt");
                measureAndSave(arrayList, REMOVE_FROM, seed, dataSetsSize, numberOfIterations, "ArrayList_RemoveFrom.txt");
                measureAndSave(arrayList, REMOVE_LAST, seed, dataSetsSize, numberOfIterations, "ArrayList_RemoveLast.txt");
                measureAndSave(arrayList, FIND_ELEMENT, seed, dataSetsSize, numberOfIterations, "ArrayList_Find");

                measureAndSave(singlyLinkedList, ADD_FIRST, seed, dataSetsSize, numberOfIterations, "SinglyLinkedList_AddFirst.txt");
                measureAndSave(singlyLinkedList, ADD_LAST, seed, dataSetsSize, numberOfIterations, "SinglyLinkedList_AddLast.txt");
                measureAndSave(singlyLinkedList, ADD_AT, seed, dataSetsSize, numberOfIterations, "SinglyLinkedList_AddAt.txt");
                measureAndSave(singlyLinkedList, REMOVE_FIRST, seed, dataSetsSize, numberOfIterations, "SinglyLinkedList_RemoveFirst.txt");
                measureAndSave(singlyLinkedList, REMOVE_FROM, seed, dataSetsSize, numberOfIterations, "SinglyLinkedList_RemoveFrom.txt");
                measureAndSave(singlyLinkedList, REMOVE_LAST, seed, dataSetsSize, numberOfIterations, "SinglyLinkedList_RemoveLast.txt");
                measureAndSave(singlyLinkedList, FIND_ELEMENT, seed, dataSetsSize, numberOfIterations, "SinglyLinkedList_Find.txt");

                measureAndSave(singlyLinkedListTail, ADD_FIRST, seed, dataSetsSize, numberOfIterations, "SinglyLinkedListTail_AddFirst.txt");
                measureAndSave(singlyLinkedListTail, ADD_LAST, seed, dataSetsSize, numberOfIterations, "SinglyLinkedListTail_AddLast.txt");
                measureAndSave(singlyLinkedListTail, ADD_AT, seed, dataSetsSize, numberOfIterations, "SinglyLinkedListTail_AddAt.txt");
                measureAndSave(singlyLinkedListTail, REMOVE_FIRST, seed, dataSetsSize, numberOfIterations, "SinglyLinkedListTail_RemoveFirst.txt");
                measureAndSave(singlyLinkedListTail, REMOVE_FROM, seed, dataSetsSize, numberOfIterations, "SinglyLinkedListTail_RemoveFrom.txt");
                measureAndSave(singlyLinkedListTail, REMOVE_LAST, seed, dataSetsSize, numberOfIterations, "SinglyLinkedListTail_RemoveLast.txt");
                measureAndSave(singlyLinkedListTail, FIND_ELEMENT, seed, dataSetsSize, numberOfIterations, "SinglyLinkedListTail_Find.txt");

                measureAndSave(doublyLinkedList, ADD_FIRST, seed, dataSetsSize, numberOfIterations, "DoublyLinkedList_AddFirst.txt");
                measureAndSave(doublyLinkedList, ADD_LAST, seed, dataSetsSize, numberOfIterations, "DoublyLinkedList_AddLast.txt");
                measureAndSave(doublyLinkedList, ADD_AT, seed, dataSetsSize, numberOfIterations, "DoublyLinkedList_AddAt.txt");
                measureAndSave(doublyLinkedList, REMOVE_FIRST, seed, dataSetsSize, numberOfIterations, "DoublyLinkedList_RemoveFirst.txt");
                measureAndSave(doublyLinkedList, REMOVE_FROM, seed, dataSetsSize, numberOfIterations, "DoublyLinkedList_RemoveFrom.txt");
                measureAndSave(doublyLinkedList, REMOVE_LAST, seed, dataSetsSize, numberOfIterations, "DoublyLinkedList_RemoveLast.txt");
                measureAndSave(doublyLinkedList, FIND_ELEMENT, seed, dataSetsSize, numberOfIterations, "DoublyLinkedList_Find.txt");
                
                std::cout << std::endl << "Pomiary zostaly wykonane i zapisane w pliku!";
                break;
            }
            case 6:
                return 0; // Wyjscie z programu
            default:
                std::cout << "Niepoprawny wybor struktury danych." << std::endl;
                break;
        }
    }
}



