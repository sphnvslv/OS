cmake_minimum_required(VERSION 3.10)
project(Lab1)

add_library(core INTERFACE)
target_include_directories(core INTERFACE ${CMAKE_SOURCE_DIR}/core)

add_subdirectory(Main)
add_subdirectory(Creator)
add_subdirectory(Reporter)
add_subdirectory(Tests)