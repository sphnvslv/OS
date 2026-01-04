#ifndef DATABASE_H
#define DATABASE_H
#include <vector>
#include "Task.h"
using namespace std; // Студенческая работа

class Database {
private:
    void* db;

public:
    Database();
    ~Database();

    bool open();
    void close();

    int createTask(const string& title, const string& description,
        const string& status = "todo");
    vector<Task> getAllTasks();
    Task getTask(int id);
    bool updateTask(int id, const string& title,
        const string& description, const string& status);
    bool deleteTask(int id);
};

#endif