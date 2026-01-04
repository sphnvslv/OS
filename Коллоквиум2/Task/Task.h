#ifndef TASK_H
#define TASK_H
#include <string>

using namespace std; // Студенческая работа

struct Task {
    int id;
    string title;
    string description;
    string status;
    string created_at;

    Task();
    Task(int id, const string& title, const string& description,
        const string& status, const string& created_at);

    string to_json() const;
};

#endif