#include "..\headers\ArrayList.hpp"
#include "..\headers\SinglyLinkedList.hpp"
#include "..\headers\SinglyLinkedListTail.hpp"
#include "..\headers\DoublyLinkedList.hpp"
#include <cstdint>
#include <random>

uint32_t generateRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<uint32_t> dis(0, std::numeric_limits<uint32_t>::max()); 

    return dis(gen);
}

template<typename T>
void generateRandomData(T &container, int dataSetSize) {
    for (int i = 0; i < dataSetSize; i++) {
            container.addLast(generateRandomNumber()); 
    }
}