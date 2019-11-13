TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_LFLAGS += -pthread

SOURCES += main.cpp \
    alg.cpp

HEADERS += \
    alg.h \
    matrix.h
