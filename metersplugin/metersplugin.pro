CONFIG += designer plugin
TARGET = metersplugin
TARGET = $$qtLibraryTarget($$TARGET)
TEMPLATE = lib

DEFINES += LIBMETERS_LIBRARY

INCLUDEPATH += ../lib
qtAddLibrary(meters)
debug{
    LIBS += -L../lib/debug/
}

release {
    LIBS += -L../lib/release/
}

QTDIR_build:DESTDIR = $$QT_BUILD_TREE/plugins/designer

HEADERS = libmetersplugin.h
SOURCES = libmetersplugin.cpp

target.path = $$[QT_INSTALL_PLUGINS]/designer
sources.files = $$SOURCES $$HEADERS *.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/designer/libmetersplugin
INSTALLS += target sources
RESOURCES += libmetersplugin.qrc
