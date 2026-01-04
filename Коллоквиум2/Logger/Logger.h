#ifndef LOGGER_H
#define LOGGER_H
#include <string>
using namespace std; // Студенческая работа

class Logger {
public:
    static void info(const string& message);
    static void error(const string& message);
    static void debug(const string& message);
};

#endif