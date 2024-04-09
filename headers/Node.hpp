#pragma once

class Node {
public:
    int element;
    Node* next;

    Node(int element) : element(element), next(nullptr) {};
};

class DoubleNode { // Node listy dwukierunkowej
    public:
        int element;
        DoubleNode* next;
        DoubleNode* previous;

    DoubleNode(int element) : element(element), next(nullptr), previous(nullptr) {};
};