#include "Arr.h"
#include <iostream>
using namespace std;

void testBasic() {

    cout << "Test 1: Duplicate remove" << endl;

    int input[] = { 1, 2, 2, 3, 4, 4, 5 };
    Arr result = Arr::removeDuplicates(input, 7);

    cout << "Result: ";

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << "Remove test OK" << endl << endl;
}

void testEmpty() {

    cout << "Test 2: Empty array" << endl;

    Arr result = Arr::removeDuplicates(nullptr, 0);

    cout << "Size: " << result.size() << endl;
    cout << "Empty test OK" << endl << endl;
}

void testAllDuplicates() {

    cout << "Test 3: All duplicates" << endl;

    int input[] = { 5, 5, 5, 5 };
    Arr result = Arr::removeDuplicates(input, 4);

    cout << "Result: ";

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << "All duplicates test OK" << endl << endl;
}

void testNoDuplicates() {

    cout << "Test 4: No duplicates" << endl;

    int input[] = { 1, 2, 3, 4, 5 };
    Arr result = Arr::removeDuplicates(input, 5);

    cout << "Result: ";

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << "No duplicates test OK" << endl << endl;
}

int main() {
    cout << "=== Array Tests ===" << endl << endl;

    testBasic();
    testEmpty();
    testAllDuplicates();
    testNoDuplicates();

    cout << "=== All tests completed ===" << endl;
    return 0;
}