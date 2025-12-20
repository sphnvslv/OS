#include <windows.h>
#include <iostream>
#include <string>

struct employee {
    int num;
    char name[10];
    double hours;
};

bool connectToPipe(HANDLE& hPipe, int clientId) {
    std::wstring pipeName = L"\\\\.\\pipe\\employee_pipe_" + std::to_wstring(clientId);

    while (true) {
        hPipe = CreateFile(
            pipeName.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL
        );

        if (hPipe != INVALID_HANDLE_VALUE) {
            DWORD mode = PIPE_READMODE_MESSAGE;
            SetNamedPipeHandleState(hPipe, &mode, NULL, NULL);
            return true;
        }

        if (GetLastError() != ERROR_PIPE_BUSY) {
            return false;
        }

        std::cout << "Waiting for server..." << std::endl;
        Sleep(1000);
    }
}

int main(int argc, char* argv[]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc < 2) {
        std::cout << "Usage: Client.exe <client_id>" << std::endl;
        return 1;
    }

    int clientId = atoi(argv[1]);

    HANDLE hPipe;
    if (!connectToPipe(hPipe, clientId)) {
        std::cout << "Failed to connect to server" << std::endl;
        return 1;
    }

    std::cout << "Client " << clientId << " started" << std::endl;

    while (true) {
        std::cout << "\nChoose action:" << std::endl;
        std::cout << "1. Read record" << std::endl;
        std::cout << "2. Modify record" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Your choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 3) {
            char command = 'q';
            DWORD bytesWritten;
            WriteFile(hPipe, &command, sizeof(char), &bytesWritten, NULL);
            break;
        }

        int id;
        std::cout << "Enter employee ID: ";
        std::cin >> id;

        char command = (choice == 1) ? 'r' : 'w';
        DWORD bytesWritten;
        WriteFile(hPipe, &command, sizeof(char), &bytesWritten, NULL);
        WriteFile(hPipe, &id, sizeof(int), &bytesWritten, NULL);

        bool found;
        DWORD bytesRead;
        ReadFile(hPipe, &found, sizeof(bool), &bytesRead, NULL);

        if (!found) {
            std::cout << "Employee with ID " << id << " not found!" << std::endl;
            continue;
        }

        employee emp;
        ReadFile(hPipe, &emp, sizeof(employee), &bytesRead, NULL);

        std::cout << "\nCurrent data:" << std::endl;
        std::cout << "ID: " << emp.num << std::endl;
        std::cout << "Name: " << emp.name << std::endl;
        std::cout << "Hours: " << emp.hours << std::endl;

        if (choice == 2) {
            std::cout << "\nEnter new data:" << std::endl;
            std::cout << "Name (max 9 chars): ";
            std::cin >> emp.name;
            std::cout << "Worked hours: ";
            std::cin >> emp.hours;

            WriteFile(hPipe, &emp, sizeof(employee), &bytesWritten, NULL);
        }

        std::cout << "\nPress Enter to complete operation...";
        std::cin.ignore();
        std::cin.get();

        char ack = 'a';
        WriteFile(hPipe, &ack, sizeof(char), &bytesWritten, NULL);
    }

    CloseHandle(hPipe);
    std::cout << "Client " << clientId << " finished" << std::endl;

    return 0;
}