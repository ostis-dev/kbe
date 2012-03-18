
TARGET        = $$qtLibraryTarget(scs)
TEMPLATE      = lib
INCLUDEPATH  += ../../kbe

DESTDIR = ../../bin/plugins

CONFIG       += plugin

OBJECTS_DIR = obj
MOC_DIR = moc


HEADERS += \
    abstracthighlightingrule.h \
    codeeditor.h \
    multilinecommenthighlightingrule.h \
    scsfileloader.h \
    scsfilewriter.h \
    scshighlightingrulespool.h \
    scsplugin.h \
    scswindow.h \
    stdhighlightingrule.h \
    syntaxhighlighter.h

SOURCES += \
    abstracthighlightingrule.cpp \
    codeeditor.cpp \
    multilinecommenthighlightingrule.cpp \
    scsfileloader.cpp \
    scsfilewriter.cpp \
    scshighlightingrulespool.cpp \
    scsplugin.cpp \
    scswindow.cpp \
    stdhighlightingrule.cpp \
    syntaxhighlighter.cpp
