# -------------------------------------------------
# Project created by QtCreator 2009-06-11T15:35:52
# -------------------------------------------------
CONFIG += WARN_ON
TEMPLATE = lib
TARGET = $$qtLibraryTarget(meters)
DEFINES += LIBMETERS_LIBRARY
SOURCES += abstractmeter.cpp \
    coilmeter.cpp \
    horizontalmeter.cpp \
    alarmmeter.cpp
HEADERS += abstractmeter.h \
    libmeters_global.h \
    coilmeter.h \
    horizontalmeter.h \
    alarmmeter.h
