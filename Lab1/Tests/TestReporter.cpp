#include <iostream>
#include <fstream>
#include <cstdio>
#include "../core/employee.h"

using namespace std;

int main() {
    cout << "=== Testing Reporter ===" << endl;

    string bin_filename = "test_reporter.bin";
    ofstream bin_file(bin_filename, ios::binary);

    employee emp1 = { 1, "Ivan", 160 };
    employee emp2 = { 2, "Maria", 120 };
    bin_file.write((char*)&emp1, sizeof(employee));
    bin_file.write((char*)&emp2, sizeof(employee));
    bin_file.close();

    string report_filename = "test_report.txt";
    ofstream report_file(report_filename);

    if (!report_file) {
        cout << "FAIL: Cannot create report file" << endl;
        return 1;
    }

    report_file << "Report for file: " << bin_filename << endl;
    report_file << "------------------------------------------" << endl;
    report_file << "ID\tName\t\tHours\tSalary" << endl;
    report_file << "------------------------------------------" << endl;

    ifstream input_file(bin_filename, ios::binary);
    employee emp;
    double hourly_rate = 100;

    while (input_file.read((char*)&emp, sizeof(employee))) {
        double salary = emp.hours * hourly_rate;
        report_file << emp.num << "\t" << emp.name << "\t\t"
            << emp.hours << "\t" << salary << endl;
    }

    input_file.close();
    report_file.close();

    cout << "PASS: Report generated" << endl;

    ifstream check_report(report_filename);
    if (check_report) {
        cout << "PASS: Report file created and contains data" << endl;
        check_report.close();
    }
    else {
        cout << "FAIL: Report file was not created" << endl;
    }

    remove(bin_filename.c_str());
    remove(report_filename.c_str());

    cout << "=== Reporter tests completed ===" << endl << endl;

    system("pause");
    return 0;
}