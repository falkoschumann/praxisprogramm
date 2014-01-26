QT          += sql testlib
TARGET       = tst_recordnavigationtest
CONFIG      += console
CONFIG      -= app_bundle
TEMPLATE     = app
SOURCES     += tst_recordnavigationtest.cpp \
               ../../src/libs/core/recordnavigation.cpp
HEADERS     += ../../src/libs/core/recordnavigation.h \
               ../../src/libs/core/recordnavigation_p.h
FORMS       += ../../src/libs/core/recordnavigation.ui
INCLUDEPATH += ../../src/libs/core
DEFINES     += \"SRCDIR=\\\"$$PWD/\\\"\"
