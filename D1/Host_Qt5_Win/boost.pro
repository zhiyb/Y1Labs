#-------------------------------------------------
#
# Project created by QtCreator 2014-01-21T19:15:40
#
#-------------------------------------------------

#-------------------------------------------------
# This is the C++(Qt5) code for host program,
# to control the boost converter.
# Wrote by Yubo Zhi (yz39g13@soton.ac.uk)
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = boost
TEMPLATE = app

SOURCES += main.cpp\
        window.cpp

HEADERS  += window.h \
    comm.h
