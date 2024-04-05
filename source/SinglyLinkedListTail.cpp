#include "SinglyLinkedListTail.hpp"

Node::Node(int element) : element(element), next(nullptr) {}

SinglyLinkedListTail::SinglyLinkedListTail() : head(nullptr), tail(nullptr) {}

SinglyLinkedListTail::~SinglyLinkedListTail() {
    while (head != nullptr) { 
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void SinglyLinkedListTail::addLast(int element) {
    Node* newNode = new Node(element);
    if (head == nullptr) { // Lista jest pusta
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void SinglyLinkedListTail::addFirst(int element) {
    Node* newNode = new Node(element);
    newNode->next = head;
    head = newNode; 
    if (tail == nullptr) {
        tail = newNode; // Jeśli lista była pusta, newNode jest zarówno głową jak i ogonem
    }
}

void SinglyLinkedListTail::addAt(int index, int element) {
    if (index < 0) throw std::out_of_range("Negative index.");
    if (index == 0) addFirst(element);
    Node* newNode = new Node(element);
    Node* currentNode = head;
    int i = 0;
    while (currentNode->next != nullptr && i < index - 1) { // Iteracja az do podanego indeksu
        currentNode = currentNode->next;
        i++;
    }
    if (currentNode == nullptr) throw std::out_of_range("Index out of range.");
    newNode->next = currentNode->next;
    currentNode->next = newNode;
    if (currentNode == nullptr) {
        tail = newNode; // Jeśli dodawany jest na końcu listy, newNode staje się ogonem
    }
}

void SinglyLinkedListTail::removeLast() {
    if (head == nullptr) return; // Lista jest pusta
    if (head->next == nullptr) { // Tylko jeden element w liście
        removeFirst();
        return;
    }
    Node* currentNode = head;
    while (currentNode->next != tail) { // Iteracja do węzła przed ogonem
        currentNode = currentNode->next;
    }
    delete tail;
    tail = currentNode; // Ustawienie ogona na poprzedni węzeł
    tail->next = nullptr; // Nowy ogon ma nullptr jako wskaźnik na następny węzeł
}

void SinglyLinkedListTail::removeFirst() {
    if (head == nullptr) return; // Lista jest pusta
    Node* temp = head;
    head = head->next;
    delete temp;
    if (head == nullptr) {
        tail = nullptr; // Jeśli lista stała się pusta, ogon wskazuje na nullptr
    }
}

void SinglyLinkedListTail::removeFrom(int index) {
    if (index < 0) throw std::out_of_range("Negative index.");
    if (head == nullptr) throw std::out_of_range("List is empty."); // Przypadek kiedy lista jest pusta
    if (index == 0) {
        removeFirst();
        return;
    }
    Node* currentNode = head;
    Node* previousNode = nullptr;
    int i = 0;
    while (currentNode->next != nullptr && i < index) {
        previousNode = currentNode;
        currentNode = currentNode->next;
        i++;
    }
    if (currentNode == nullptr) throw std::out_of_range("Index out of range.");
    previousNode->next = currentNode->next;
    if (currentNode == tail) {
        tail = previousNode; // Jeśli usuwany jest ogon, aktualizacja ogonu na poprzedni węzeł
    }
    delete currentNode;
}

int SinglyLinkedListTail::findElement(int element) {
    Node* currentNode = head;
    int i = 0;
    while (currentNode != nullptr) {
        if (element == currentNode->element) return i;
        currentNode = currentNode->next;
        i++;
    }
    throw std::out_of_range("Element not found.");
}

void SinglyLinkedListTail::display() {
    Node* currentNode = head;
    int i = 0;
    while (currentNode != nullptr) {
        std::cout << i << ": "<< currentNode->element << std::endl;
        currentNode = currentNode->next;
        i++;
    }
}

int SinglyLinkedListTail::getElement(int index) {
    if (index < 0) throw std::out_of_range("Negative index.");
    if (head == nullptr) throw std::out_of_range("List is empty.");
    Node* currentNode = head;
    int i = 0;
    while (currentNode != nullptr && i < index) {    
        currentNode = currentNode->next;
        i++;
    }
    if (currentNode == nullptr) throw std::out_of_range("Element not found.");
    return currentNode->element;
}

int SinglyLinkedListTail::getSize() {
    Node* currentNode = head;
    int i = 0;
    while (currentNode != nullptr) {
        i++;
        currentNode = currentNode->next;
    }
    return i;
}
