set (PROJECT scg)

set(SCG_DIR ${PLUGINS_DIR}/scg)
set(SCG_MEDIA_DIR ${SCG_DIR}/media)

set(SCG_SRCS
    scgabstractobjectbuilder.cpp
    scgalphabet.cpp
    scgbus.cpp
    scgconfig.cpp
    scgcontent.cpp
    scgcontentchangedialog.cpp
    scgcontentdialog.cpp
    scgcontentfactory.cpp
    scgcontentimage.cpp
    scgcontentnumeric.cpp
    scgcontentstring.cpp
)

set(SCG_HDRS
    scgabstractobjectbuilder.h
    scgalphabet.h
    scgbus.h
    scgconfig.h
    scgcontent.h
    scgcontentchangedialog.h
    scgcontentdialog.h
    scgcontentfactory.h
    scgcontentimage.h
    scgcontentnumeric.h
    scgcontentstring.h
)

set(SCG_MOC_HDRS

)

set (SCG_UI_FORMS
    )

set (SCG_ALL_SRCS
    ${SCG_SRCS}
    ${SCG_UI_FORMS}
    )

project (${PROJECT})

include_directories(./)
include_directories(${PROJECT_ROOT_DIR}/kbe)

include (${QT_USE_FILE})
qt4_wrap_ui (SAMPLE_UI_HDRS ${SCG_UI_FORMS})
qt4_wrap_cpp (MOC_SOURCES ${SCG_MOC_HDRS})

add_definitions (-Wall)

source_group ("Header Files" FILES ${SCG_HDRS})
source_group ("Source Files" FILES ${SCG_ALL_SRCS})
source_group ("Generated Files" FILES ${MOC_SOURCES} ${QM_FILES})

if (WIN32)
add_library (${PROJECT}
             ${SCG_HDRS}
             ${MOC_SOURCES}
             ${SCG_ALL_SRCS}
             ${QM_FILES}
             scg.rc
             )
else (WIN32)
add_library (${PROJECT}
             ${SCG_HDRS}
             ${MOC_SOURCES}
             ${SCG_ALL_SRCS}
             ${QM_FILES}
             )
endif (WIN32)

target_link_libraries (${PROJECT} ${QT_LIBRARIES})

