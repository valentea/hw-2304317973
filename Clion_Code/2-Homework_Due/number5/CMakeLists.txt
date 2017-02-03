cmake_minimum_required(VERSION 3.3)
project(number5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES hw2_lists.cpp)
add_executable(number5 ${SOURCE_FILES})