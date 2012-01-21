cmake_minimum_required (VERSION 2.6)
 
set (PROJECT 
    kbe)

set (KBE_HDRS 
    ./sources/abstractfileloader.h
    ./sources/abstractfilewriter.h
    ./sources/basewindow.h
    ./sources/config.h
    ./sources/extendedtabwidget.h
    ./sources/extendedundoview.h
    ./sources/extendedundoviewmodel.h
    ./sources/findwidget.h
    ./sources/gwfobjectinforeader.h
    ./sources/gwfstreamwriter.h
    ./sources/layoutmanager.h
    ./sources/mainwindow.h
    ./sources/platform.h
    ./sources/pointgraphicsitem.h
    ./sources/readwritemanager.h
    ./sources/scgabstractobjectbuilder.h
    ./sources/scgalphabet.h
    ./sources/scgarranger.h
    ./sources/scgbus.h
    ./sources/scgcommands.h
    ./sources/scgconfig.h
    ./sources/scgcontent.h
    ./sources/scgcontentchangedialog.h
    ./sources/scgcontentdialog.h
    ./sources/scgcontentfactory.h
    ./sources/scgcontentimage.h
    ./sources/scgcontentnumeric.h
    ./sources/scgcontentstring.h
    ./sources/scgcontentviewer.h
    ./sources/scgcontour.h
    ./sources/scgdefaultobjectbuilder.h
    ./sources/scgfileloadergwf.h
    ./sources/scgfilewritergwf.h
    ./sources/scgfilewriterimage.h
    ./sources/scgminimap.h
    ./sources/scgnode.h
    ./sources/scgobject.h
    ./sources/scgobjectsinfo.h
    ./sources/scgobjectsinfodata.h
    ./sources/scgpair.h
    ./sources/scgpointobject.h
    ./sources/scgscene.h
    ./sources/scgtemplateobjectbuilder.h
    ./sources/scgview.h
    ./sources/scgwindow.h
    ./sources/ui_mainwindow.h
    ./sources/version.h
    ./sources/event_handling/SCgInsertModeEventHandler.h
    ./sources/event_handling/SCgSelectModeEventHandler.h
    ./sources/event_handling/SCgPairModeEventHandler.h
    ./sources/event_handling/SCgEventHandler.h
    ./sources/event_handling/SCgContourModeEventHandler.h
    ./sources/event_handling/SCgBusModeEventHandler.h
    )
 
set (KBE_SRSC
    ./sources/abstractfileloader.cpp
    ./sources/abstractfilewriter.cpp
    ./sources/basewindow.cpp
    ./sources/config.cpp
    ./sources/extendedtabwidget.cpp
    ./sources/extendedundoview.cpp
    ./sources/extendedundoviewmodel.cpp
    ./sources/findwidget.cpp
    ./sources/gwfobjectinforeader.cpp
    ./sources/gwfstreamwriter.cpp
    ./sources/layoutmanager.cpp
    ./sources/mainwindow.cpp
    ./sources/main.cpp
    ./sources/pointgraphicsitem.cpp
    ./sources/readwritemanager.cpp
    ./sources/scgabstractobjectbuilder.cpp
    ./sources/scgalphabet.cpp
    ./sources/scgarranger.cpp
    ./sources/scgbus.cpp
    ./sources/scgcommands.cpp
    ./sources/scgconfig.cpp
    ./sources/scgcontent.cpp
    ./sources/scgcontentchangedialog.cpp
    ./sources/scgcontentdialog.cpp
    ./sources/scgcontentfactory.cpp
    ./sources/scgcontentimage.cpp
    ./sources/scgcontentnumeric.cpp
    ./sources/scgcontentstring.cpp
    ./sources/scgcontentviewer.cpp
    ./sources/scgcontour.cpp
    ./sources/scgdefaultobjectbuilder.cpp
    ./sources/scgfileloadergwf.cpp
    ./sources/scgfilewritergwf.cpp
    ./sources/scgfilewriterimage.cpp
    ./sources/scgminimap.cpp
    ./sources/scgnode.cpp
    ./sources/scgobject.cpp
    ./sources/scgobjectsinfo.cpp
    ./sources/scgobjectsinfodata.cpp
    ./sources/scgpair.cpp
    ./sources/scgpointobject.cpp
    ./sources/scgscene.cpp
    ./sources/scgtemplateobjectbuilder.cpp
    ./sources/scgview.cpp
    ./sources/scgwindow.cpp
    ./sources/event_handling/SCgInsertModeEventHandler.cpp
    ./sources/event_handling/SCgSelectModeEventHandler.cpp
    ./sources/event_handling/SCgPairModeEventHandler.cpp
    ./sources/event_handling/SCgEventHandler.cpp
    ./sources/event_handling/SCgContourModeEventHandler.cpp
    ./sources/event_handling/SCgBusModeEventHandler.cpp
    )

