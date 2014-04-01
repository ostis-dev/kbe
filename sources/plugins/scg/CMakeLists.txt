set (PROJECT scg)

set (SCG_DIR ${PLUGINS_DIR}/scg)
set (SCG_MEDIA_DIR ${SCG_DIR}/media)

set (HEADERS
    scgwindow.h
    scgview.h
    scgtemplateobjectbuilder.h
    scgscene.h
    scgpointobject.h
    scgpair.h
    scgobjectsinfodata.h
    scgobjectsinfo.h
    scgobject.h
    scgnode.h
    scgminimap.h
    scglayoutmanager.h
    scgfilewriterimage.h
    scgdefaultobjectbuilder.h
    scgcontour.h
    scgcontentviewer.h
    scgcontentstring.h
    scgcontentnumeric.h
    scgcontentimage.h
    scgcontentfactory.h
    scgcontentdialog.h
    scgcontentchangedialog.h
    scgcontent.h
    scgconfig.h
    scgbus.h
    scgalphabet.h
    scgabstractobjectbuilder.h
    scgpointgraphicsitem.h
    scgtextitem.h
    gwf/gwfstreamwriter.h
    gwf/gwfobjectinforeader.h
    gwf/gwffilewriter.h
    gwf/gwffileloader.h
    scgplugin.h
    scgfindwidget.h
    scgundoviewmodel.h
    scgundoview.h
    commands/scgcommandselectedobjectmove.h
    commands/scgcommandpointschange.h
    commands/scgcommandpointmove.h
    commands/scgcommandobjectmove.h
    commands/scgcommandobjectdelete.h
    commands/scgcommandinsert.h
    commands/scgcommanddeletecontour.h
    commands/scgcommandcreatepair.h
    commands/scgcommandcreatenode.h
    commands/scgcommandcreatecontour.h
    commands/scgcommandcreatebus.h
    commands/scgcommandcontentvisibility.h
    commands/scgcommandcontentchange.h
    commands/scgcommandclone.h
    commands/scgcommandchangeincedentobject.h
    commands/scgbasecommand.h
    commands/scgcommandidtfmove.h
    commands/scgcommandobjectidtfchange.h
    commands/scgcommandobjecttypechange.h
    scgexportimage.h
    arrangers/scgarrangervertical.h
    arrangers/scgarrangertuple.h
    arrangers/scgarrangerhorizontal.h
    arrangers/scgarrangergrid.h
    arrangers/scgarranger.h
    select/scgselectinputoutput.h
    select/scgselect.h
    select/scgselectsubgraph.h
    modes/scgselectmode.h
    modes/scgpairmode.h
    modes/scgmode.h
    modes/scginsertmode.h
    modes/scgcontourmode.h
    modes/scgclonemode.h
    modes/scgbusmode.h
    commands/scgcommandswappairorient.h
    arrangers/scgarrangerenergybased.h
    commands/scgcommandremovebreakpoints.h
    commands/scgcommandminimizecontour.h
    arrangers/scgforcecalculator.h
    scgnodetextitem.h
)

set (SOURCES
    scgwindow.cpp
    scgview.cpp
    scgtemplateobjectbuilder.cpp
    scgscene.cpp
    scgpointobject.cpp
    scgpair.cpp
    scgobjectsinfodata.cpp
    scgobjectsinfo.cpp
    scgobject.cpp
    scgnode.cpp
    scgminimap.cpp
    scglayoutmanager.cpp
    scgfilewriterimage.cpp
    scgdefaultobjectbuilder.cpp
    scgcontour.cpp
    scgcontentviewer.cpp
    scgcontentstring.cpp
    scgcontentnumeric.cpp
    scgcontentimage.cpp
    scgcontentfactory.cpp
    scgcontentdialog.cpp
    scgcontentchangedialog.cpp
    scgcontent.cpp
    scgconfig.cpp
    scgbus.cpp
    scgalphabet.cpp
    scgabstractobjectbuilder.cpp
    scgpointgraphicsitem.cpp
    scgtextitem.cpp
    gwf/gwfstreamwriter.cpp
    gwf/gwfobjectinforeader.cpp
    gwf/gwffilewriter.cpp
    gwf/gwffileloader.cpp
    scgplugin.cpp
    scgfindwidget.cpp
    scgundoviewmodel.cpp
    scgundoview.cpp
    commands/scgcommandselectedobjectmove.cpp
    commands/scgcommandpointschange.cpp
    commands/scgcommandpointmove.cpp
    commands/scgcommandobjectmove.cpp
    commands/scgcommandobjectdelete.cpp
    commands/scgcommandinsert.cpp
    commands/scgcommanddeletecontour.cpp
    commands/scgcommandcreatepair.cpp
    commands/scgcommandcreatecontour.cpp
    commands/scgcommandcreatebus.cpp
    commands/scgcommandcontentvisibility.cpp
    commands/scgcommandcontentchange.cpp
    commands/scgcommandclone.cpp
    commands/scgcommandchangeincedentobject.cpp
    commands/scgbasecommand.cpp
    commands/scgcommandcreatenode.cpp
    commands/scgcommandidtfmove.cpp
    commands/scgcommandobjectidtfchange.cpp
    commands/scgcommandobjecttypechange.cpp
    scgexportimage.cpp
    arrangers/scgarrangervertical.cpp
    arrangers/scgarrangertuple.cpp
    arrangers/scgarrangerhorizontal.cpp
    arrangers/scgarrangergrid.cpp
    arrangers/scgarranger.cpp
    select/scgselectinputoutput.cpp
    select/scgselect.cpp
    select/scgselectsubgraph.cpp
    modes/scgselectmode.cpp
    modes/scgpairmode.cpp
    modes/scgmode.cpp
    modes/scginsertmode.cpp
    modes/scgcontourmode.cpp
    modes/scgclonemode.cpp
    modes/scgbusmode.cpp
    commands/scgcommandswappairorient.cpp
    arrangers/scgarrangerenergybased.cpp
    commands/scgcommandremovebreakpoints.cpp
    commands/scgcommandminimizecontour.cpp
    arrangers/scgforcecalculator.cpp
    scgnodetextitem.cpp
)

set (RESOURCES
    scg.qrc
    )

set (TRANSLATIONS
    ${SCG_MEDIA_DIR}/translations/scg_en_EN.ts
    ${SCG_MEDIA_DIR}/translations/scg_ru_RU.ts
    )

project (${PROJECT})

FOREACH (TRANSLATION ${TRANSLATIONS})
    execute_process(COMMAND lrelease-qt4 ${TRANSLATION})
ENDFOREACH(TRANSLATION)

include_directories(./)
include_directories(${PROJECT_ROOT_DIR}/kbe)

include (${QT_USE_FILE})
qt4_add_resources (QRC_SOURCES ${RESOURCES})
qt4_wrap_cpp (MOC_SOURCES ${HEADERS})

if (MSVC)
    add_definitions (/W3)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions (-Wall)
else ()
    message ("Unknown compiler")
endif ()

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})
source_group ("Generated Files" FILES ${MOC_SOURCES})
source_group ("Resource Files" FILES ${QRC_SOURCES})
 
add_library (${PROJECT} ${HEADERS} ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES})

target_link_libraries (${PROJECT} ${QT_LIBRARIES})
