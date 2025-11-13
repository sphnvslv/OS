add_executable(testLab3
    testMain.cpp
    testThread.cpp
    ../arr/arr.cpp
    ../marker/marker.cpp
    ../threads/threads.cpp
)

target_include_directories(testLab3 PRIVATE
    ..
    ../arr
    ../marker
    ../threads
)

if(WIN32)
    target_link_libraries(testLab3 synchronization)
endif()

add_test(NAME testLab3 COMMAND testLab3)