#-------------------------------------------------
#
# Project created by QtCreator 2015-03-19T18:38:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = whiteboard
TEMPLATE = app


SOURCES += main.cpp \
    connection.cpp \
    mainwindow.cpp \
    sendwidget.cpp \
    recvwidget.cpp

HEADERS  += \
    connection.h \
    mainwindow.h \
    sendwidget.h \
    recvwidget.h \
    package.h
