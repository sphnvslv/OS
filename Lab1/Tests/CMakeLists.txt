cmake_minimum_required(VERSION 3.10)
project(Tests)

add_executable(TestMain TestMain.cpp)         
target_link_libraries(TestMain PRIVATE core)
target_include_directories(TestMain PRIVATE ${CMAKE_SOURCE_DIR}/core)

add_executable(TestCreator TestCreator.cpp)    
target_link_libraries(TestCreator PRIVATE core)
target_include_directories(TestCreator PRIVATE ${CMAKE_SOURCE_DIR}/core)

add_executable(TestReporter TestReporter.cpp)  
target_link_libraries(TestReporter PRIVATE core)
target_include_directories(TestReporter PRIVATE ${CMAKE_SOURCE_DIR}/core)

if(WIN32)
    target_link_libraries(TestMain PRIVATE Kernel32)
endif()