TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

RC_FILE = Icon/Icon.rc

SOURCES += main.cpp \
    sboard.cpp \
    sbox.cpp

HEADERS += \
    define.h \
    sboard.h \
    sbox.h

