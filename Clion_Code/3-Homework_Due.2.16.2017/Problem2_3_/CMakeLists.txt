cmake_minimum_required(VERSION 3.6)
project(Problem2_3_)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        llistdbl_test.cpp
        llistint.cpp
        llistint.h)

add_executable(Problem2_3_ ${SOURCE_FILES})