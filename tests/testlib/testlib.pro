QT       += testlib
QT       -= gui
TARGET    = tst_testlib
CONFIG   += console testcase
CONFIG   -= app_bundle
TEMPLATE  = app
SOURCES  += tst_testlibtest.cpp
DEFINES  += \"SRCDIR=\\\"$$PWD/\\\"\"
