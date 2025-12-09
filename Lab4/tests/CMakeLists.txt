find_package(GTest REQUIRED)

add_executable(test_message test_message.cpp)
target_link_libraries(test_message GTest::gtest_main)
target_include_directories(test_message PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_executable(test_shared_file test_shared_file.cpp)
target_link_libraries(test_shared_file GTest::gtest_main)
target_include_directories(test_shared_file PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_test(NAME MessageTest COMMAND test_message)
add_test(NAME SharedFileTest COMMAND test_shared_file)