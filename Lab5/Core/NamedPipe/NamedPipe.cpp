#include "NamedPipe.h"
#include <iostream>

NamedPipe::NamedPipe(const std::wstring& name, bool isServer)
    : pipeName(name), isServer(isServer), pipeHandle(INVALID_HANDLE_VALUE) {}

NamedPipe::~NamedPipe() {
    if (pipeHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(pipeHandle);
    }
}

bool NamedPipe::create() {
    pipeHandle = CreateNamedPipe(
        pipeName.c_str(),
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        1024,
        1024,
        0,
        NULL
    );

    return pipeHandle != INVALID_HANDLE_VALUE;
}

bool NamedPipe::connect() {
    pipeHandle = CreateFile(
        pipeName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (pipeHandle == INVALID_HANDLE_VALUE) {
        return false;
    }

    DWORD mode = PIPE_READMODE_MESSAGE;
    return SetNamedPipeHandleState(pipeHandle, &mode, NULL, NULL) != 0;
}

bool NamedPipe::waitForConnection() {
    return ConnectNamedPipe(pipeHandle, NULL) != 0;
}

void NamedPipe::disconnect() {
    DisconnectNamedPipe(pipeHandle);
}

bool NamedPipe::read(void* buffer, DWORD size) {
    DWORD bytesRead;
    return ReadFile(pipeHandle, buffer, size, &bytesRead, NULL) != 0;
}

bool NamedPipe::write(const void* buffer, DWORD size) {
    DWORD bytesWritten;
    return WriteFile(pipeHandle, buffer, size, &bytesWritten, NULL) != 0;
}