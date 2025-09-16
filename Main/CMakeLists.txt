add_executable(Main Main.cpp)
target_link_libraries(Main PRIVATE core)

if(WIN32)
    target_link_libraries(Main PRIVATE Kernel32)
endif()