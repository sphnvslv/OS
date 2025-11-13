#include <iostream>
#include <cassert>
#include "../arr/arr.h"
using namespace std;

void testThreadConcurrAccess();
void testThreadBlock();
void testThreadSafety();

void testInitArr() {
    cout << "Testing InitializeArr" << endl;

    arr arrManager;

    assert(arrManager.InitializeArr(10) == true);
    assert(arrManager.InitializeArr(0) == false);
    assert(arrManager.InitializeArr(-5) == false);

    cout << "InitializeArr tests passed" << endl;
}

void testSetEl() {
    cout << "Testing SetEl" << endl;

    arr arrManager;
    arrManager.InitializeArr(5);

    assert(arrManager.SetEl(0, 1, 1) == true);
    assert(arrManager.SetEl(1, 2, 1) == true);
    assert(arrManager.SetEl(0, 3, 1) == false);
    assert(arrManager.SetEl(10, 3, 1) == false);
    assert(arrManager.SetEl(-1, 3, 1) == false);

    cout << "SetEl tests passed" << endl;
}

void testGetEl() {
    cout << "Testing GetEl" << endl;

    arr arrManager;
    arrManager.InitializeArr(3);
    arrManager.SetEl(1, 5, 1);

    assert(arrManager.GetEl(1) == 5);
    assert(arrManager.GetEl(0) == 0);
    assert(arrManager.GetEl(10) == -1);

    cout << "GetEl tests passed" << endl;
}

void testResetElsByThread() {
    cout << "Testing ResetElByThread" << endl;

    arr arrManager;
    arrManager.InitializeArr(5);

    arrManager.SetEl(0, 1, 1);
    arrManager.SetEl(1, 1, 1);
    arrManager.SetEl(2, 2, 2);
    arrManager.ResetElByThread(1);

    assert(arrManager.GetEl(0) == 0);
    assert(arrManager.GetEl(1) == 0);
    assert(arrManager.GetEl(2) == 2);

    cout << "ResetElByThread tests passed" << endl;
}

void testGetSize() {
    cout << "Testing GetSize" << endl;

    arr arrManager;
    arrManager.InitializeArr(7);
    assert(arrManager.GetSize() == 7);

    cout << "GetSize tests passed" << endl;
}

void testIsValidInd() {
    cout << "Testing IsValidInd" << endl;

    arr arrManager;
    arrManager.InitializeArr(3);

    assert(arrManager.IsValidInd(0) == true);
    assert(arrManager.IsValidInd(2) == true);
    assert(arrManager.IsValidInd(-1) == false);
    assert(arrManager.IsValidInd(3) == false);

    cout << "IsValidInd tests passed" << endl;
}

void runAllThreadTests() {
    cout << "\nStarting thread tests..." << endl;

    testThreadConcurrAccess();
    testThreadBlock();
    testThreadSafety();

    cout << "All thread tests passed" << endl;
}

int main() {
    cout << "Starting array manager tests\n" << endl;

    testInitArr();
    testSetEl();
    testGetEl();
    testResetElsByThread();
    testGetSize();
    testIsValidInd();

    runAllThreadTests();

    cout << "\nAll tests passed successfully!" << endl;
    return 0;
}