#include "ClientHandler.h"
#include <windows.h>
#include <iostream>

ClientHandler::ClientHandler(int id, EmployeeRepository& repo, EmployeeLockManager& locks)
    : clientId(id), repository(repo), lockManager(locks) {}

void ClientHandler::handleConnection() {
    std::wstring pipeName = L"\\\\.\\pipe\\employee_pipe_" + std::to_wstring(clientId);

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

    std::cout << "Client " << clientId << " waiting for connection..." << std::endl;

    if (ConnectNamedPipe(hPipe, NULL)) {
        std::cout << "Client " << clientId << " connected" << std::endl;
        processRequest(hPipe);
    }

    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
    std::cout << "Client " << clientId << " disconnected" << std::endl;
}

void ClientHandler::processRequest(HANDLE hPipe) {
    while (true) {
        char command;
        DWORD bytesRead;

        if (!ReadFile(hPipe, &command, sizeof(char), &bytesRead, NULL)) break;

        if (command == 'q') break;

        int employeeId;
        if (!ReadFile(hPipe, &employeeId, sizeof(int), &bytesRead, NULL)) break;

        if (command == 'r') {
            handleReadRequest(hPipe, employeeId);
        }
        else if (command == 'w') {
            handleWriteRequest(hPipe, employeeId);
        }
    }
}

void ClientHandler::handleReadRequest(HANDLE hPipe, int employeeId) {
    Employee* emp = repository.findEmployeeById(employeeId);
    DWORD bytesWritten;

    bool found = (emp != nullptr);
    WriteFile(hPipe, &found, sizeof(bool), &bytesWritten, NULL);

    if (!found) return;

    lockManager.lockForRead(employeeId);

    char buffer[Employee::getSerializedSize()];
    emp->serialize(buffer);
    WriteFile(hPipe, buffer, Employee::getSerializedSize(), &bytesWritten, NULL);

    lockManager.unlock(employeeId);

    char ack;
    DWORD bytesRead;
    ReadFile(hPipe, &ack, sizeof(char), &bytesRead, NULL);
}

void ClientHandler::handleWriteRequest(HANDLE hPipe, int employeeId) {
    Employee* emp = repository.findEmployeeById(employeeId);
    DWORD bytesWritten;

    bool found = (emp != nullptr);
    WriteFile(hPipe, &found, sizeof(bool), &bytesWritten, NULL);

    if (!found) return;

    lockManager.lockForWrite(employeeId);

    char buffer[Employee::getSerializedSize()];
    emp->serialize(buffer);
    WriteFile(hPipe, buffer, Employee::getSerializedSize(), &bytesWritten, NULL);

    DWORD bytesRead;
    ReadFile(hPipe, buffer, Employee::getSerializedSize(), &bytesRead, NULL);

    Employee updatedEmp;
    updatedEmp.deserialize(buffer);
    repository.updateEmployee(employeeId, updatedEmp);

    lockManager.unlock(employeeId);

    char ack;
    ReadFile(hPipe, &ack, sizeof(char), &bytesRead, NULL);
}