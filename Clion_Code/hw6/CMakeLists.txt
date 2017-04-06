cmake_minimum_required(VERSION 3.6)
project(hw6)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        board.cpp
        board.h
        heap.h
        puzzle.cpp
        puzzle_heur.h
        puzzle_move.h
        puzzle_solver.h)

add_executable(hw6 ${SOURCE_FILES})