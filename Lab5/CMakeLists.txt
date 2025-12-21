cmake_minimum_required(VERSION 3.15)
project(Lab5)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

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

add_executable(EmployeeTests
    Core/Employee/Employee.cpp
    Core/Employee/EmployeeTests.cpp
)
target_link_libraries(EmployeeTests GTest::gtest_main)
add_test(NAME EmployeeTests COMMAND EmployeeTests)

add_executable(EmployeeRepositoryTests
    Core/Employee/Employee.cpp
    Server/EmployeeRepository/EmployeeRepository.cpp
    Server/EmployeeRepository/EmployeeRepositoryTests.cpp
)
target_link_libraries(EmployeeRepositoryTests GTest::gtest_main)
add_test(NAME EmployeeRepositoryTests COMMAND EmployeeRepositoryTests)