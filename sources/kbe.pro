# -------------------------------------------------
# Project created by QtCreator 2010-03-10T23:38:40
# -------------------------------------------------
QT += svg \
    xml \
    xmlpatterns # \

# phonon
TARGET = kbe
TEMPLATE = app
SOURCES += findwidget.cpp \
    main.cpp \
    config.cpp \
    mainwindow.cpp \
    extendedtabwidget.cpp \
    basewindow.cpp \
    scgwindow.cpp \
    scgscene.cpp \
    scgalphabet.cpp \
    scgview.cpp \
    pointgraphicsitem.cpp \
    scgobject.cpp \
    scgpointobject.cpp \
    scgnode.cpp \
    scgpair.cpp \
    scgbus.cpp \
    scgcontour.cpp \
    scgobjectsinfodata.cpp \
    scgobjectsinfo.cpp \
    readwritemanager.cpp \
    abstractfileloader.cpp \
    scgfileloadergwf.cpp \
    abstractfilewriter.cpp \
    gwfstreamwriter.cpp \
    gwfobjectinforeader.cpp \
    scgfilewritergwf.cpp \
    scgfilewriterimage.cpp \
    scgcontent.cpp \
    scgcontentfactory.cpp \
    scgcontentdialog.cpp \
    scgcontentviewer.cpp \
    scgcontentstring.cpp \
    scgcontentchangedialog.cpp \
    scgcontentimage.cpp \
    scgcontentnumeric.cpp \
    scgcommands.cpp \
    layoutmanager.cpp \
    scgobjectarrangers.cpp \
    event_handling/SCgInsertModeEventHandler.cpp \
    event_handling/SCgSelectModeEventHandler.cpp \
    event_handling/SCgPairModeEventHandler.cpp \
    event_handling/SCgEventHandler.cpp \
    event_handling/SCgContourModeEventHandler.cpp \
    event_handling/SCgBusModeEventHandler.cpp \
    scgminimap.cpp \
    extendedundoviewmodel.cpp \
    extendedundoview.cpp \
    scgtemplateobjectbuilder.cpp \
    scgdefaultobjectbuilder.cpp \
    scgabstractobjectbuilder.cpp \
    scgconfig.cpp \
    scgarranger.cpp
HEADERS += findwidget.h \
    platform.h \
    version.h \
    config.h \
    mainwindow.h \
    extendedtabwidget.h \
    basewindow.h \
    scgwindow.h \
    scgscene.h \
    scgalphabet.h \
    scgview.h \
    pointgraphicsitem.h \
    scgobject.h \
    scgpointobject.h \
    scgnode.h \
    scgpair.h \
    scgbus.h \
    scgcontour.h \
    scgobjectsinfodata.h \
    scgobjectsinfo.h \
    readwritemanager.h \
    abstractfileloader.h \
    scgfileloadergwf.h \
    abstractfilewriter.h \
    gwfstreamwriter.h \
    gwfobjectinforeader.h \
    scgfilewritergwf.h \
    scgfilewriterimage.h \
    scgcontent.h \
    scgcontentfactory.h \
    scgcontentdialog.h \
    scgcontentviewer.h \
    scgcontentstring.h \
    scgcontentchangedialog.h \
    scgcontentimage.h \
    scgcontentnumeric.h \
    scgcommands.h \
    layoutmanager.h \
    event_handling/SCgInsertModeEventHandler.h \
    event_handling/SCgSelectModeEventHandler.h \
    event_handling/SCgPairModeEventHandler.h \
    event_handling/SCgEventHandler.h \
    event_handling/SCgContourModeEventHandler.h \
    event_handling/SCgBusModeEventHandler.h \
    scgminimap.h \
    extendedundoviewmodel.h \
    extendedundoview.h \
    scgtemplateobjectbuilder.h \
    scgdefaultobjectbuilder.h \
    scgabstractobjectbuilder.h \
    scgconfig.h \
    scgarranger.h
FORMS += mainwindow.ui
TRANSLATIONS += translations/lang_en_EN.ts \
    translations/lang_ru_RU.ts
RC_FILE = kbe.rc
Debug:DEFINES += _DEBUG

OBJECTS_DIR = obj
MOC_DIR = moc
