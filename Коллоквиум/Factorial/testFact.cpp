#include "Fact.h"
#include <iostream>
using namespace std;

void testBasic() {
    cout << "Test 1: Basic factorial calculation" << endl;
    FactRes result = FactCalc::calculateFirstNFactorials(7);

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    cout << "Basic test OK" << endl << endl;
}

void testZero() {
    cout << "Test 2: Zero factorials" << endl;

    FactRes result = FactCalc::calculateFirstNFactorials(0);

    cout << "Size: " << result.size() << endl;
    cout << "Zero test OK" << endl << endl;
}

void testSingle() {
    cout << "Test 3: Single factorial" << endl;

    FactRes result = FactCalc::calculateFirstNFactorials(1);

    cout << "First factorial: " << result[0] << endl;
    cout << "Single test OK" << endl << endl;
}

void testError() {
    cout << "Test 4: Error handling" << endl;

    try {
        FactRes result = FactCalc::calculateFirstNFactorials(-7);
        cout << "Error test FAILED" << endl;
    }
    catch (const exception& e) {

        cout << "Correctly caught error: " << e.what() << endl;
        cout << "Error test OK" << endl;
    }
    cout << endl;
}

int main() {
    cout << "=== Factorial Tests ===" << endl << endl;

    testBasic();
    testZero();
    testSingle();
    testError();

    cout << "=== All tests completed ===" << endl;
    return 0;
}