#include "List.h"
#include <iostream>
using namespace std;

List::Node::Node(int val) : data(val), next(nullptr) {}

List::List() : head(nullptr) {}

List::Node* List::reverseRecurs(Node* node) {
    if (!node || !node->next) return node;
    Node* newHead = reverseRecurs(node->next);
    node->next->next = node;
    node->next = nullptr;
    return newHead;
}

void List::add(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next) current = current->next;
        current->next = newNode;
    }
}

void List::reverse() {
    head = reverseRecurs(head);
}

void List::print() {
    Node* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

List::~List() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}