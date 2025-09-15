#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "employee.h"
#include "report_header.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 4) {
        cerr << "Usage: Reporter <input_file> <report_file> <hourly_rate>" << endl;
        return 1;
    }

    string inputFilename = argv[1];
    string outputFilename = argv[2];
    double hourlyRate = stod(argv[3]);

    ifstream inputFile(inputFilename, ios::binary);
    if (!inputFile) {
        cerr << "Error opening input file: " << inputFilename << endl;
        return 1;
    }

    ofstream outputFile(outputFilename);
    if (!outputFile) {
        cerr << "Error creating output file: " << outputFilename << endl;
        inputFile.close();
        return 1;
    }
    printReportHeader(outputFile, inputFilename);

    employee emp;
    while (inputFile.read((char*)&emp, sizeof(employee)))
    {
        double salary = emp.hours * hourlyRate;
        outputFile << emp.num << "\t"
            << emp.name << "\t\t"
            << fixed << setprecision(2) << emp.hours << "\t"
            << fixed << setprecision(2) << salary << endl;
    }

    inputFile.close();
    outputFile.close();

    cout << "Report " << outputFilename << " created." << endl;
    cout << endl;
    return 0;
}