TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    finddistance.cpp \
    matrix.cpp \
    tests.cpp

HEADERS += \
    finddistance.h \
    matrix.h \
    tests.h
