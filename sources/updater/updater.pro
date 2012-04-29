QT       += core gui network xml

DESTDIR = ../bin


CONFIG(debug, debug|release) {
    TARGET = updater_d
    DEFINES += _DEBUG
} else {
    TARGET = updater
}

TEMPLATE = app

OBJECTS_DIR = obj
MOC_DIR = moc

SOURCES += \
    main.cpp \
    updatewindow.cpp \
    updateinstaller.cpp \
    updatedownloader.cpp \
    updateextractor.cpp

HEADERS += \
    updatewindow.h \
    updateinstaller.h \
    updatedownloader.h \
    updateextractor.h
