cmake_minimum_required(VERSION 3.15.0)
project(message-broker VERSION 1.0.0)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
add_library(message-broker ${SRC_FILES})

find_package(Boost)

target_include_directories(message-broker 
                    PUBLIC 
                        ${Boost_INCLUDE_DIRS}
                        ${CMAKE_CURRENT_SOURCE_DIR}/include)
