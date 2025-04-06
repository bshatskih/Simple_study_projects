cmake_minimum_required(VERSION 3.21)
project(qt_xml)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets Core Gui Xml REQUIRED)

add_executable(qt_xml main.cpp MainWindow.cpp MainWindow.h Parser.cpp Parser.h)
target_link_libraries(qt_xml Qt::Core Qt::Gui Qt::Widgets Qt::Xml)
