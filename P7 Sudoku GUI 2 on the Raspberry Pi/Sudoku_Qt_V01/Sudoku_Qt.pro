#-------------------------------------------------
#
# Project created by QtCreator 2014-03-12T15:55:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sudoku_Qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    node.cpp \
    dancinglinks.cpp \
    sudoku.cpp \
    sudokuwidget.cpp \
    sudokuselector.cpp

HEADERS  += mainwindow.h \
    node.h \
    dancinglinks.h \
    sudoku.h \
    sudokuwidget.h \
    sudokuselector.h
