#include "EmployeeLockManager.h"
#include <string>

EmployeeLockManager::EmployeeLockManager() = default;

EmployeeLockManager::~EmployeeLockManager() {
    for (auto& pair : mutexMap) {
        CloseHandle(pair.second);
    }
}

void EmployeeLockManager::lockForRead(int employeeId) {
    std::lock_guard<std::mutex> lock(mapMutex);

    auto it = mutexMap.find(employeeId);
    HANDLE mutex;

    if (it == mutexMap.end()) {
        std::wstring mutexName = L"Global\\employee_mutex_" + std::to_wstring(employeeId);
        mutex = CreateMutex(NULL, FALSE, mutexName.c_str());
        mutexMap[employeeId] = mutex;
    }
    else {
        mutex = it->second;
    }

    WaitForSingleObject(mutex, INFINITE);
}

void EmployeeLockManager::lockForWrite(int employeeId) {
    lockForRead(employeeId);
}

void EmployeeLockManager::unlock(int employeeId) {
    std::lock_guard<std::mutex> lock(mapMutex);

    auto it = mutexMap.find(employeeId);
    if (it != mutexMap.end()) {
        ReleaseMutex(it->second);
    }
}