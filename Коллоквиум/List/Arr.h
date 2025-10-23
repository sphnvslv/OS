#ifndef ARR_H
#define ARR_H

class Arr {
private:
    int* data_;
    int size_;

public:
    Arr(int size = 0);
    ~Arr();

    int operator[](int index) const;
    int size() const;

    static Arr removeDuplicates(const int* input, int inputSize);
};

#endif