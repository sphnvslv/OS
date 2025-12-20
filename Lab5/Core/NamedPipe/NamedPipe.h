#pragma once
#include <windows.h>
#include <string>

class NamedPipe {
private:
    HANDLE pipeHandle;
    std::wstring pipeName;
    bool isServer;

public:
    NamedPipe(const std::wstring& name, bool isServer);
    ~NamedPipe();

    bool create();
    bool connect();
    bool waitForConnection();
    void disconnect();

    bool read(void* buffer, DWORD size);
    bool write(const void* buffer, DWORD size);
};