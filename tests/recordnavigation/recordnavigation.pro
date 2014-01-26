QT          += sql testlib
TARGET       = tst_recordnavigationtest
CONFIG      += console
CONFIG      -= app_bundle
TEMPLATE     = app
SOURCES     += tst_recordnavigationtest.cpp
INCLUDEPATH += ../../src/libs/core
DEFINES     += \"SRCDIR=\\\"$$PWD/\\\"\"
LIBS        += ../../src/libs/core/libcore.a
INCLUDEPATH += ../../src/libs

