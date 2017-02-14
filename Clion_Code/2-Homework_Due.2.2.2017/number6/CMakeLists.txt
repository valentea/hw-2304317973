cmake_minimum_required(VERSION 3.3.2)
project(number6)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        llistdbl.cpp
        llistdbl.h
        llistdbl_test.cpp)

add_executable(number6 ${SOURCE_FILES})