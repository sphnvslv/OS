#include "Task.h"
#include <sstream>
using namespace std; // Студенческая работа

Task::Task() : id(0) {}

Task::Task(int id, const string& title, const string& description,
    const string& status, const string& created_at)
    : id(id), title(title), description(description), status(status), created_at(created_at) {}

string Task::to_json() const {
    stringstream json;
    json << "{"
        << "\"id\":" << id << ","
        << "\"title\":\"" << title << "\","
        << "\"description\":\"" << description << "\","
        << "\"status\":\"" << status << "\","
        << "\"created_at\":\"" << created_at << "\""
        << "}";
    return json.str();
}