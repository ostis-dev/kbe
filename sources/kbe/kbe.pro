# -------------------------------------------------
# Project created by QtCreator 2010-03-10T23:38:40
# -------------------------------------------------

DESTDIR = ../bin

CONFIG (debug, debug|release) {
        TARGET = kbe_d
} else {
        TARGET = kbe
}

TEMPLATE = app

SOURCES += readwritemanager.cpp \
    mainwindow.cpp \
    main.cpp \
    findwidget.cpp \
    extendedundoviewmodel.cpp \
    extendedundoview.cpp \
    extendedtabwidget.cpp \
    config.cpp \
    pluginmanager.cpp

HEADERS += version.h \
    readwritemanager.h \
    platform.h \
    mainwindow.h \
    findwidget.h \
    extendedundoviewmodel.h \
    extendedundoview.h \
    extendedtabwidget.h \
    config.h \
    interfaces/plugininterface.h \
    pluginmanager.h \
    interfaces/windowinterface.h \
    interfaces/filewriterinterface.h \
    interfaces/fileloaderinterface.h

FORMS += mainwindow.ui

TRANSLATIONS += translations/lang_en_EN.ts \
    translations/lang_ru_RU.ts
RC_FILE = kbe.rc
Debug:DEFINES += _DEBUG

OBJECTS_DIR = obj
MOC_DIR = moc
