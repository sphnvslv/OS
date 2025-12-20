#include "Employee.h"
#include <iostream>

Employee::Employee(int id, const std::string& name, double hours)
    : id(id), hours(hours) {
    strncpy_s(this->name, name.c_str(), 9);
    this->name[9] = '\0';
}

int Employee::getId() const { return id; }
std::string Employee::getName() const { return std::string(name); }
double Employee::getHours() const { return hours; }

void Employee::setName(const std::string& name) {
    strncpy_s(this->name, name.c_str(), 9);
    this->name[9] = '\0';
}

void Employee::setHours(double hours) {
    this->hours = hours;
}

void Employee::serialize(char* buffer) const {
    memcpy(buffer, &id, sizeof(id));
    memcpy(buffer + sizeof(id), name, 10);
    memcpy(buffer + sizeof(id) + 10, &hours, sizeof(hours));
}

void Employee::deserialize(const char* buffer) {
    memcpy(&id, buffer, sizeof(id));
    memcpy(name, buffer + sizeof(id), 10);
    memcpy(&hours, buffer + sizeof(id) + 10, sizeof(hours));
}

size_t Employee::getSerializedSize() {
    return sizeof(id) + 10 + sizeof(hours);
}

void Employee::display() const {
    std::cout << "ID: " << id
        << ", Name: " << name
        << ", Hours: " << hours << std::endl;
}