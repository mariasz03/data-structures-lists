#include "..\headers\DoublyLinkedList.hpp"

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
    while (head != nullptr) { 
        DoubleNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void DoublyLinkedList::addLast(int element) {
    DoubleNode* newNode = new DoubleNode(element);
    if (head == nullptr) { // Lista jest pusta
        head = newNode; // Ustawia jako head i tail dodany element
        tail = newNode;
    } else {
        tail->next = newNode; // Wstawia nowy element za tail
        newNode->previous = tail; // Ustawia wskaznik previous nowego elementu na element poprzedni (poprzedni tail)
        tail = newNode; // Ustawia dodany element jako tail
    }
}

void DoublyLinkedList::addFirst(int element) {
    DoubleNode* newNode = new DoubleNode(element);
    newNode->next = head;
    if (head != nullptr) {
        head->previous = newNode; // Jeżeli istnieje head (pierwszy element) to ustaw jego wskaznik previous na dodany element
    } else {
        tail = newNode; // Jeżeli head nie istnieje (pusta lista) ustaw jako tail nowy element
    }
    head = newNode; // Ustaw head tak, zeby wskazywalo na dodany element
}

void DoublyLinkedList::addAt(int index, int element) {
    if (index < 0) throw std::out_of_range("Negative index.");
    if (index == 0) addFirst(element);
    DoubleNode* newNode = new DoubleNode(element);
    DoubleNode* currentNode = head;
    int i = 0;
    while (currentNode != nullptr && i < index) { // Iteracja do podanego indeksu
        currentNode = currentNode->next;
        i++;
    }
    if (currentNode == nullptr) throw std::out_of_range("Index out of range."); // Jezeli przeiterowano przez cala liste i nie dotarlo do indexu, error
    newNode->next = currentNode;
    newNode->previous = currentNode->previous;
    if (currentNode->previous != nullptr) {
        currentNode->previous->next = newNode;
    } else {
        head = newNode; // Aktualizacja head, jeśli wstawiany jest na początku
    }
    currentNode->previous = newNode;
}

void DoublyLinkedList::removeLast() {
    if (head == nullptr) return; // Lista jest pusta
    if (head->next == nullptr) { // Tylko jeden element w liście
        removeFirst();
        return;
    }
    DoubleNode* temp = tail;
    tail = tail->previous;
    tail->next = nullptr;
    delete temp;// Nowy ogon ma nullptr jako wskaźnik na następny węzeł
}

void DoublyLinkedList::removeFirst() {
    if (head == nullptr) return; // Lista jest pusta
    DoubleNode* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->previous = nullptr;
    } else {
        tail = nullptr; // Lista jest teraz pusta
    }
    delete temp;
}

void DoublyLinkedList::removeFrom(int index) {
    if (index < 0) throw std::out_of_range("Negative index.");
    if (head == nullptr) throw std::out_of_range("List is empty.");
    if (index == 0) {
        removeFirst();
        return;
    }
    DoubleNode* currentNode = head;
    int i = 0;
    while (currentNode != nullptr && i < index) {
        currentNode = currentNode->next;
        i++;
    }
    if (currentNode == nullptr) throw std::out_of_range("Index out of range.");
    if (currentNode == tail) {
        removeLast();
        return;
    }
    currentNode->previous->next = currentNode->next;
    currentNode->next->previous = currentNode->previous;
    delete currentNode;
}

int DoublyLinkedList::findElement(int element) {
    DoubleNode* currentNode = head;
    int i = 0;
    while (currentNode != nullptr) {
        if (element == currentNode->element) return i;
        currentNode = currentNode->next;
        i++;
    }
    return -1;
}

void DoublyLinkedList::display() {
    DoubleNode* currentNode = head;
    int i = 0;
    while (currentNode != nullptr) {
        std::cout << i << ": "<< currentNode->element << std::endl;
        currentNode = currentNode->next;
        i++;
    }
}

int DoublyLinkedList::getElement(int index) {
    if (index < 0) throw std::out_of_range("Negative index.");
    if (head == nullptr) throw std::out_of_range("List is empty.");
    DoubleNode* currentNode = head;
    int i = 0;
    while (currentNode != nullptr && i < index) {    
        currentNode = currentNode->next;
        i++;
    }
    if (currentNode == nullptr) throw std::out_of_range("Element not found.");
    return currentNode->element;
}

int DoublyLinkedList::getSize() {
    DoubleNode* currentNode = head;
    int i = 0;
    while (currentNode != nullptr) {
        i++;
        currentNode = currentNode->next;
    }
    return i;
}
