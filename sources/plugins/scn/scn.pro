
TARGET        = $$qtLibraryTarget(scn)
TEMPLATE      = lib
INCLUDEPATH  += ../../kbe

DESTDIR = ../../bin/plugins

CONFIG       += plugin

OBJECTS_DIR = obj
MOC_DIR = moc

RESOURCES += \
    scn.qrc

HEADERS += \
    scnplugin.h \
    scnwindow.h

SOURCES += \
    scnplugin.cpp \
    scnwindow.cpp
