QT          += sql
TARGET       = stammdaten
TEMPLATE     = lib
CONFIG      += staticlib
SOURCES     += patientform.cpp
HEADERS     += patientform.h \
               patientform_p.h
FORMS       += patientformbody.ui
LIBS        += ../core/libcore.a
INCLUDEPATH += ..
