#include <iostream>
#include <fstream>
#include <string>
#include "employee.h"

using namespace std;

void printReportHeader(ofstream& outputFile, const string& inputFilename) {
    outputFile << "Report for file: \"" << inputFilename << "\"" << endl;
    outputFile << "------------------------------------------" << endl;
    outputFile << "ID\tName\t\tHours\tSalary" << endl;
    outputFile << "------------------------------------------" << endl;
}

int main(int argc, char* argv[])
{
    if (argc != 4) {
        cerr << "Usage: Reporter <binary_file> <report_file> <hourly_rate>" << endl;
        return 1;
    }

    string binaryFileName = argv[1];
    string reportFileName = argv[2];
    double hourlyRate = stod(argv[3]);

    ifstream inputFile(binaryFileName, ios::binary);
    if (!inputFile) {
        cerr << "Error opening binary file: " << binaryFileName << endl;
        return 1;
    }

    ofstream outputFile(reportFileName);
    if (!outputFile) {
        cerr << "Error creating report file: " << reportFileName << endl;
        return 1;
    }

    printReportHeader(outputFile, binaryFileName);

    employee emp;
    while (inputFile.read((char*)&emp, sizeof(employee))) {
        double salary = emp.hours * hourlyRate;
        outputFile << emp.num << "\t" << emp.name << "\t\t"
            << emp.hours << "\t" << salary << endl;
    }

    inputFile.close();
    outputFile.close();

    cout << "Report file " << reportFileName << " created." << endl;
    return 0;
}