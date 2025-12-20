#pragma once
#include <string>

class Client {
private:
    int clientId;

public:
    Client(int id);
    void run();

private:
    void displayMenu();
    void handleRead();
    void handleWrite();
};