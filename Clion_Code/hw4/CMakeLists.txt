cmake_minimum_required(VERSION 3.3)
project(hw4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    amazon.cpp
    datastore.h
    db_parser.cpp
    db_parser.h
    product.cpp
    product.h
    product_parser.cpp
    product_parser.h
    user.cpp
    user.h
    util.cpp
    util.h)

add_executable(hw4 ${SOURCE_FILES})