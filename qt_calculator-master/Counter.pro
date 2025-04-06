# собирал с помощью cmake. этот файл чуть чуть подредактировал чтобы запускался,
# но проверить не имею возможности. рекоммендую собирать с через CMakeLists.txt
QT += core gui
CONFIG += C++20

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets qml

TARGET = Calculator
TEMPLATE = app


SOURCES += main.cpp \
           Calculator.cpp

HEADERS += \
           Calculator.h \
           mainwidnow.h
