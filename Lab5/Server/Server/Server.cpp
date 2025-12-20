#include "Server.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <thread>
#include "Employee.h"

struct employee {
    int num;
    char name[10];
    double hours;
};

std::vector<employee> employees;
std::string filename;
int clientCount;

void createFile() {
    std::cout << "Enter filename: ";
    std::cin >> filename;

    std::cout << "How many employees to add? ";
    int n;
    std::cin >> n;

    employees.clear();
    for (int i = 0; i < n; i++) {
        employee emp;
        std::cout << "\nEmployee " << i + 1 << ":\n";
        std::cout << "ID: ";
        std::cin >> emp.num;
        std::cout << "Name (max 9 chars): ";
        std::cin >> emp.name;
        std::cout << "Worked hours: ";
        std::cin >> emp.hours;
        employees.push_back(emp);
    }

    std::ofstream file(filename, std::ios::binary);
    for (const auto& emp : employees) {
        file.write((char*)&emp, sizeof(employee));
    }
    file.close();

    std::cout << "\nFile created successfully!\n";
}

void printFile() {
    std::cout << "\n=== File contents ===\n";
    std::ifstream file(filename, std::ios::binary);
    employee emp;

    while (file.read((char*)&emp, sizeof(employee))) {
        std::cout << "ID: " << emp.num
            << ", Name: " << emp.name
            << ", Hours: " << emp.hours << std::endl;
    }
    file.close();
}

void handleClient(int clientId) {
    std::wstring pipeName = L"\\\\.\\pipe\\employee_pipe_" + std::to_wstring(clientId);
    std::cout << "Client " << clientId << " connected\n";

    HANDLE hPipe = CreateNamedPipe(
        pipeName.c_str(),
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        1024,
        1024,
        0,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE) return;

    if (ConnectNamedPipe(hPipe, NULL)) {
        while (true) {
            char command;
            DWORD bytesRead;

            if (!ReadFile(hPipe, &command, sizeof(char), &bytesRead, NULL)) break;

            if (command == 'q') break;

            int id;
            ReadFile(hPipe, &id, sizeof(int), &bytesRead, NULL);

            if (command == 'r' || command == 'w') {
                bool found = false;
                employee* empPtr = nullptr;

                for (auto& emp : employees) {
                    if (emp.num == id) {
                        found = true;
                        empPtr = &emp;
                        break;
                    }
                }

                DWORD bytesWritten;
                WriteFile(hPipe, &found, sizeof(bool), &bytesWritten, NULL);

                if (found && empPtr) {
                    if (command == 'r') {
                        WriteFile(hPipe, empPtr, sizeof(employee), &bytesWritten, NULL);
                    }
                    else if (command == 'w') {
                        WriteFile(hPipe, empPtr, sizeof(employee), &bytesWritten, NULL);

                        employee updatedEmp;
                        ReadFile(hPipe, &updatedEmp, sizeof(employee), &bytesRead, NULL);
                        *empPtr = updatedEmp;

                        std::ofstream file(filename, std::ios::binary);
                        for (const auto& emp : employees) {
                            file.write((char*)&emp, sizeof(employee));
                        }
                        file.close();
                    }

                    char ack;
                    ReadFile(hPipe, &ack, sizeof(char), &bytesRead, NULL);
                }
            }
        }
    }

    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
    std::cout << "Client " << clientId << " disconnected\n";
}

void runClients() {
    std::vector<std::thread> clientThreads;

    for (int i = 0; i < clientCount; i++) {
        clientThreads.emplace_back(handleClient, i);
        Sleep(100);
    }

    for (int i = 0; i < clientCount; i++) {
        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        std::wstring cmd = L"Client.exe " + std::to_wstring(i);

        CreateProcess(NULL, const_cast<LPWSTR>(cmd.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    for (auto& thread : clientThreads) {
        thread.join();
    }
}

Server::Server() : clientCount(0) {}

void Server::start() {
    createFile();
    printFile();

    std::cout << "\nHow many clients to start? ";
    std::cin >> clientCount;

    runClients();

    std::cout << "\n=== Final file state ===\n";
    printFile();

    std::cout << "\nPress Enter to finish server work...";
    std::cin.ignore();
    std::cin.get();
}