QT       += sql testlib

QT       -= gui

TARGET = tst_testlib
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testlibtest.cpp
DEFINES += \"SRCDIR=\\\"$$PWD/\\\"\"
