cmake_minimum_required(VERSION 3.15)
project(IPCLab)

set(CMAKE_CXX_STANDARD 17)

# Включить тесты (опционально)
option(BUILD_TESTS "Build tests" ON)

 "tests/test_message.cpp"# Основные приложения
add_executable(receiver receiver/main_receiver.cpp receiver/receiver.cpp)
add_executable(sender sender/main_sender.cpp sender/sender.cpp)

# Подключить Google Test
 "tests/test_message.cpp"if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()