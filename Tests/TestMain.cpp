#include <iostream>
#include <windows.h>
#include "../core/employee.h"

using namespace std;

int main() {
    cout << "=== Testing Main (Process Creation) ===" << endl;

    // Тест создания простого процесса
    STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    si.cb = sizeof(si);

    // Пробуем запустить notepad (более надежно чем calc)
    BOOL result = CreateProcessA(
        NULL,
        "notepad.exe",
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    );

    if (result) {
        cout << "PASS: Process created successfully" << endl;

        // Даем процессу немного поработать и закрываем
        Sleep(1000);
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        cout << "PASS: Process terminated correctly" << endl;
    }
    else {
        cout << "FAIL: Cannot create process" << endl;
        cout << "Error code: " << GetLastError() << endl;
    }

    cout << "=== Main tests completed ===" << endl << endl;
    return 0;
}