#ifndef LIST_H
#define LIST_H

class List {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val);
    };

    Node* head;
    Node* reverseRecurs(Node* node);

public:
    List();
    void add(int value);
    void reverse();
    void print();
    ~List();
};

#endif