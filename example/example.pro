# -------------------------------------------------
# Project created by QtCreator 2009-06-12T10:22:44
# -------------------------------------------------
TARGET = example
TEMPLATE = app
DEPENDPATH += ../lib
INCLUDEPATH += ../lib

qtAddLibrary(meters)
debug{
    LIBS += -L../lib/debug/
}

release {
    LIBS += -L../lib/release/
}

SOURCES += main.cpp
HEADERS += main.h
