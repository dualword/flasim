TEMPLATE = app
TARGET = ./bin/flasim
DEPENDPATH += . src
INCLUDEPATH += . src

Qt -= qt
DEPENDPATH += .
INCLUDEPATH += .

LIBS += -lsfml-system -lsfml-audio -lIrrlicht

HEADERS += src/Aircraft.hpp \
           src/Dispatcher.hpp \
           src/FireUnit.hpp \
           src/FlaSimApp.hpp \
           src/Globals.hpp \
           src/TurretCamAnimator.hpp
           
SOURCES += src/Aircraft.cpp \
           src/Dispatcher.cpp \
           src/FireUnit.cpp \
           src/FlaSimApp.cpp \
           src/Globals.cpp \
           src/main.cpp \
           src/TurretCamAnimator.cpp
           
OBJECTS_DIR = .build/obj
MOC_DIR     = .build/moc
RCC_DIR     = .build/rcc
UI_DIR      = .build/ui

