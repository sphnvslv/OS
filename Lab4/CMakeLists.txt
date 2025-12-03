cmake_minimum_required(VERSION 3.15)
project(IPCLab)

set(CMAKE_CXX_STANDARD 17)

add_executable(receiver 
    receiver/main_receiver.cpp
    receiver/receiver.cpp
)

add_executable(sender
    sender/main_sender.cpp
    sender/sender.cpp
)