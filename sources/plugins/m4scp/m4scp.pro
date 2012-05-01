
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
    m4scpcodeeditor.h \
    m4scpcodecompleter.h \
    m4scpplugin.h \
    m4scpcodeanalyzer.h \
    m4scpblockdata.h

SOURCES += \
    m4scpwindow.cpp \
    m4scpsyntaxhighlighter.cpp \
    m4scpsyntax.cpp \
    m4scpcodeeditor.cpp \
    m4scpcodecompleter.cpp \
    m4scpplugin.cpp \
    m4scpcodeanalyzer.cpp

RESOURCES += \
    m4scp.qrc

TRANSLATIONS += media/translations/m4scp_en_EN.ts \
                media/translations/m4scp_ru_RU.ts

lrelease.input         = TRANSLATIONS
lrelease.output        = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_IN_BASE}.qm
lrelease.commands      = $$[QT_INSTALL_BINS]/lrelease ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_IN_BASE}.qm
lrelease.CONFIG       += no_link target_predeps
QMAKE_EXTRA_COMPILERS += lrelease
