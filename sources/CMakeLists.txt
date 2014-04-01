cmake_minimum_required (VERSION 2.6)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ../../bin/plugins)

set (PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})
set (PROJECT_OUTPUT_DIR ${PROJECT_ROOT_DIR}/build)

if (WIN32)
  set(CMAKE_USE_RELATIVE_PATHS true)
  set(CMAKE_SUPPRESS_REGENERATION true)
endif()

# setup default build type
if (CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

find_package (Qt4 COMPONENTS QtCore QtGui QtMain QtXml REQUIRED)

add_subdirectory(kbe)
add_subdirectory(plugins)
