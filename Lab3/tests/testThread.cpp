#include <iostream>
#include <cassert>
#include <thread>
#include "../arr/arr.h"

using namespace std;

void testThreadConcurrAccess() {
    cout << "Testing ThreadConcurrentAccess" << endl;

    arr arrayManager;
    arrayManager.InitializeArr(100);

    auto marker_func = [&arrayManager](int threadId) {
        for (int i = 0; i < 50; ++i) {
            int index = rand() % 100;
            arrayManager.SetEl(index, threadId, threadId);
        }
        };

    thread t1(marker_func, 1);
    thread t2(marker_func, 2);
    thread t3(marker_func, 3);

    t1.join();
    t2.join();
    t3.join();

    cout << "ThreadConcurrentAccess test passed" << endl;
}

void testThreadBlock() {
    cout << "Testing ThreadBlock" << endl;

    arr arrayManager;
    arrayManager.InitializeArr(2);

    arrayManager.SetEl(0, 1, 1);
    arrayManager.SetEl(1, 2, 2);

    assert(arrayManager.SetEl(0, 3, 3) == false);
    assert(arrayManager.SetEl(1, 4, 4) == false);

    cout << "ThreadBlock test passed" << endl;
}

void testThreadSafety() {
    cout << "Testing ThreadSafety" << endl;

    arr arrayManager;
    arrayManager.InitializeArr(50);

    auto worker = [&arrayManager](int start, int end, int threadId) {
        for (int i = start; i < end; i++) {
            arrayManager.SetEl(i, threadId, threadId);
        }
        };

    thread t1(worker, 0, 25, 1);
    thread t2(worker, 25, 50, 2);

    t1.join();
    t2.join();

    for (int i = 0; i < 50; i++) {
        int value = arrayManager.GetEl(i);
        assert(value == 1 || value == 2);
    }

    cout << "ThreadSafety test passed" << endl;
}