# -------------------------------------------------
# Project created by QtCreator 2010-03-10T23:38:40
# -------------------------------------------------

DESTDIR = ../bin

CONFIG(debug, debug|release) {
    TARGET = kbe_d
    DEFINES += _DEBUG
} else {
    TARGET = kbe
}

TEMPLATE = app

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    extendedtabwidget.cpp \
    config.cpp \
    pluginmanager.cpp \
    guidedialog.cpp

HEADERS += version.h \
    platform.h \
    mainwindow.h \
    extendedtabwidget.h \
    config.h \
    interfaces/plugininterface.h \
    pluginmanager.h \
    interfaces/editorinterface.h \
    guidedialog.h

FORMS += mainwindow.ui

RESOURCES     = kbe.qrc

TRANSLATIONS += media/translations/lang_en_EN.ts \
                media/translations/lang_ru_RU.ts

RC_FILE = kbe.rc
#Debug:DEFINES += _DEBUG

OBJECTS_DIR = obj
MOC_DIR = moc
