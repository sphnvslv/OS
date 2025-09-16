#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include "../core/employee.h"

using namespace std;

void printBinInfo(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    cout << "\nBinary file data:" << endl;
    cout << "----------------------------" << endl;
    cout << "ID\tName\t\tHours" << endl;
    cout << "----------------------------" << endl;

    employee emp;
    while (file.read((char*)&emp, sizeof(employee))) {
        cout << emp.num << "\t" << emp.name << "\t\t" << emp.hours << endl;
    }
    file.close();
}

void printReport(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening report: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

int main() {
    string binaryFileName;
    int recordCount;
    string reportFileName;
    double hourlyRate;

    cout << "Enter binary file name: ";
    cin >> binaryFileName;
    cout << "Enter number of employees: ";
    cin >> recordCount;

    string command = "Creator\\\\Debug\\\\Creator.exe " + binaryFileName + " " + to_string(recordCount);

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char* commandLine = _strdup(command.c_str());

    if (!CreateProcessA(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cerr << "Error starting Creator" << endl;
        free(commandLine);
        return 1;
    }
    free(commandLine);

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    printBinInfo(binaryFileName);

    cout << "\nEnter report file name: ";
    cin >> reportFileName;
    cout << "Enter hourly rate: ";
    cin >> hourlyRate;
    cout << endl;

    command = "Reporter.exe " + binaryFileName + " " + reportFileName + " " + to_string(hourlyRate);

    commandLine = _strdup(command.c_str());

    if (!CreateProcessA(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cerr << "Error starting Reporter" << endl;
        free(commandLine);
        return 1;
    }
    free(commandLine);

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    printReport(reportFileName);

    return 0;
}