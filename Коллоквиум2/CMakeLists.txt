cmake_minimum_required(VERSION 3.10)
project(ToDoAPI)

set(CMAKE_CXX_STANDARD 17)

add_library(sqlite3 STATIC sqlite3.c)

add_executable(todo_api 
    main.cpp
    Logger.cpp
    Database.cpp
    Task.cpp
)

target_include_directories(todo_api PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(todo_api sqlite3)

if(WIN32)
    target_link_libraries(todo_api ws2_32)
else()
    target_link_libraries(todo_api pthread)
endif()

find_package(GTest CONFIG REQUIRED)
 
add_executable(todo_tests
     tests.cpp
     Logger.cpp
     Database.cpp
     Task.cpp
 )
 
 target_link_libraries(todo_tests GTest::gtest GTest::gtest_main sqlite3)
 
 enable_testing()
 add_test(NAME AllTestsInMain COMMAND todo_tests)