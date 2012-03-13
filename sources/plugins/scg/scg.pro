QT += xml

TARGET        = $$qtLibraryTarget(scg)
TEMPLATE      = lib
INCLUDEPATH  += ../../kbe

DESTDIR = ../../bin/plugins

CONFIG       += plugin

OBJECTS_DIR = obj
MOC_DIR = moc

RESOURCES     = scg.qrc

HEADERS += \
    scgwindow.h \
    scgview.h \
    scgtemplateobjectbuilder.h \
    scgscene.h \
    scgpointobject.h \
    scgpair.h \
    scgobjectsinfodata.h \
    scgobjectsinfo.h \
    scgobject.h \
    scgnode.h \
    scgminimap.h \
    scglayoutmanager.h \
    scgfilewriterimage.h \
    scgdefaultobjectbuilder.h \
    scgcontour.h \
    scgcontentviewer.h \
    scgcontentstring.h \
    scgcontentnumeric.h \
    scgcontentimage.h \
    scgcontentfactory.h \
    scgcontentdialog.h \
    scgcontentchangedialog.h \
    scgcontent.h \
    scgconfig.h \
    scgcommands.h \
    scgbus.h \
    scgarrangervertical.h \
    scgarrangertuple.h \
    scgarrangerhorizontal.h \
    scgarrangergrid.h \
    scgarranger.h \
    scgalphabet.h \
    scgabstractobjectbuilder.h \
    pointgraphicsitem.h \
    event_handling/SCgSelectModeEventHandler.h \
    event_handling/SCgPairModeEventHandler.h \
    event_handling/SCgInsertModeEventHandler.h \
    event_handling/SCgEventHandler.h \
    event_handling/SCgContourModeEventHandler.h \
    event_handling/SCgBusModeEventHandler.h \
    gwf/gwfstreamwriter.h \
    gwf/gwfobjectinforeader.h \
    gwf/gwffilewriter.h \
    gwf/gwffileloader.h \
    scgplugin.h \
    scgfindwidget.h \
    scgundoviewmodel.h \
    scgundoview.h \
    event_handling/SCgCloneModeEventHandler.h

SOURCES += \
    scgwindow.cpp \
    scgview.cpp \
    scgtemplateobjectbuilder.cpp \
    scgscene.cpp \
    scgpointobject.cpp \
    scgpair.cpp \
    scgobjectsinfodata.cpp \
    scgobjectsinfo.cpp \
    scgobject.cpp \
    scgnode.cpp \
    scgminimap.cpp \
    scglayoutmanager.cpp \
    scgfilewriterimage.cpp \
    scgdefaultobjectbuilder.cpp \
    scgcontour.cpp \
    scgcontentviewer.cpp \
    scgcontentstring.cpp \
    scgcontentnumeric.cpp \
    scgcontentimage.cpp \
    scgcontentfactory.cpp \
    scgcontentdialog.cpp \
    scgcontentchangedialog.cpp \
    scgcontent.cpp \
    scgconfig.cpp \
    scgcommands.cpp \
    scgbus.cpp \
    scgarrangervertical.cpp \
    scgarrangertuple.cpp \
    scgarrangerhorizontal.cpp \
    scgarrangergrid.cpp \
    scgarranger.cpp \
    scgalphabet.cpp \
    scgabstractobjectbuilder.cpp \
    pointgraphicsitem.cpp \
    event_handling/SCgSelectModeEventHandler.cpp \
    event_handling/SCgPairModeEventHandler.cpp \
    event_handling/SCgInsertModeEventHandler.cpp \
    event_handling/SCgEventHandler.cpp \
    event_handling/SCgContourModeEventHandler.cpp \
    event_handling/SCgBusModeEventHandler.cpp \
    gwf/gwfstreamwriter.cpp \
    gwf/gwfobjectinforeader.cpp \
    gwf/gwffilewriter.cpp \
    gwf/gwffileloader.cpp \
    scgplugin.cpp \
    scgfindwidget.cpp \
    scgundoviewmodel.cpp \
    scgundoview.cpp \
    event_handling/SCgCloneModeEventHandler.cpp


