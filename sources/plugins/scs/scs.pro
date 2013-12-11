
TARGET        = $$qtLibraryTarget(scs)
TEMPLATE      = lib
INCLUDEPATH  += ../../kbe

DESTDIR = ../../bin/plugins

CONFIG       += plugin

OBJECTS_DIR = obj
MOC_DIR = moc

LIBS+= -lantlr3c

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
    scswindow.h \
    scsplugin.h \
    scscodeerroranalyzer.h \
    scserrortablewidget.h \
    scscodeeditor.h \
    scserrortablewidgetitem.h \
    scsfindwidget.h \
    scssyntaxhighlighter.h \
    scscodeanalyzer.h \
    scscodecompleter.h \
    antlr3treeparser.h \
    antlr3tokenstream.h \
    antlr3string.h \
    antlr3rewritestreams.h \
    antlr3recognizersharedstate.h \
    antlr3parsetree.h \
    antlr3parser.h \
    antlr3memory.h \
    antlr3lexer.h \
    antlr3intstream.h \
    antlr3interfaces.h \
    antlr3input.h \
    antlr3filestream.h \
    antlr3exception.h \
    antlr3errors.h \
    antlr3encodings.h \
    antlr3defs.h \
    antlr3debugeventlistener.h \
    antlr3cyclicdfa.h \
    antlr3convertutf.h \
    antlr3commontreenodestream.h \
    antlr3commontreeadaptor.h \
    antlr3commontree.h \
    antlr3commontoken.h \
    antlr3collections.h \
    antlr3bitset.h \
    antlr3basetreeadaptor.h \
    antlr3basetree.h \
    antlr3baserecognizer.h \
    antlr3.h


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
    scswindow.cpp \
    scserrortablewidget.cpp \
    scscodeeditor.cpp \
    scsfindwidget.cpp \
    scscodeerroranalyzer.cpp \
    scsplugin.cpp \
    scserrortablewidgetitem.cpp \
    scscodeanalyzer.cpp \
    scssyntaxhighlighter.cpp \
    scscodecompleter.cpp \
    antlr3treeparser.c \
    antlr3tokenstream.c \
    antlr3string.c \
    antlr3rewritestreams.c \
    antlr3parser.c \
    antlr3lexer.c \
    antlr3intstream.c \
    antlr3inputstream.c \
    antlr3filestream.c \
    antlr3exception.c \
    antlr3encodings.c \
    antlr3debughandlers.c \
    antlr3cyclicdfa.c \
    antlr3convertutf.c \
    antlr3commontreenodestream.c \
    antlr3commontreeadaptor.c \
    antlr3commontree.c \
    antlr3commontoken.c \
    antlr3collections.c \
    antlr3bitset.c \
    antlr3basetreeadaptor.c \
    antlr3basetree.c \
    antlr3baserecognizer.c


