#include "Logger.h"
#include <iostream>
#include <ctime>
using namespace std; // Студенческая работа

void Logger::info(const string& message) {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    cout << "[" << buf << "] INFO: " << message << endl;
}

void Logger::error(const string& message) {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    cerr << "[" << buf << "] ERROR: " << message << endl;
}

void Logger::debug(const string& message) {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    cout << "[" << buf << "] DEBUG: " << message << endl;
}