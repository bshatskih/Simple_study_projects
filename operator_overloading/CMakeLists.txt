cmake_minimum_required(VERSION 3.21)
project(operator_overloading)

set(CMAKE_CXX_STANDARD 14)

include_directories(operator_overloading)

add_executable(operator_overloading
        operator_overloading/Main.cpp
        operator_overloading/Matrix.cpp
        operator_overloading/Matrix.h
        operator_overloading/Vector.cpp
        operator_overloading/Vector.h)
