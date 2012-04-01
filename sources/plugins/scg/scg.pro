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
    scgbus.h \
    scgalphabet.h \
    scgabstractobjectbuilder.h \
    pointgraphicsitem.h \
    scgtextitem.h \
    event_handling/SCgSelectModeEventHandler.h \
    event_handling/SCgPairModeEventHandler.h \
    event_handling/SCgInsertModeEventHandler.h \
    event_handling/SCgEventHandler.h \
    event_handling/SCgContourModeEventHandler.h \
    event_handling/SCgBusModeEventHandler.h \
    event_handling/SCgCloneModeEventHandler.h \
    gwf/gwfstreamwriter.h \
    gwf/gwfobjectinforeader.h \
    gwf/gwffilewriter.h \
    gwf/gwffileloader.h \
    scgplugin.h \
    scgfindwidget.h \
    scgundoviewmodel.h \
    scgundoview.h \
    commands/scgcommandselectedobjectmove.h \
    commands/scgcommandpointschange.h \
    commands/scgcommandpointmove.h \
    commands/scgcommandobjecttypechage.h \
    commands/scgcommandobjectmove.h \
    commands/scgcommandobjectidftchange.h \
    commands/scgcommandobjectdelete.h \
    commands/scgcommandinsert.h \
    commands/scgcommanddeletecontour.h \
    commands/scgcommandcreatepair.h \
    commands/scgcommandcreatenode.h \
    commands/scgcommandcreatecontour.h \
    commands/scgcommandcreatebus.h \
    commands/scgcommandcontentvisibility.h \
    commands/scgcommandcontentchange.h \
    commands/scgcommandclone.h \
    commands/scgcommandchangeincedentobject.h \
    commands/scgbasecommand.h \
    commands/scgcommandidtfmove.h \
    scgexportimage.h \
    arrangers/scgarrangervertical.h \
    arrangers/scgarrangertuple.h \
    arrangers/scgarrangerhorizontal.h \
    arrangers/scgarrangergrid.h \
    arrangers/scgarranger.h \
    select/scgselectinputoutput.h \
    select/scgselect.h \
    select/scgselectsubgraph.h

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
    scgbus.cpp \
    scgalphabet.cpp \
    scgabstractobjectbuilder.cpp \
    pointgraphicsitem.cpp \
    scgtextitem.cpp \
    event_handling/SCgSelectModeEventHandler.cpp \
    event_handling/SCgPairModeEventHandler.cpp \
    event_handling/SCgInsertModeEventHandler.cpp \
    event_handling/SCgEventHandler.cpp \
    event_handling/SCgContourModeEventHandler.cpp \
    event_handling/SCgBusModeEventHandler.cpp \
    event_handling/SCgCloneModeEventHandler.cpp \
    gwf/gwfstreamwriter.cpp \
    gwf/gwfobjectinforeader.cpp \
    gwf/gwffilewriter.cpp \
    gwf/gwffileloader.cpp \
    scgplugin.cpp \
    scgfindwidget.cpp \
    scgundoviewmodel.cpp \
    scgundoview.cpp \
    commands/scgcommandselectedobjectmove.cpp \
    commands/scgcommandpointschange.cpp \
    commands/scgcommandpointmove.cpp \
    commands/scgcommandobjecttypechange.cpp \
    commands/scgcommandobjectmove.cpp \
    commands/scgcommandobjectidtfchange.cpp \
    commands/scgcommandobjectdelete.cpp \
    commands/scgcommandinsert.cpp \
    commands/scgcommanddeletecontour.cpp \
    commands/scgcommandcreatepair.cpp \
    commands/scgcommandcreatecontour.cpp \
    commands/scgcommandcreatebus.cpp \
    commands/scgcommandcontentvisibility.cpp \
    commands/scgcommandcontentchange.cpp \
    commands/scgcommandclone.cpp \
    commands/scgcommandchangeincedentobject.cpp \
    commands/scgbasecommand.cpp \
    commands/scgcommandcreatenode.cpp \
    commands/scgcommandidtfmove.cpp \
    scgexportimage.cpp \
    arrangers/scgarrangervertical.cpp \
    arrangers/scgarrangertuple.cpp \
    arrangers/scgarrangerhorizontal.cpp \
    arrangers/scgarrangergrid.cpp \
    arrangers/scgarranger.cpp \
    select/scgselectinputoutput.cpp \
    select/scgselect.cpp \
    select/scgselectsubgraph.cpp


