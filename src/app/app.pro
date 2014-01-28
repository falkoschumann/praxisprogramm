QT          += core gui sql
TARGET       = app
TEMPLATE     = app
SOURCES     += main.cpp\
               mainwindow.cpp
HEADERS     += mainwindow.h
LIBS        += ../libs/core/libcore.a ../libs/stammdaten/libstammdaten.a
INCLUDEPATH += ../libs
