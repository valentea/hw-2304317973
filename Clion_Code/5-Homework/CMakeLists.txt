cmake_minimum_required(VERSION 3.6)
project(5_Homework)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        amazon.cpp
        Book.cpp
        Book.h
        Clothing.cpp
        Clothing.h
        datastore.h
        db_parser.cpp
        db_parser.h
        Movie.cpp
        Movie.h
        mydatastore.cpp
        mydatastore.h
        product.cpp
        product.h
        product_parser.cpp
        product_parser.h
        review.h
        user.cpp
        user.h
        util.cpp
        util.h msort.h)

add_executable(5_Homework ${SOURCE_FILES})