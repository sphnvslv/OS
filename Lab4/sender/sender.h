#pragma once
#include <string>
#include "shared_file.h"

using namespace std;

class Sender {
private:
    SharedFile* file;
    string filename;
    int id;

public:
    Sender(string name, int senderId);
    void run();

private:
    void processCommands();
    void sendMessage();
    void showMenu();
};