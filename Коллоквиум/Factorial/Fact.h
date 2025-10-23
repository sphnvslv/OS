#ifndef FACT_H
#define FACT_H

class FactRes {
private:
    unsigned long long* data_;
    int size_;

public:
    FactRes(int size);
    ~FactRes();

    unsigned long long& operator[](int index);
    int size() const;
};

class FactCalc {
public:
    static FactRes calculateFirstNFactorials(int n);
};

#endif