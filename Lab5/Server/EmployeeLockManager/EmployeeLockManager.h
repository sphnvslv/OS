#pragma once
#include <windows.h>
#include <map>
#include <mutex>

class EmployeeLockManager {
private:
    std::map<int, HANDLE> mutexMap;
    std::mutex mapMutex;

public:
    EmployeeLockManager();
    ~EmployeeLockManager();

    void lockForRead(int employeeId);
    void lockForWrite(int employeeId);
    void unlock(int employeeId);
};