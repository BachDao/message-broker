cmake_minimum_required(VERSION 3.15.0)
project(brokerTest VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

add_executable(brokerTest bufferTest.cpp parserTest.cpp)

# include source of message-broker
include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt)
target_link_libraries(brokerTest PRIVATE message-broker)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(brokerTest PRIVATE GTest::gtest GTest::gtest_main)

