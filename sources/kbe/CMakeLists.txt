set (PROJECT kbe)

set (KBE_DIR ${PROJECT_ROOT_DIR}/kbe)
set (KBE_MEDIA_DIR ${KBE_DIR}/media)

set (HEADERS
    version.h
    platform.h
    mainwindow.h
    extendedtabwidget.h
    config.h
    interfaces/plugininterface.h
    pluginmanager.h
    interfaces/editorinterface.h
    guidedialog.h
    newfiledialog.h
)

set (SOURCES
    mainwindow.cpp
    main.cpp
    extendedtabwidget.cpp
    config.cpp
    pluginmanager.cpp
    guidedialog.cpp
    newfiledialog.cpp
)

set (FORMS
    mainwindow.ui
    )

set (RESOURCES
    kbe.qrc
    )

set (RC_FILE
    kbe.rc
    )

set (TRANSLATIONS
    ${KBE_MEDIA_DIR}/translations/lang_en_EN.ts
    ${KBE_MEDIA_DIR}/translations/lang_ru_RU.ts
    )

project (${PROJECT})

FOREACH (TRANSLATION ${TRANSLATIONS})
    execute_process(COMMAND lrelease-qt4 ${TRANSLATION})
ENDFOREACH(TRANSLATION)
 
include_directories(./)

include (${QT_USE_FILE})
qt4_add_resources (QRC_SOURCES ${RESOURCES})
qt4_wrap_ui (UI_HEADERS ${FORMS})
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
 
if (WIN32)
    add_executable (${PROJECT} ${HEADERS} ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES} ${RC_FILE})
else (WIN32)
    add_executable (${PROJECT} ${HEADERS} ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES})
endif (WIN32)

target_link_libraries (${PROJECT} ${QT_LIBRARIES})
