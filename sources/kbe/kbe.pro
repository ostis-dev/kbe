# -------------------------------------------------
# Project created by QtCreator 2010-03-10T23:38:40
# -------------------------------------------------
QT += core

# phonon
TARGET = kbe
TEMPLATE = app

SOURCES += readwritemanager.cpp \
    mainwindow.cpp \
    main.cpp \
    findwidget.cpp \
    extendedundoviewmodel.cpp \
    extendedundoview.cpp \
    extendedtabwidget.cpp \
    config.cpp \

HEADERS += version.h \
    readwritemanager.h \
    platform.h \
    mainwindow.h \
    findwidget.h \
    extendedundoviewmodel.h \
    extendedundoview.h \
    extendedtabwidget.h \
    config.h \
    interfaces/abstractfilewriter.h \
    interfaces/abstractfileloader.h

FORMS += mainwindow.ui

TRANSLATIONS += translations/lang_en_EN.ts \
    translations/lang_ru_RU.ts
RC_FILE = kbe.rc
Debug:DEFINES += _DEBUG

OBJECTS_DIR = obj
MOC_DIR = moc
