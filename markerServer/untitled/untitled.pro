QT += core network gui

TARGET = untitled
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    httpparser.cpp \
    server.cpp \
    client.cpp \
    task.cpp

HEADERS += \
    httpparser.h \
    server.h \
    client.h \
    task.h


-c++11


