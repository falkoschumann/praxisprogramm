TARGET       = core
TEMPLATE     = lib
CONFIG      += staticlib
SOURCES     += recordnavigation.cpp \
               form.cpp
HEADERS     += recordnavigation.h \
               recordnavigation_p.h \
               form.h \
               form_p.h
FORMS       += recordnavigation.ui
RESOURCES   += core.qrc
INCLUDEPATH += ..
