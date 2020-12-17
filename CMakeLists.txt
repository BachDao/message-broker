cmake_minimum_required(VERSION 3.15.0)
project(message-broker VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
file(GLOB SRC_FILES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
        ${CMAKE_CURRENT_LIST_DIR}/proto/*.cc)
add_library(message-broker ${SRC_FILES})

find_package(Boost)

target_include_directories(message-broker 
                    PUBLIC 
                        ${Boost_INCLUDE_DIRS}
                        ${CMAKE_CURRENT_LIST_DIR}/include
                        ${CMAKE_CURRENT_LIST_DIR}/proto)

find_package(protobuf CONFIG REQUIRED)
target_link_libraries(message-broker PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
