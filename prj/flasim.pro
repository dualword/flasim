QT       -= core gui

CONFIG += debug_and_release
Release:TARGET = flasim
Debug:TARGET = flasimD
TEMPLATE = app

unix:INCLUDEPATH += /usr/include/irrlicht
win32:INCLUDEPATH += ../pharus/external/irrlicht

unix:LIBS += -lIrrlicht

DESTDIR = ../bin

HEADERS += \
    ../src/FlaSimApp.hpp

SOURCES += \
    ../src/FlaSimApp.cpp \
    ../src/main.cpp
