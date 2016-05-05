
##
## Project Properties
##
cmake_minimum_required (VERSION 3.0)
project (spear)

set (APPLICATION_NAME "spear")
set (APPLICATION_CODENAME "${PROJECT_NAME}")
set (APPLICATION_COPYRIGHT_YEARS "2016")

set (APPLICATION_VERSION_MAJOR 0)
set (APPLICATION_VERSION_MINOR 1)
set (APPLICATION_VERSION_PATCH 0)

set (APPLICATION_VERSION_TYPE SNAPSHOT)
set (APPLICATION_VERSION_STRING
    "${APPLICATION_VERSION_MAJOR}."
    "${APPLICATION_VERSION_MINOR}."
    "${APPLICATION_VERSION_PATCH}-"
    "${APPLICATION_VERSION_TYPE}")
set (APPLICATION_VENDOR_ID "com.AJC")
set (APPLICATION_VENDOR_NAME "AJC")
set (APPLICATION_VENDOR_URL "https://github.com/anthony-jclark/spear")
set (APPLICATION_ID "${APPLICATION_VENDOR_ID}.${PROJECT_NAME}")



##
## Project Output Paths
##
set (MAINFOLDER ${PROJECT_SOURCE_DIR})
set (BIN_PATH "${MAINFOLDER}/bin")
set (SRC_PATH "${MAINFOLDER}/src")
set (SUPPORT_PATH "${MAINFOLDER}/support")

# set (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_PATH})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_PATH})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_PATH})


##
## Project Search Paths
##
list (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
# list (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/tools")
# list (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/thirdparty")
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${MAINFOLDER}/support/cmake")
# INCLUDE_DIRECTORIES("${MAINFOLDER}/include")



##
## Use 0 for debugging, 1 for release
##
set (CMAKE_VERBOSE_MAKEFILE 0)



##
## Project Sources
##
# file (GLOB_RECURSE PROJECT_SRCS ${MAINFOLDER}/src/*.cpp ${MAINFOLDER}/src/*.h)
# file (GLOB_RECURSE TEST_SRCS ${MAINFOLDER}/test/*.cpp ${MAINFOLDER}/test/*.h)



##
## Configure Files
##
file (GLOB_RECURSE CONFIGINPUTS1 include/*.h.in.cmake)
file (GLOB_RECURSE CONFIGINPUTS2 src/*.h.in.cmake)
list (APPEND CONFIGINPUTS "${CONFIGINPUTS1}")
list (APPEND CONFIGINPUTS "${CONFIGINPUTS2}")
foreach (CONFIGINPUT ${CONFIGINPUTS})
    string (REPLACE ".h.in.cmake" ".h" CONFIGOUTPUT1 "${CONFIGINPUT}")
    configure_file ("${CONFIGINPUT}" "${CONFIGOUTPUT1}")
endforeach (CONFIGINPUT ${CONFIGINPUTS})



##
## Add Build Targets
##
add_subdirectory (src)
add_subdirectory (test)
# add_subdirectory (thirdparty)



##
## Add Documentation Targets
##
# include (DocumentationTargets)
