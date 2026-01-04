cmake_minimum_required(VERSION 3.10)
project(ToDoAPI)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_CXX_STANDARD 17)

set(GTest_DIR "C:/vcpkg/installed/x64-windows/share/gtest")
find_package(GTest CONFIG REQUIRED)

# SQLite3 библиотека
add_library(sqlite3 STATIC sqlite3.c)

# ====== ОСНОВНОЕ ПРИЛОЖЕНИЕ (todo_api) ======
add_executable(todo_api 
    main.cpp
    Database/Database.cpp
    Logger/Logger.cpp
    Task/Task.cpp
)

# ДОБАВЬТЕ ЭТО - пути к заголовкам для todo_api
target_include_directories(todo_api PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Database
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger  
    ${CMAKE_CURRENT_SOURCE_DIR}/Task
    ${CMAKE_CURRENT_SOURCE_DIR}/asio/include
)

# Подключаем библиотеки для todo_api
target_link_libraries(todo_api PRIVATE sqlite3)

if(WIN32)
    target_link_libraries(todo_api PRIVATE ws2_32)
endif()

# ====== ТЕСТЫ (todo_tests) ======
add_executable(todo_tests
    tests.cpp  
    Database/Database.cpp
    Logger/Logger.cpp
    Task/Task.cpp
)

# ДОБАВЬТЕ ЭТО - те же пути для тестов
target_include_directories(todo_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Database
    ${CMAKE_CURRENT_SOURCE_DIR}/Logger  
    ${CMAKE_CURRENT_SOURCE_DIR}/Task
    ${CMAKE_CURRENT_SOURCE_DIR}/asio/include
)

# Подключаем библиотеки для тестов
target_link_libraries(todo_tests PRIVATE 
    sqlite3 
    GTest::gtest 
    GTest::gtest_main  
)

if(WIN32)
    target_link_libraries(todo_tests PRIVATE ws2_32)
endif()

# Включаем систему тестирования
enable_testing()
add_test(NAME ToDoAPITests COMMAND todo_tests)