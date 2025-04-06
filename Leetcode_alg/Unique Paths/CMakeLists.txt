cmake_minimum_required(VERSION 3.26)
project(Unique_Paths)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(Unique_Paths main.cpp
        Solution.h)
