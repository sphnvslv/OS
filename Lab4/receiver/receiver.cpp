#include "receiver.h"
#include <iostream>
#include <cstdlib>
#include <thread>

using namespace std;

void Receiver::run() {
    cout << "=== RECEIVER ===" << endl;
    setup();
    startSenders();
    processCommands();
}

void Receiver::setup() {
    cout << "Enter filename: ";
    getline(cin, filename);

    cout << "Enter buffer capacity: ";
    cin >> capacity;
    cin.ignore();

    cout << "Enter number of senders: ";
    cin >> senderCount;
    cin.ignore();

    file = new SharedFile(filename, capacity, true);
}

void Receiver::startSenders() {
    cout << "\nStarting " << senderCount << " senders..." << endl;

    for (int i = 0; i < senderCount; i++) {
        string cmd = "start cmd /c sender.exe " + filename;
        system(cmd.c_str());
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    cout << "All senders started. Waiting for ready signals..." << endl;

    // ∆дем готовности всех сендеров
    for (int i = 0; i < senderCount; i++) {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Sender " << (i + 1) << " ready" << endl;
    }

    cout << "\nReady to receive messages!" << endl;
}

void Receiver::processCommands() {
    char choice;

    do {
        showMenu();
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case '1':
            readMessage();
            break;
        case '2':
            cout << "Messages in buffer: "
                << file->getMessageCount() << endl;
            break;
        case '3':
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != '3');
}

void Receiver::readMessage() {
    if (file->isEmpty()) {
        cout << "Buffer is empty. Waiting for messages..." << endl;

        // ∆дем по€влени€ сообщений
        while (file->isEmpty()) {
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }

    Message msg;
    if (file->read(msg)) {
        cout << "Received: [" << msg.senderId << "] "
            << msg.getContent() << endl;
    }
    else {
        cout << "Failed to read message" << endl;
    }
}

void Receiver::showMenu() {
    cout << "\n=== MENU ===" << endl;
    cout << "1. Read message" << endl;
    cout << "2. Check message count" << endl;
    cout << "3. Exit" << endl;
    cout << "============" << endl;
}