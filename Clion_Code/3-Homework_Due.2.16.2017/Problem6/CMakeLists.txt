cmake_minimum_required(VERSION 3.6)
project(Problem6)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        cnf.cpp
        cnf.h
        cnfeval.cpp
        llistint.cpp
        llistint.h
        queueint.cpp
        queueint.h)

add_executable(Problem6 ${SOURCE_FILES})