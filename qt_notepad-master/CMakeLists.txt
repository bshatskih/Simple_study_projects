cmake_minimum_required(VERSION 3.23)
project(qt_notepad)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Xml
        REQUIRED)

include_directories(src)

add_executable(qt_notepad src/main.cpp src/textedit.cpp src/textedit.h src/mainwindow.cpp src/mainwindow.h src/mainwindow.ui src/textedit.cpp src/textedit.h src/Highlighter.cpp src/Highlighter.h src/resources.qrc src/fileTabWidget.h src/fileTabWidget.cpp src/Custom.h src/Custom.cpp src/multiple_unsaved_files.cpp src/multiple_unsaved_files.h src/multiple_unsaved_files.ui src/linenumberarea.cpp src/linenumberarea.h)
target_link_libraries(qt_notepad
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Xml
        )
