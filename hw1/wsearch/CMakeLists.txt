cmake_minimum_required(VERSION 3.6)
project(wsearch)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES wsearch.cpp)
add_executable(wsearch ${SOURCE_FILES})