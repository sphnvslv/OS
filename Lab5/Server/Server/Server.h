#pragma once
#include <string>

class Server {
private:
    std::string filename;
    int clientCount;

public:
    Server();
    void start();

private:
    void createFile();
    void printFile();
    void runClients();
};