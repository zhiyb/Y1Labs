QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HSM_Host
TEMPLATE = app

LIBS += -L. -lbcm2835

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h
