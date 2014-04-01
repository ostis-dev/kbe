set (PROJECT m4scp)

set (M4SCP_DIR ${PLUGINS_DIR}/m4scp)
set (M4SCP_MEDIA_DIR ${M4SCP_DIR}/media)

set (HEADERS
    m4scpwindow.h
    m4scpsyntaxhighlighter.h
    m4scpsyntax.h
    m4scpcodeeditor.h
    m4scpcodecompleter.h
    m4scpplugin.h
    m4scpcodeanalyzer.h
    m4scpblockdata.h
)

set (SOURCES
    m4scpwindow.cpp
    m4scpsyntaxhighlighter.cpp
    m4scpsyntax.cpp
    m4scpcodeeditor.cpp
    m4scpcodecompleter.cpp
    m4scpplugin.cpp
    m4scpcodeanalyzer.cpp
)

set (RESOURCES
    m4scp.qrc
    )

set (TRANSLATIONS
    ${M4SCP_MEDIA_DIR}/translations/m4scp_en_EN.ts
    ${M4SCP_MEDIA_DIR}/translations/m4scp_ru_RU.ts
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
