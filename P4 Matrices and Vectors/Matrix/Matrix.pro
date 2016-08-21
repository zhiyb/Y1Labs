TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    complex.cpp \
    matrix.cpp
QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    complex.h \
    matrix.h
