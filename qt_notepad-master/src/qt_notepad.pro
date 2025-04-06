QT += core gui
CONFIG += C++20

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets widgets xml xmlpatterns

TARGET = qt_notepad
TEMPLATE = app

SOURCES +=  main.cpp \
            mainwindow.cpp \
            textedit.cpp \
            Highlighter.cpp \
            fileTabWidget.cpp \
            Custom.cpp \
            multiple_unsaved_files.cpp \
            linenumberarea.cpp

FORMS += multiple_unsaved_files.ui \
        mainwindow.ui

RESOURCES += resources.qrc

HEADERS += mainwindow.h \
           textedit.h \
           Highlighter.h \
           fileTabWidget.h \
           Custom.h \
           multiple_unsaved_files.h \
           linenumberarea.h

DESTDIR = build_dir_qmake
OBJECTS_DIR = build_dir_qmake/.obj
MOC_DIR = build_dir_qmake/.moc
RCC_DIR = build_dir_qmake/.rcc
UI_DIR = build_dir_qmake/.ui
