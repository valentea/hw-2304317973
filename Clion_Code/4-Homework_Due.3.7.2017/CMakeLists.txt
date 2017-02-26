cmake_minimum_required(VERSION 3.6)
project(4_Homework_Due_3_7_2017)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        amazon.cpp
        database.txt
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
        util.h book.h book.cpp)

add_executable(4_Homework_Due_3_7_2017 ${SOURCE_FILES})