#include "sender.h"
#include <iostream>
#include <thread>

using namespace std;

Sender::Sender(string name, int senderId) {
    filename = name;
    id = senderId;
    file = new SharedFile(filename, 0, false);
}

void Sender::run() {
    cout << "Sender " << id << " started" << endl;
    cout << "Using file: " << filename << endl;

    this_thread::sleep_for(chrono::seconds(1));
    cout << "Sender " << id << " ready" << endl;

    processCommands();
}

void Sender::processCommands() {
    char choice;

    do {
        showMenu();
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case '1':
            sendMessage();
            break;
        case '2':
            cout << "Sender " << id << " exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != '2');
}

void Sender::sendMessage() {
    string text;
    cout << "Enter message: ";
    getline(cin, text);

    Message msg(text, id);

    if (file->write(msg)) {
        cout << "Message sent: " << text << endl;
    }
    else {
        cout << "Failed to send message" << endl;
    }
}

void Sender::showMenu() {
    cout << "\n=== SENDER " << id << " ===" << endl;
    cout << "1. Send message" << endl;
    cout << "2. Exit" << endl;
    cout << "=================" << endl;
}