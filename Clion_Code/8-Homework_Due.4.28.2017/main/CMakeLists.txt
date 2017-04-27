cmake_minimum_required(VERSION 3.6)
project(main)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        heap.h
        main.cpp)

add_executable(main ${SOURCE_FILES})