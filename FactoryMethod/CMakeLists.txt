cmake_minimum_required(VERSION 3.27)
project(FactoryMethod)

set(CMAKE_CXX_STANDARD 23)

add_executable(FactoryMethod main.cpp
        Logistics.h
        Ship.h
        SeaLogistic.h
        RoadLogistic.h
        Transport.h
        Truck.h
        )
