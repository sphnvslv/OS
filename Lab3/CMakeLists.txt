cmake_minimum_required(VERSION 3.10)
project(MarkerThreads)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(MarkerThreads 
    main.cpp
    arr/arr.cpp
    marker/marker.cpp
    threads/threads.cpp
)

target_include_directories(MarkerThreads PRIVATE
    .
    arr
    marker
    threads
)

if(WIN32)
    target_link_libraries(MarkerThreads synchronization)
endif()