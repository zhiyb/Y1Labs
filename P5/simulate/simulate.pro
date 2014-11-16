TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    object.cpp \
    gate2to1.cpp \
    halfadder.cpp \
    fulladder.cpp \
    multibitadder.cpp

HEADERS += \
    object.h \
    gate2to1.h \
    xor.h \
    or.h \
    and.h \
    halfadder.h \
    fulladder.h \
    multibitadder.h

