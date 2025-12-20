#pragma once
#include "EmployeeRepository.h"
#include "EmployeeLockManager.h"
#include <memory>

class ClientHandler {
private:
    int clientId;
    EmployeeRepository& repository;
    EmployeeLockManager& lockManager;

public:
    ClientHandler(int id, EmployeeRepository& repo, EmployeeLockManager& locks);

    void handleConnection();

private:
    void processRequest(HANDLE hPipe);
    void handleReadRequest(HANDLE hPipe, int employeeId);
    void handleWriteRequest(HANDLE hPipe, int employeeId);
};