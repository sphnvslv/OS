#include "receiver.h"
#include <iostream>

using namespace std;

int main() {
    cout << "IPC Message System - Receiver" << endl;

    Receiver receiver;
    receiver.run();

    return 0;
}