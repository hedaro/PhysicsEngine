TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    ../entities.h

LIBS += -lGL -lglut
