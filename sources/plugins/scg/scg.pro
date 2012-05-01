QT += xml

TARGET        = $$qtLibraryTarget(scg)
TEMPLATE      = lib
INCLUDEPATH  += ../../kbe \
                ./

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
    scgpointgraphicsitem.h \
    scgtextitem.h \
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
    commands/scgcommandobjectmove.h \
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
    commands/scgcommandobjectidtfchange.h \
    commands/scgcommandobjecttypechange.h \
    scgexportimage.h \
    arrangers/scgarrangervertical.h \
    arrangers/scgarrangertuple.h \
    arrangers/scgarrangerhorizontal.h \
    arrangers/scgarrangergrid.h \
    arrangers/scgarranger.h \
    select/scgselectinputoutput.h \
    select/scgselect.h \
    select/scgselectsubgraph.h \
    modes/scgselectmode.h \
    modes/scgpairmode.h \
    modes/scgmode.h \
    modes/scginsertmode.h \
    modes/scgcontourmode.h \
    modes/scgclonemode.h \
    modes/scgbusmode.h \
    commands/scgcommandswappairorient.h

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
    scgpointgraphicsitem.cpp \
    scgtextitem.cpp \
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
    commands/scgcommandobjectmove.cpp \
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
    commands/scgcommandobjectidtfchange.cpp \
    commands/scgcommandobjecttypechange.cpp \
    scgexportimage.cpp \
    arrangers/scgarrangervertical.cpp \
    arrangers/scgarrangertuple.cpp \
    arrangers/scgarrangerhorizontal.cpp \
    arrangers/scgarrangergrid.cpp \
    arrangers/scgarranger.cpp \
    select/scgselectinputoutput.cpp \
    select/scgselect.cpp \
    select/scgselectsubgraph.cpp \
    modes/scgselectmode.cpp \
    modes/scgpairmode.cpp \
    modes/scgmode.cpp \
    modes/scginsertmode.cpp \
    modes/scgcontourmode.cpp \
    modes/scgclonemode.cpp \
    modes/scgbusmode.cpp \
    commands/scgcommandswappairorient.cpp

TRANSLATIONS += media/translations/scg_en_EN.ts \
                media/translations/scg_ru_RU.ts

lrelease.input         = TRANSLATIONS
lrelease.output        = ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_IN_BASE}.qm
lrelease.commands      = $$[QT_INSTALL_BINS]/lrelease ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_IN_PATH}/${QMAKE_FILE_IN_BASE}.qm
lrelease.CONFIG       += no_link target_predeps
QMAKE_EXTRA_COMPILERS += lrelease
