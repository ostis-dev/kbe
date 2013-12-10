
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
<<<<<<< HEAD
    scnfieldglobalidtf.h
=======
    scnfieldglobalidtf.h \
    scninputdialog.h
>>>>>>> bf0c1d6d3442b4bad1171f3e79d21965c3b6c417

SOURCES += \
    scnplugin.cpp \
    scnwindow.cpp \
    scneditorscene.cpp \
    scnfielditem.cpp \
<<<<<<< HEAD
    scnfieldglobalidtf.cpp
=======
    scnfieldglobalidtf.cpp \
    scninputdialog.cpp
>>>>>>> bf0c1d6d3442b4bad1171f3e79d21965c3b6c417
