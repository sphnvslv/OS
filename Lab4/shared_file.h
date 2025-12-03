#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "message.h"

using namespace std;

class SharedFile {
private:
    string filename;
    int capacity;
    fstream file;

public:
    SharedFile(string name, int cap, bool createNew) {
        filename = name;
        capacity = cap;

        if (createNew) {
            createFile();
        }
        else {
            openFile();
        }
    }

    bool write(Message msg) {
        file.seekp(0, ios::end);
        file.write((char*)&msg, sizeof(Message));
        file.flush();
        return true;
    }

    bool read(Message& msg) {
        file.seekg(0, ios::beg);
        file.read((char*)&msg, sizeof(Message));
        return !file.eof();
    }

    int getMessageCount() {
        file.seekg(0, ios::end);
        int size = file.tellg();
        return size / sizeof(Message);
    }

    bool isFull() {
        return getMessageCount() >= capacity;
    }

    bool isEmpty() {
        return getMessageCount() == 0;
    }

private:
    void createFile() {
        file.open(filename, ios::out | ios::binary | ios::trunc);
        if (!file) {
            throw runtime_error("Cannot create file: " + filename);
        }
        cout << "File created: " << filename << endl;
        file.close();
        file.open(filename, ios::in | ios::out | ios::binary);
    }

    void openFile() {
        file.open(filename, ios::in | ios::out | ios::binary);
        if (!file) {
            throw runtime_error("Cannot open file: " + filename);
        }
        cout << "File opened: " << filename << endl;
    }
};