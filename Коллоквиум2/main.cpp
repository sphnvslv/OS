#include "crow_all.h"
#include "Database.h"
#include <sstream>
#include <iostream>
using namespace std; // Студенческая работа

void log(const string& msg) {
    cout << "[LOG] " << msg << endl;
}

int main() {
    Database db;
    if (!db.open()) { log("DB error"); return 1; }

    crow::SimpleApp app;

    CROW_ROUTE(app, "/tasks").methods("GET"_method)([&db] {
        log("GET /tasks");
        auto tasks = db.getAllTasks();
        stringstream json; json << "[";
        for (size_t i = 0; i < tasks.size(); i++) {
            if (i > 0) json << ",";
            json << "{\"id\":" << tasks[i].id << ",\"title\":\"" << tasks[i].title
                << "\",\"description\":\"" << tasks[i].description << "\",\"status\":\""
                << tasks[i].status << "\"}";
        }
        json << "]";
        auto res = crow::response(json.str());
        res.add_header("Content-Type", "application/json");
        return res;
        });

    CROW_ROUTE(app, "/tasks/<int>").methods("GET"_method)([&db](int id) {
        log("GET /tasks/" + to_string(id));
        Task task = db.getTask(id);
        if (task.id == 0) return crow::response(404, "{\"error\":\"Not found\"}");

        stringstream json;
        json << "{\"id\":" << task.id << ",\"title\":\"" << task.title
            << "\",\"description\":\"" << task.description << "\",\"status\":\""
            << task.status << "\"}";

        auto res = crow::response(json.str());
        res.add_header("Content-Type", "application/json");
        return res;
        });

    CROW_ROUTE(app, "/tasks").methods("POST"_method)([&db](const crow::request& req) {
        log("POST /tasks");
        auto json = crow::json::load(req.body);
        if (!json || !json.has("title")) return crow::response(400, "{\"error\":\"Title required\"}");

        string title = json["title"].s();
        string desc = json.has("description") ? json["description"].s() : "";
        string status = json.has("status") ? json["status"].s() : "todo";

        int id = db.createTask(title, desc, status);
        if (id <= 0) return crow::response(500, "{\"error\":\"DB error\"}");

        auto res = crow::response(201, "{\"id\":" + to_string(id) + "}");
        res.add_header("Content-Type", "application/json");
        res.add_header("Location", "/tasks/" + to_string(id));
        return res;
        });

    CROW_ROUTE(app, "/tasks/<int>").methods("PUT"_method)([&db](const crow::request& req, int id) {
        log("PUT /tasks/" + to_string(id));
        auto json = crow::json::load(req.body);
        if (!json || !json.has("title")) return crow::response(400, "{\"error\":\"Title required\"}");

        if (!db.updateTask(id, json["title"].s(),
            json.has("description") ? json["description"].s() : "",
            json.has("status") ? json["status"].s() : "todo")) {
            return crow::response(404, "{\"error\":\"Not found\"}");
        }
        return crow::response(200, "{\"message\":\"OK\"}");
        });

    CROW_ROUTE(app, "/tasks/<int>").methods("DELETE"_method)([&db](int id) {
        log("DELETE /tasks/" + to_string(id));
        if (!db.deleteTask(id)) return crow::response(404, "{\"error\":\"Not found\"}");
        return crow::response(200, "{\"message\":\"OK\"}");
        });

    log("Server on 8080");
    app.port(8080).multithreaded().run();
    return 0;
}