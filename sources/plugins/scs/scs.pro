
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
    scscodeeditor.h \
    scsabstracthighlightingrule.h \
    scscodeanalyzer.h \
    scscodecompleter.h
    
SOURCES += \
    scswindow.cpp \
    scssyntaxhighlighter.cpp \
    scsstdhighlightingrule.cpp \
    scsplugin.cpp \
    scsmultilinecommenthighlightingrule.cpp \
    scshighlightingrulespool.cpp \
    scscodeeditor.cpp \
    scsabstracthighlightingrule.cpp \
    scscodeanalyzer.cpp \
    scscodecompleter.cpp

TRANSLATIONS += media/translations/scs_en_EN.ts \
                media/translations/scs_ru_RU.ts

lrelease.input         = TRANSLATIONS
lrelease.output        = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_IN_BASE}.qm
lrelease.commands      = $$[QT_INSTALL_BINS]/lrelease ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_IN_BASE}.qm
lrelease.CONFIG       += no_link target_predeps
QMAKE_EXTRA_COMPILERS += lrelease
