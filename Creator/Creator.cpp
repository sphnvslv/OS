#include <iostream>
#include <fstream>
#include <string>
#include "employee.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3) {
        cerr << "Usage: Creator <filename> <record_count>" << endl;
        return 1;
    }

    string filename = argv[1];
    int recordCount = stoi(argv[2]);

    ofstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error creating file: " << filename << endl;
        return 1;
    }

    cout << "Enter data for " << recordCount << " employees:" << endl;

    for (int i = 0; i < recordCount; i++) {
        employee emp;

        cout << "\nEmployee " << (i + 1) << ":" << endl;
        cout << "ID number: ";
        cin >> emp.num;
        cout << "Name (no more than 10 characters): ";
        cin.ignore();
        cin.getline(emp.name, 10);
        cout << "Worked hours: ";
        cin >> emp.hours;
        cout << endl;

        file.write((char*)&emp, sizeof(employee));
       
    }

    file.close();
    cout << "File " << filename << " created." << endl;
    return 0;
}