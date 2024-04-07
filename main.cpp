
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
#include "source/generate_random_data.cpp"



int main() {
    std::ofstream outputTime("measured_times/output.txt");

    ArrayList arrayList;
    SinglyLinkedList list;
    int dataSetsSize[8] = {5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000};
    generateRandomData(arrayList, dataSetsSize[1]);
    uint32_t randNum = generateRandomNumber();
    TimerClock timer;
    list.addLast(randNum);
    double elapsed = timer.elapsed();
    arrayList.removeLast();
    std::cout << "Time: " << elapsed << "[ns]" << std::endl;
    

    return 0;
}