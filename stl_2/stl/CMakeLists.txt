cmake_minimum_required(VERSION 3.22)
project(stl)

set(CMAKE_CXX_STANDARD 20)

add_executable(stl main.cpp)

add_subdirectory(tests)