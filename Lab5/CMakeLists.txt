cmake_minimum_required(VERSION 3.15)
project(Lab5)

set(CMAKE_CXX_STANDARD 17)

add_executable(Server
    Server/server_main.cpp
    Server/Server/Server.cpp
    Core/Employee/Employee.cpp
    Core/NamedPipe/NamedPipe.cpp
    Server/EmployeeRepository/EmployeeRepository.cpp
    Server/EmployeeLockManager/EmployeeLockManager.cpp
    Server/ClientHandler/ClientHandler.cpp
)

add_executable(Client
    Client/client_main.cpp
    Client/Client/Client.cpp
    Core/Employee/Employee.cpp
    Core/NamedPipe/NamedPipe.cpp
)