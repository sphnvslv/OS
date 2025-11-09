#pragma once
#include "../Core.h"
using namespace std;

class arr {
public:
    arr();
    ~arr() = default;

    bool InitializeArr(int size);
    bool SetEl(int index, int value, int threadId);
    int GetEl(int index) const;
    void PrintArr() const;
    void ResetElByThread(int threadId);
    int GetSize() const;
    bool IsValidInd(int index) const;

private:
    IntArrayPtr mArr;
    mutable mutex mMutex;
    int mSize;
};

using arrPtr = shared_ptr<arr>;