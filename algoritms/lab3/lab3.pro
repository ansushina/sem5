TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    mergesort.cpp \
    shakersort.cpp \
    coutingsort.cpp \
    test.cpp

HEADERS += \
    mergesort.h \
    shakersort.h \
    coutingsort.h \
    test.h
