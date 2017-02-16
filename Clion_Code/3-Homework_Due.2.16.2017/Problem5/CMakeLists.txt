cmake_minimum_required(VERSION 3.6)
project(Problem5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        llistint.cpp
        llistint.h
        queueint.cpp
        queueint.h
        scheduling.cpp)

add_executable(Problem5 ${SOURCE_FILES})