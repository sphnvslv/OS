#include <iostream>
#include <fstream>
#include <cstdio>
#include "../core/employee.h"

using namespace std;

int main() {
    cout << "=== Testing Creator ===" << endl;

    // Тест 1: Создание файла
    string filename = "test_creator.bin";

    // Имитируем работу Creator
    ofstream file(filename, ios::binary);
    if (!file) {
        cout << "FAIL: Cannot create file " << filename << endl;
        return 1;
    }

    employee test_emp = { 123, "TestUser", 40.5 };
    file.write((char*)&test_emp, sizeof(employee));
    file.close();

    cout << "PASS: File created successfully" << endl;

    // Тест 2: Чтение файла
    ifstream read_file(filename, ios::binary);
    if (!read_file) {
        cout << "FAIL: Cannot read created file" << endl;
        return 1;
    }

    employee read_emp;
    read_file.read((char*)&read_emp, sizeof(employee));

    if (read_emp.num == 123 && read_emp.hours == 40.5) {
        cout << "PASS: Data written and read correctly" << endl;
    }
    else {
        cout << "FAIL: Data corruption" << endl;
    }

    read_file.close();

    // Убираем за собой
    remove(filename.c_str());
    cout << "=== Creator tests completed ===" << endl << endl;

    return 0;
}