OPTION (BUILD_SHARED_LIBS "Build shared libraries." ON)

set(PLUGINS_DIR ${PROJECT_ROOT_DIR}/plugins)

add_subdirectory(scg)
add_subdirectory(scs)
