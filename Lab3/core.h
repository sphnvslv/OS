#pragma once

#include <vector>
#include <memory>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <iostream>
#include <random>
#include <string>

using namespace std;

constexpr int MARKER_SLEEP_MS = 5;

using IntArray = vector<int>;
using IntArrayPtr = shared_ptr<IntArray>;

enum class ThreadSignal {
    START,
    CONTINUE,
    TERMINATE
};

inline void SleepFor(int millisec) {
    this_thread::sleep_for(chrono::milliseconds(millisec));
}

inline void PrintMess(const string& mess) {
    cout << mess << endl;
}

inline void PrintError(const string& error) {
    cerr << "ERROR: " << error << endl;
}

inline int GetValidatedInput(const string& prompt, int minValue = 1) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < minValue) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Wrong input. Please enter a number >= " << minValue << endl;
        }
        else {
            break;
        }
    }
    return value;
}