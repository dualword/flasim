QT       -= core gui

CONFIG += debug_and_release
Release:TARGET = flasim
Debug:TARGET = flasimD
TEMPLATE = app

unix:INCLUDEPATH += /usr/include/irrlicht
INCLUDEPATH += ../ext/cAudio/cAudio/include ../ext/cAudio/include

unix:LIBS += -L../ext/cAudio/cAudio
unix:LIBS += -lIrrlicht -lopenal -lcAudio

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
