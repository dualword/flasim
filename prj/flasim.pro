QT       -= core gui

CONFIG += debug_and_release
Release:TARGET = flasim
Debug:TARGET = flasimD
TEMPLATE = app

unix:INCLUDEPATH += /usr/include/irrlicht
win32:INCLUDEPATH += ../pharus/external/irrlicht

unix:LIBS += -lIrrlicht -lcAudio

DESTDIR = ../bin

HEADERS += \
    ../src/FlaSimApp.hpp \
    ../src/FireUnit.hpp \
    ../src/Globals.hpp \
    ../src/TurretCamAnimator.hpp \
    ../src/Aircraft.hpp \
    ../src/Dispatcher.hpp

SOURCES += \
    ../src/FlaSimApp.cpp \
    ../src/main.cpp \
    ../src/FireUnit.cpp \
    ../src/Globals.cpp \
    ../src/TurretCamAnimator.cpp \
    ../src/Aircraft.cpp \
    ../src/Dispatcher.cpp
