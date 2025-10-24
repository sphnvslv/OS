#include "List.h"
#include <iostream>
using namespace std;

void testEmptyList() {
    cout << "Test 1: Empty list" << endl;
    List list;
    list.print(); 
    cout << "Empty list OK" << endl << endl;
}

void testAddPrint() {
    cout << "Test 2: Add and print" << endl;
    List list;
    list.add(1);
    list.add(2);
    list.add(3);
    cout << "List: ";
    list.print();  
    cout << "Add and print OK" << endl << endl;
}

void testReverse() {
    cout << "Test 3: Reverse" << endl;
    List list;
    list.add(1);
    list.add(2);
    list.add(3);

    cout << "Before: ";
    list.print(); 

    list.reverse();

    cout << "After: ";
    list.print(); 
    cout << "Reverse OK" << endl << endl;
}

void testSingleElement() {
    cout << "Test 4: Single element" << endl;
    List list;
    list.add(17);

    cout << "Before: ";
    list.print();  

    list.reverse();

    cout << "After: ";
    list.print();  
    cout << "Single element OK" << endl << endl;
}

int main() {
    cout << "=== List Tests ===" << endl << endl;

    testEmptyList();
    testAddPrint();
    testReverse();
    testSingleElement();

    cout << "=== All tests completed ===" << endl;
    return 0;
}