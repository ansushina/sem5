TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_LFLAGS += -pthread

QMAKE_CXXFLAGS += -std=gnu++0x -pthread
QMAKE_CFLAGS += -std=gnu++0x -lpthread

SOURCES += main.cpp \
    alg.cpp

HEADERS += \
    alg.h \
    matrix.h
