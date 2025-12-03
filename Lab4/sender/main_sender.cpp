#include "sender.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: sender.exe <filename>" << endl;
        return 1;
    }

    static int counter = 0;
    counter++;

    Sender sender(argv[1], counter);
    sender.run();

    return 0;
}