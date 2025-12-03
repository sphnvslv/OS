#pragma once
#include <string>
#include <cstring>
#include <chrono>
#include <sstream>
#include <iomanip>

using namespace std;

class Message {
public:
    static const int MAX_LENGTH = 20;
    char content[MAX_LENGTH + 1];
    int senderId;

    Message() {
        content[0] = '\0';
        senderId = 0;
    }

    Message(string text, int id) {
        setContent(text);
        senderId = id;
    }

    void setContent(string text) {
        if (text.length() > MAX_LENGTH) {
            text = text.substr(0, MAX_LENGTH);
        }
        strcpy(content, text.c_str());
    }

    string getContent() {
        return string(content);
    }

    bool isEmpty() {
        return content[0] == '\0';
    }
};