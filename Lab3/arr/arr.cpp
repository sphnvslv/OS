#include "arr.h"
using namespace std;

arr::arr() : mSize(0) {
    mArr = make_shared<IntArray>();
}

bool arr::InitializeArr(int size) {
    if (size <= 0) {
        PrintError("Wrong array size: " + to_string(size));
        return false;
    }

    lock_guard<mutex> lock(mMutex);
    mArr->resize(size, 0);
    mSize = size;

    return true;
}

bool arr::SetEl(int ind, int value, int threadId) {
    if (!IsValidInd(ind)) {
        return false;
    }

    lock_guard<mutex> lock(mMutex);

    if ((*mArr)[ind] == 0) {
        SleepFor(MARKER_SLEEP_MS);
        (*mArr)[ind] = value;
        SleepFor(MARKER_SLEEP_MS);
        return true;
    }

    return false;
}

int arr::GetEl(int index) const {
    if (!IsValidInd(index)) {
        return -1;
    }

    lock_guard<mutex> lock(mMutex);
    return (*mArr)[index];
}

void arr::PrintArr() const {
    lock_guard<mutex> lock(mMutex);

    cout << "Array contents: [";
    for (int i = 0; i < mSize; ++i) {
        cout << (*mArr)[i];
        if (i < mSize - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

void arr::ResetElByThread(int threadId) {
    lock_guard<mutex> lock(mMutex);

    int resetCount = 0;
    for (int i = 0; i < mSize; ++i) {
        if ((*mArr)[i] == threadId) {
            (*mArr)[i] = 0;
            resetCount++;
        }
    }

    PrintMess("Reset " + to_string(resetCount) +
        " elements for thread " + to_string(threadId));
}

int arr::GetSize() const {
    return mSize;
}

bool arr::IsValidInd(int ind) const {
    return ind >= 0 && ind < mSize;
}