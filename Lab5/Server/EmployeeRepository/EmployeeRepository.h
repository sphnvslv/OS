#pragma once
#include <string>
#include <vector>
#include "Employee.h"

class EmployeeRepository {
private:
    std::string filename;
    std::vector<Employee> employees;

public:
    EmployeeRepository(const std::string& filename);

    void loadFromFile();
    void saveToFile();

    void addEmployee(const Employee& employee);
    Employee* findEmployeeById(int id);
    void updateEmployee(int id, const Employee& updatedEmployee);

    std::vector<Employee> getAllEmployees() const;
    void displayAll() const;
};