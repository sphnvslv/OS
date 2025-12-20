#include "EmployeeRepository.h"
#include <fstream>
#include <algorithm>
#include <iostream>

EmployeeRepository::EmployeeRepository(const std::string& filename)
    : filename(filename) {
    loadFromFile();
}

void EmployeeRepository::loadFromFile() {
    employees.clear();
    std::ifstream file(filename, std::ios::binary);

    if (!file) return;

    char buffer[Employee::getSerializedSize()];
    while (file.read(buffer, Employee::getSerializedSize())) {
        Employee emp;
        emp.deserialize(buffer);
        employees.push_back(emp);
    }

    file.close();
}

void EmployeeRepository::saveToFile() {
    std::ofstream file(filename, std::ios::binary);

    for (const auto& emp : employees) {
        char buffer[Employee::getSerializedSize()];
        emp.serialize(buffer);
        file.write(buffer, Employee::getSerializedSize());
    }

    file.close();
}

void EmployeeRepository::addEmployee(const Employee& employee) {
    employees.push_back(employee);
    saveToFile();
}

Employee* EmployeeRepository::findEmployeeById(int id) {
    for (auto& emp : employees) {
        if (emp.getId() == id) {
            return &emp;
        }
    }
    return nullptr;
}

void EmployeeRepository::updateEmployee(int id, const Employee& updatedEmployee) {
    Employee* emp = findEmployeeById(id);
    if (emp) {
        *emp = updatedEmployee;
        saveToFile();
    }
}

std::vector<Employee> EmployeeRepository::getAllEmployees() const {
    return employees;
}

void EmployeeRepository::displayAll() const {
    std::cout << "\n=== File Contents ===" << std::endl;
    for (const auto& emp : employees) {
        emp.display();
    }
}