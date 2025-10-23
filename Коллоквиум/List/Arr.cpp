#include "Arr.h"

Arr::Arr(int size) : size_(size) {
    if (size > 0) {
        data_ = new int[size];
    }
    else {
        data_ = nullptr;
    }
}

Arr::~Arr() {
    delete[] data_;
}

int Arr::operator[](int index) const {
    return data_[index];
}

int Arr::size() const {
    return size_;
}

Arr Arr::removeDuplicates(const int* input, int inputSize) {
    if (inputSize <= 0) return Arr(0);

    int* temp = new int[inputSize];
    int uniqueCount = 0;

    for (int i = 0; i < inputSize; ++i) {
        bool found = false;
        for (int j = 0; j < uniqueCount; ++j) {
            if (temp[j] == input[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            temp[uniqueCount++] = input[i];
        }
    }

    Arr result(uniqueCount);
    for (int i = 0; i < uniqueCount; ++i) {
        result.data_[i] = temp[i];
    }

    delete[] temp;
    return result;
}