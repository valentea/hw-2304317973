cmake_minimum_required(VERSION 3.6)
project(Problem4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        llistint.cpp
        llistint.h
        queueint.cpp
        queueint.h
        QueueList.cpp)

add_executable(Problem4 ${SOURCE_FILES})