set (KBE_UI_FORMS
    ./sources/mainwindow.ui
    )

set (KBE_ALL_SRSC
    ${KBE_SRSC}
    ${KBE_UI_FORMS}
    )

set (KBE_TRANSLATIONS
    ./sources/translations/lang_en_EN.ts
	./sources/translations/lang_ru_RU.ts
    )

project (${PROJECT})
 
include_directories (./)

set (WIN_RESOURCE ./sources/kbe.rc)
 
find_package (Qt4 COMPONENTS QtCore QtGui QtMain QtXml QtSvg Phonon REQUIRED)

include (${QT_USE_FILE})
qt4_wrap_ui (SAMPLE_UI_HDRS ${KBE_UI_FORMS})
qt4_wrap_cpp (MOC_SOURCES ${KBE_HDRS})

option (FIM_WITHOUT_I18N "Do not use language tool (for debugging)" OFF)

if (NOT FIM_WITHOUT_I18N)

option (FIM_UPDATE_TRANSLATIONS "Update translations (*.ts files)" OFF)

if (FIM_UPDATE_TRANSLATIONS)
    QT4_CREATE_TRANSLATION(QM_FILES ${KBE_ALL_SRSC} ${KBE_TRANSLATIONS} OPTIONS -no-obsolete)
    message("Updating *.ts files")
else (FIM_UPDATE_TRANSLATIONS)
      QT4_ADD_TRANSLATION(QM_FILES ${KBE_TRANSLATIONS})
      message("Using existing *.ts files")
endif (FIM_UPDATE_TRANSLATIONS)

endif (NOT FIM_WITHOUT_I18N)

add_definitions (-Wall)

source_group ("Header Files" FILES ${KBE_HDRS})
source_group ("Source Files" FILES ${KBE_ALL_SRSC})
source_group ("Generated Files" FILES ${MOC_SOURCES} ${QM_FILES})
 
if (WIN32)
add_executable (${PROJECT} 
                ${KBE_HDRS} 
                ${MOC_SOURCES} 
                ${KBE_ALL_SRSC}
                ${QM_FILES}
                ${WIN_RESOURCE}
                )
else (WIN32)
add_executable (${PROJECT} 
                ${KBE_HDRS} 
                ${MOC_SOURCES} 
                ${KBE_ALL_SRSC}
                ${QM_FILES}
                )
endif (WIN32)

target_link_libraries (${PROJECT} ${QT_LIBRARIES})

file (COPY ./sources/media DESTINATION ${CMAKE_BINARY_DIR})

IF (WIN32)
	add_custom_command (TARGET kbe COMMAND 
		if not exist $(TargetDir)media\\lang\\ mkdir $(TargetDir)media\\lang\\)

	foreach(FILENAME ${QM_FILES})
		add_custom_command(TARGET kbe 
            COMMAND copy \"${FILENAME}\" $(TargetDir)media\\lang\\)
        add_custom_command(TARGET kbe 
            COMMAND del \"${FILENAME}\")
	endforeach(FILENAME)
ELSE (WIN32)
    add_custom_command (TARGET kbe COMMAND
        mkdir $(TargetDir)media/lang/)
    foreach(FILENAME ${QM_FILES})
        add_custom_command(TARGET kbe 
            COMMAND cp ${FILENAME} $(TargetDir)media/lang/)
        add_custom_command(TARGET kbe 
            COMMAND rm ${FILENAME})
    endforeach(FILENAME)
ENDIF (WIN32)
