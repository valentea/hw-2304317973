cmake_minimum_required(VERSION 3.6)
project(SkipListClass)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        SkipList.h)

add_executable(SkipListClass ${SOURCE_FILES})