cmake_minimum_required(VERSION 4.2)
project(LABA3)

set(CMAKE_CXX_STANDARD 20)

add_executable(LABA3 main.cpp
        base_matrix.h
        square_matrix.h
        rectangle_matrix.h
        imatrix.h
        triangle_matrix.h
        diagonal_matrix.h
        sparse_matrix.h
        complex.h
)
