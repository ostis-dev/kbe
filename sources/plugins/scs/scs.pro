QT += concurrent widgets

TARGET        = $$qtLibraryTarget(scs)
TEMPLATE      = lib
INCLUDEPATH  += ../../kbe

DESTDIR = ../../bin/plugins

CONFIG       += plugin

OBJECTS_DIR = obj
MOC_DIR = moc

unix {
    LIBS+= -lantlr3c
}

win32 {
    DEFINES +=  _XKEYCHECK_H

    INCLUDEPATH += $$PWD/../../../depends/antlr3c/
    !contains(QMAKE_TARGET.arch, x86_64) {
        LIBS += -l$$PWD/../../../depends/antlr3c/antlr3c_x86
    } else {
        LIBS += -l$$PWD/../../../depends/antlr3c/antlr3c_x86_64
    }
}

TRANSLATIONS += media/translations/scs_en_EN.ts \
                media/translations/scs_ru_RU.ts

lrelease.input         = TRANSLATIONS
lrelease.output        = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_IN_BASE}.qm
lrelease.commands      = $$[QT_INSTALL_BINS]/lrelease ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_IN_BASE}.qm
lrelease.CONFIG       += no_link target_predeps
QMAKE_EXTRA_COMPILERS += lrelease

RESOURCES += scs.qrc

INCLUDEPATH += \
    scsparser \
    highlightingrules

HEADERS += \
    highlightingrules/scsstdhighlightingrule.h \
    highlightingrules/scsmultilinehighlightingrule.h \
    highlightingrules/scsmultilinecommenthighlightingrule.h \
    highlightingrules/scshighlightingrulespool.h \
    highlightingrules/scsabstracthighlightingrule.h \
    scsparser/scsparserexception.h \
    scsparser/scsparserwrapper.h \
    scsparser/SCsCLexer.h \
    scsparser/SCsCParser.h \
    scsparser/scscparserdefs.h \
    scsparser/scsasynchparser.h \
    scswindow.h \
    scsplugin.h \
    scscodeerroranalyzer.h \
    scserrortablewidget.h \
    scscodeeditor.h \
    scserrortablewidgetitem.h \
    scsfindwidget.h \
    scssyntaxhighlighter.h \
    scscodeanalyzer.h \
    scscodecompleter.h


SOURCES += \
    highlightingrules/scsstdhighlightingrule.cpp \
    highlightingrules/scsmultilinehighlightingrule.cpp \
    highlightingrules/scsmultilinecommenthighlightingrule.cpp \
    highlightingrules/scshighlightingrulespool.cpp \
    highlightingrules/scsabstracthighlightingrule.cpp \
    scsparser/scsparserwrapper.cpp \
    scsparser/scsparserexception.cpp \
    scsparser/SCsCLexer.c \
    scsparser/SCsCParser.c \
    scsparser/scscparserdefs.c \
    scsparser/scsasynchparser.cpp \
    scswindow.cpp \
    scserrortablewidget.cpp \
    scscodeeditor.cpp \
    scsfindwidget.cpp \
    scscodeerroranalyzer.cpp \
    scsplugin.cpp \
    scserrortablewidgetitem.cpp \
    scscodeanalyzer.cpp \
    scssyntaxhighlighter.cpp \
    scscodecompleter.cpp

OTHER_FILES += \
    scsplugin.json


