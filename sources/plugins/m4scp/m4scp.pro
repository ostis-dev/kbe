
TARGET        = $$qtLibraryTarget(m4scp)
TEMPLATE      = lib
INCLUDEPATH  += ../../kbe

DESTDIR = ../../bin/plugins

CONFIG       += plugin

OBJECTS_DIR = obj
MOC_DIR = moc


HEADERS += \
    m4scpwindow.h \
    m4scpsyntaxhighlighter.h \
    m4scpsyntax.h \
    m4scpfilewriter.h \
    m4scpfileloader.h \
    m4scpcodeeditor.h \
    m4scpcodecompleter.h \
    m4scpplugin.h

SOURCES += \
    m4scpwindow.cpp \
    m4scpsyntaxhighlighter.cpp \
    m4scpsyntax.cpp \
    m4scpfilewriter.cpp \
    m4scpfileloader.cpp \
    m4scpcodeeditor.cpp \
    m4scpcodecompleter.cpp \
    m4scpplugin.cpp
