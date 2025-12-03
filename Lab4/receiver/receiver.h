#pragma once
#include <string>
#include "shared_file.h"

using namespace std;

class Receiver {
private:
    SharedFile* file;
    string filename;
    int capacity;
    int senderCount;

public:
    void run();

private:
    void setup();
    void startSenders();
    void processCommands();
    void readMessage();
    void showMenu();
};