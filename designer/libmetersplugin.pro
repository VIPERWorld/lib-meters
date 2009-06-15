CONFIG += designer plugin release
TARGET = metersplugin
TARGET = $$qtLibraryTarget($$TARGET)
TEMPLATE = lib

INCLUDEPATH += ../
LIBS += -L../release -lmeters

QTDIR_build:DESTDIR = $$QT_BUILD_TREE/plugins/designer
HEADERS = libmetersplugin.h
SOURCES = libmetersplugin.cpp
target.path = $$[QT_INSTALL_PLUGINS]/designer
sources.files = $$SOURCES $$HEADERS *.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/designer/libmetersplugin
INSTALLS += target sources
RESOURCES += battmeter.qrc
