#include "Database.h"
#include <sqlite3.h>
#include <iostream>
using namespace std; // Студенческая работа

Database::Database() : db(nullptr) {}
Database::~Database() { if (db) sqlite3_close((sqlite3*)db); }

bool Database::open() {
    if (sqlite3_open("todo.db", (sqlite3**)&db)) return false;
    const char* sql = "CREATE TABLE IF NOT EXISTS tasks ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, title TEXT NOT NULL, "
        "description TEXT, status TEXT DEFAULT 'todo');";
    char* err = nullptr;
    if (sqlite3_exec((sqlite3*)db, sql, nullptr, nullptr, &err) != SQLITE_OK) {
        cerr << "SQL: " << err << endl; sqlite3_free(err); return false;
    }
    cout << "DB opened" << endl; return true;
}

int Database::createTask(const string& title, const string& desc,
    const string& status) {
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2((sqlite3*)db, "INSERT INTO tasks (title,description,status) VALUES(?,?,?)", -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, desc.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, status.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE) { sqlite3_finalize(stmt); return -1; }
    int id = sqlite3_last_insert_rowid((sqlite3*)db);
    sqlite3_finalize(stmt); cout << "Created ID=" << id << endl; return id;
}

vector<Task> Database::getAllTasks() {
    vector<Task> tasks;
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2((sqlite3*)db, "SELECT id,title,description,status FROM tasks", -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        tasks.push_back({ sqlite3_column_int(stmt,0),
                        (const char*)sqlite3_column_text(stmt,1),
                        (const char*)sqlite3_column_text(stmt,2),
                        (const char*)sqlite3_column_text(stmt,3) });
    }
    sqlite3_finalize(stmt);
    cout << "Fetched " << tasks.size() << " tasks" << endl;
    return tasks;
}

Task Database::getTask(int id) {
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2((sqlite3*)db, "SELECT id,title,description,status FROM tasks WHERE id=?", -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    Task task;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        task = { sqlite3_column_int(stmt,0),
               (const char*)sqlite3_column_text(stmt,1),
               (const char*)sqlite3_column_text(stmt,2),
               (const char*)sqlite3_column_text(stmt,3) };
    }
    sqlite3_finalize(stmt); return task;
}

bool Database::updateTask(int id, const string& title,
    const string& desc, const string& status) {
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2((sqlite3*)db, "UPDATE tasks SET title=?,description=?,status=? WHERE id=?", -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, desc.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, status.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, id);
    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    if (ok) cout << "Updated ID=" << id << endl;
    return ok;
}

bool Database::deleteTask(int id) {
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2((sqlite3*)db, "DELETE FROM tasks WHERE id=?", -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);
    bool ok = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    if (ok) cout << "Deleted ID=" << id << endl;
    return ok;
}