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
    scnwindow.h \
    scneditorscene.h \
    scnfielditem.h \
    scnfieldglobalidtf.h \
    scninputdialog.h

SOURCES += \
    scnplugin.cpp \
    scnwindow.cpp \
    scneditorscene.cpp \
    scnfielditem.cpp \
    scnfieldglobalidtf.cpp \
    scninputdialog.cpp
