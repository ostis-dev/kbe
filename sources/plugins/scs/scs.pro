
TARGET        = $$qtLibraryTarget(scs)
TEMPLATE      = lib
INCLUDEPATH  += ../../kbe

DESTDIR = ../../bin/plugins

CONFIG       += plugin

OBJECTS_DIR = obj
MOC_DIR = moc


HEADERS += \
    scsfileloader.h \
    scsfilewriter.h \
    scshighlightingrulespool.h \
    scsplugin.h \
    scswindow.h \
    scssyntaxhighlighter.h \
    scscodeeditor.h \
    scsstdhighlightingrule.h \
    scsmultilinecommenthighlightingrule.h \
    scsabstracthighlightingrule.h

SOURCES += \
    scsfileloader.cpp \
    scsfilewriter.cpp \
    scshighlightingrulespool.cpp \
    scsplugin.cpp \
    scswindow.cpp \
    scssyntaxhighlighter.cpp \
    scscodeeditor.cpp \
    scsstdhighlightingrule.cpp \
    scsmultilinecommenthighlightingrule.cpp \
    scsabstracthighlightingrule.cpp
