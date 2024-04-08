#include "..\headers\SinglyLinkedList.hpp"
#include "..\headers\Node.hpp"

SinglyLinkedList::SinglyLinkedList() : head(nullptr) {}

SinglyLinkedList::~SinglyLinkedList() {
    while (head != nullptr) { 
        Node* temp = head; // Wskaznik temp wskazuje na miejsce na ktore wskazywal head
        head = head->next; // head wskazuje teraz na nastepny element
        delete temp; // Zwolnienie pamieci w miejscu na ktorym wskazywal wczesniej head
    }
}

void SinglyLinkedList::addLast(int element) {
    Node* newNode = new Node(element);
    if (head == nullptr) { // Przypadek kiedy lista jest pusta
        head = newNode;
    } else {
        Node* currentNode = head;
        while (currentNode->next != nullptr) { // Dopóki następny węzeł istnieje
            currentNode = currentNode->next; 
        }
        currentNode->next = newNode;
    }
}

void SinglyLinkedList::addFirst(int element) {
    Node* newNode = new Node(element);
    newNode->next = head;
    head = newNode; 
}

void SinglyLinkedList::addAt(int index, int element) {
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
}

void SinglyLinkedList::removeLast() {
    if (head == nullptr) return; // Przypadek kiedy lista jest pusta
    if (head->next == nullptr) { // Przypadek w którym lista ma tylko jeden element
        removeFirst();
        return;
    }
    Node* currentNode = head;
    Node* previousNode = nullptr;
    while (currentNode->next != nullptr) {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
    delete currentNode;
    previousNode->next = nullptr;
}

void SinglyLinkedList::removeFirst() {
    if (head == nullptr) {  // Przypadek kiedy lista jest pusta
        return;
    } else {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }
}

void SinglyLinkedList::removeFrom(int index) {
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
    previousNode->next = currentNode->next;
    if (currentNode == nullptr) throw std::out_of_range("Index out of range.");
    delete currentNode;
}

int SinglyLinkedList::findElement (int element) {
    Node* currentNode = head;
    int i = 0;
    while (currentNode != nullptr) {
        if (element == currentNode->element) return i;
        currentNode = currentNode->next;
        i++;
    }
    return -1;
}

void SinglyLinkedList::display() {
    Node* currentNode = head;
    int i = 0;
    while (currentNode != nullptr) {
        std::cout << i  << ": "<< currentNode->element << std::endl;
        currentNode = currentNode->next;
        i++;
    }
}

void SinglyLinkedList::reset() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int SinglyLinkedList::getElement(int index) {
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

int SinglyLinkedList::getSize() {
    Node* currentNode = head;
    int i = 0;
    while (currentNode != nullptr) {
        i++;
        currentNode = currentNode->next;
    }
    return i;
}