#-------------------------------------------------
#
# Project created by QtCreator 2014-01-24T15:10:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sudoku
TEMPLATE = app

RC_FILE = Icon/Icon.rc

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -Os
#QMAKE_LFLAGS_RELEASE -= -O1

SOURCES += main.cpp\
        mainwindow.cpp \
    sboard.cpp \
    sbox.cpp \
    sselector.cpp

HEADERS  += mainwindow.h \
    sboard.h \
    sbox.h \
    sselector.h \
    define.h
