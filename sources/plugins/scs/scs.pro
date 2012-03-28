
TARGET        = $$qtLibraryTarget(scs)
TEMPLATE      = lib
INCLUDEPATH  += ../../kbe

DESTDIR = ../../bin/plugins

CONFIG       += plugin

OBJECTS_DIR = obj
MOC_DIR = moc


HEADERS += \
    scswindow.h \
    scssyntaxhighlighter.h \
    scsstdhighlightingrule.h \
    scsplugin.h \
    scsmultilinecommenthighlightingrule.h \
    scshighlightingrulespool.h \
    scsfilewriter.h \
    scsfileloader.h \
    scscodeeditor.h \
    scsabstracthighlightingrule.h

SOURCES += \
    scswindow.cpp \
    scssyntaxhighlighter.cpp \
    scsstdhighlightingrule.cpp \
    scsplugin.cpp \
    scsmultilinecommenthighlightingrule.cpp \
    scshighlightingrulespool.cpp \
    scsfilewriter.cpp \
    scsfileloader.cpp \
    scscodeeditor.cpp \
    scsabstracthighlightingrule.cpp
