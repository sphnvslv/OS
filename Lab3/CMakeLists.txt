cmake_minimum_required(VERSION 3.10)
project(Lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab3 
    main.cpp
    arr/arr.cpp
    marker/marker.cpp
    threads/threads.cpp
)

target_include_directories(Lab3 PRIVATE
    .
    arr
    marker
    threads
)

if(WIN32)
    target_link_libraries(Lab3 synchronization)
endif()


option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
   enable_testing()
    add_subdirectory(tests)
endif()