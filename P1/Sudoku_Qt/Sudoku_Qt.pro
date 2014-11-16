#-------------------------------------------------
#
# Project created by QtCreator 2014-01-28T15:33:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sudoku_Qt
TEMPLATE = app
RC_FILE = Icon/Icon.rc

SOURCES += main.cpp\
        window.cpp \
    sboard.cpp \
    sbox.cpp \
    sudokuboard.cpp \
    sudokubox.cpp \
    squarewidget.cpp \
    sudokuselector.cpp

HEADERS  += window.h \
    define.h \
    sboard.h \
    sbox.h \
    sudokuboard.h \
    sudokubox.h \
    squarewidget.h \
    sudokuselector.h
