set (PROJECT kbe)

set(KBE_DIR ${PROJECT_ROOT_DIR}/kbe)
set(KBE_MEDIA_DIR ${KBE_DIR}/media)

set(KBE_SRCS
    basewindow.cpp
    config.cpp
    extendedtabwidget.cpp
    main.cpp
    mainwindow.cpp
    pluginmanager.cpp
)

set(KBE_HDRS
    basewindow.h
    config.h
    extendedtabwidget.h
    mainwindow.h
    platform.h
    pluginmanager.h
    version.h
)

set(KBE_MOC_HDRS
    basewindow.h
    extendedtabwidget.h
    mainwindow.h
    pluginmanager.h
)

set (KBE_UI_FORMS
    mainwindow.ui
    )

set (KBE_ALL_SRCS
    ${KBE_SRCS}
    ${KBE_UI_FORMS}
    )

set (KBE_TRANSLATIONS
    ${KBE_MEDIA_DIR}/translations/lang_en_EN.ts
    ${KBE_MEDIA_DIR}/translations/lang_ru_RU.ts
    )

project (${PROJECT})
 
include_directories (./)

 
find_package (Qt4 COMPONENTS QtCore QtGui QtMain QtXml REQUIRED) #Phonon

include (${QT_USE_FILE})
qt4_wrap_ui (SAMPLE_UI_HDRS ${KBE_UI_FORMS})
qt4_wrap_cpp (MOC_SOURCES ${KBE_MOC_HDRS})

option (FIM_WITHOUT_I18N "Do not use language tool (for debugging)" OFF)

if (NOT FIM_WITHOUT_I18N)

option (FIM_UPDATE_TRANSLATIONS "Update translations (*.ts files)" OFF)

if (FIM_UPDATE_TRANSLATIONS)
    QT4_CREATE_TRANSLATION(QM_FILES ${KBE_ALL_SRCS} ${KBE_TRANSLATIONS} OPTIONS -no-obsolete)
    message("Updating *.ts files")
else (FIM_UPDATE_TRANSLATIONS)
      QT4_ADD_TRANSLATION(QM_FILES ${KBE_TRANSLATIONS})
      message("Using existing *.ts files")
endif (FIM_UPDATE_TRANSLATIONS)

endif (NOT FIM_WITHOUT_I18N)

add_definitions (-Wall)

source_group ("Header Files" FILES ${KBE_HDRS})
source_group ("Source Files" FILES ${KBE_ALL_SRCS})
source_group ("Generated Files" FILES ${MOC_SOURCES} ${QM_FILES})
 
if (WIN32)
add_executable (${PROJECT} 
                ${KBE_HDRS} 
                ${MOC_SOURCES} 
                ${KBE_ALL_SRCS}
                ${QM_FILES}
                kbe.rc
                )
else (WIN32)
add_executable (${PROJECT} 
                ${KBE_HDRS} 
                ${MOC_SOURCES} 
                ${KBE_ALL_SRCS}
                ${QM_FILES}
                )
endif (WIN32)

target_link_libraries (${PROJECT} ${QT_LIBRARIES})

#file (COPY ./sources/media DESTINATION ${CMAKE_BINARY_DIR})

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
        mkdir ${KBE_MEDIA_DIR}/lang/)
    foreach(FILENAME ${QM_FILES})
        add_custom_command(TARGET kbe 
            COMMAND cp ${FILENAME} ${KBE_MEDIA_DIR}/lang/)
        add_custom_command(TARGET kbe 
            COMMAND rm ${FILENAME})
    endforeach(FILENAME)

ENDIF (WIN32)
