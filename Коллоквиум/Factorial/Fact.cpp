#include "Fact.h"
#include <stdexcept>
#include <limits>

FactRes::FactRes(int size) : size_(size) {
    if (size > 0) {
        data_ = new unsigned long long[size];
    }
    else {
        data_ = nullptr;
    }
}

FactRes::~FactRes() {
    delete[] data_;
}

unsigned long long& FactRes::operator[](int index) {
    return data_[index];
}

int FactRes::size() const {
    return size_;
}

FactRes FactCalc::calculateFirstNFactorials(int n) {
    if (n < 0) {
        throw std::invalid_argument("Number must be >= 0");
    }

    FactRes result(n);

    unsigned long long factorial = 1;
    result[0] = factorial;

    for (int i = 1; i < n; ++i) {
        if (factorial > std::numeric_limits<unsigned long long>::max() / i) {
            throw std::overflow_error("Overflow");
        }
        factorial *= i;
        result[i] = factorial;
    }

    return result;
}