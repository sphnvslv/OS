#pragma once
#include <string>
#include <cstring>

class Employee {
private:
    int id;
    char name[10];
    double hours;

public:
    Employee(int id = 0, const std::string& name = "", double hours = 0.0);

    int getId() const;
    std::string getName() const;
    double getHours() const;

    void setName(const std::string& name);
    void setHours(double hours);

    void serialize(char* buffer) const;
    void deserialize(const char* buffer);

    static size_t getSerializedSize();
    void display() const;
};