
TARGET        = $$qtLibraryTarget(scs)
TEMPLATE      = lib
INCLUDEPATH  += ../../kbe

DESTDIR = ../../bin/plugins

CONFIG       += plugin

OBJECTS_DIR = obj
MOC_DIR = moc



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
    highlightingrules/scshighlightingrulespool.h \
    highlightingrules/scsmultilinehighlightingrule.h \
    highlightingrules/scsabstracthighlightingrule.h \
    highlightingrules/scsstdhighlightingrule.h \
    scsparser/scsparserexception.h \
    scsparser/scsparserwrapper.h \
    scsparser/SCsCLexer.h \
    scsparser/SCsCParser.h \
    scsparser/scscparserdefs.h \
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
    highlightingrules/scshighlightingrulespool.cpp \
    highlightingrules/scsmultilinehighlightingrule.cpp \
    highlightingrules/scsstdhighlightingrule.cpp \
    highlightingrules/scsabstracthighlightingrule.cpp \
    scsparser/scsparserwrapper.cpp \
    scsparser/scsparserexception.cpp \
    scsparser/SCsCLexer.c \
    scsparser/SCsCParser.c \
    scsparser/scscparserdefs.c \
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

LIBS+= -lantlr3c
