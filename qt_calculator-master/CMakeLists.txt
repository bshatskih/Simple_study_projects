cmake_minimum_required(VERSION 3.23)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:\\Qt\\6.2.4\\mingw_64")
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Qml
        REQUIRED)

add_executable(Calculator main.cpp Calculator.cpp Calculator.h mainwidnow.h)
target_link_libraries(Calculator
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::Qml
        )

