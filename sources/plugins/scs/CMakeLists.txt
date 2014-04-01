set (PROJECT scs)

set (SCS_DIR ${PLUGINS_DIR}/scs)
set (SCS_MEDIA_DIR ${SCS_DIR}/media)

set (HEADERS
    highlightingrules/scsstdhighlightingrule.h
    highlightingrules/scsmultilinehighlightingrule.h
    highlightingrules/scsmultilinecommenthighlightingrule.h
    highlightingrules/scshighlightingrulespool.h
    highlightingrules/scsabstracthighlightingrule.h
    scsparser/scsparserexception.h
    scsparser/scsparserwrapper.h
    scsparser/SCsCLexer.h
    scsparser/SCsCParser.h
    scsparser/scscparserdefs.h
    scsparser/scsasynchparser.h
    scswindow.h
    scsplugin.h
    scscodeerroranalyzer.h
    scserrortablewidget.h
    scscodeeditor.h
    scserrortablewidgetitem.h
    scsfindwidget.h
    scssyntaxhighlighter.h
    scscodeanalyzer.h
    scscodecompleter.h
)

set (SOURCES
    highlightingrules/scsstdhighlightingrule.cpp
    highlightingrules/scsmultilinehighlightingrule.cpp
    highlightingrules/scsmultilinecommenthighlightingrule.cpp
    highlightingrules/scshighlightingrulespool.cpp
    highlightingrules/scsabstracthighlightingrule.cpp
    scsparser/scsparserwrapper.cpp
    scsparser/scsparserexception.cpp
    scsparser/SCsCLexer.c
    scsparser/SCsCParser.c
    scsparser/scscparserdefs.c
    scsparser/scsasynchparser.cpp
    scswindow.cpp
    scserrortablewidget.cpp
    scscodeeditor.cpp
    scsfindwidget.cpp
    scscodeerroranalyzer.cpp
    scsplugin.cpp
    scserrortablewidgetitem.cpp
    scscodeanalyzer.cpp
    scssyntaxhighlighter.cpp
    scscodecompleter.cpp
)

set (RESOURCES
    scs.qrc
    )

set (TRANSLATIONS
    ${SCS_MEDIA_DIR}/translations/scs_en_EN.ts
    ${SCS_MEDIA_DIR}/translations/scs_ru_RU.ts
    )

project (${PROJECT})

FOREACH (TRANSLATION ${TRANSLATIONS})
    execute_process(COMMAND lrelease-qt4 ${TRANSLATION})
ENDFOREACH(TRANSLATION)

include_directories(./)
include_directories(./scsparser)
include_directories(./highlightingrules)
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
