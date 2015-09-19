# Francesco Pischedda. Copyright (C) 2015. GPLv3


#
# Project Properties
#
macro(use_cxx11)
    if (CMAKE_VERSION VERSION_LESS "3.1")
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
        endif ()
    else ()
        set (CMAKE_CXX_STANDARD 11)
    endif ()
endmacro(use_cxx11)

cmake_minimum_required (VERSION 2.8)
project (sfml_sprite_sheet CXX)
set (APPLICATION_NAME "sfml_sprite_sheet")
set (APPLICATION_CODENAME "${PROJECT_NAME}")
set (APPLICATION_COPYRIGHT_YEARS "2015")
set (APPLICATION_VERSION_MAJOR 0)
set (APPLICATION_VERSION_MINOR 1)
set (APPLICATION_VERSION_PATCH 0)
set (APPLICATION_VERSION_TYPE SNAPSHOT)
set (APPLICATION_VERSION_STRING "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}-${APPLICATION_VERSION_TYPE}")
#set (APPLICATION_VENDOR_ID "com.yourcompany")
#set (APPLICATION_VENDOR_NAME "Your Company")
#set (APPLICATION_VENDOR_URL "yourcompany.com")
#set (APPLICATION_ID "${APPLICATION_VENDOR_ID}.${PROJECT_NAME}")

use_cxx11()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH})

add_library(sfml_sprite_sheet SHARED
    ${CMAKE_SOURCE_DIR}/src/sprite_sheet.cpp
    ${CMAKE_SOURCE_DIR}/src/animation.cpp
    ${CMAKE_SOURCE_DIR}/src/animation_player.cpp
    ${CMAKE_SOURCE_DIR}/src/animation_loader.cpp
    ${CMAKE_SOURCE_DIR}/src/animated_sprite.cpp)

find_package(RapidJSON)
find_package(SFML 2 REQUIRED system window graphics network audio)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(sfml_sprite_sheet ${SFML_LIBRARIES})
endif()

#
# Debugging Options
#
set (CMAKE_VERBOSE_MAKEFILE 0) # Use 1 for debugging, 0 for release


#
# Project Output Paths
#
set (MAINFOLDER ${PROJECT_SOURCE_DIR})
# set (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
set (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")
set (CATCH_DIR "${MAINFOLDER}/thirdparity/catch")

IF(UNIX OR CYGWIN)
    SET(_CMAKE_INSTALL_DIR "${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME}")
ELSEIF(WIN32)
    SET(_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/cmake")
ENDIF()
SET(CMAKE_INSTALL_DIR "${_CMAKE_INSTALL_DIR}" CACHE PATH "The directory cmake fiels are installed in")

#
# Project Search Paths
#
list (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
include_directories("${MAINFOLDER}/include")


#
# Add Build Targets
#
# add_subdirectory(src)

# enable_testing()
# add_subdirectory(test)


#
# Add Install Targets
#
if (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")
    install(DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}" DESTINATION "include")
endif (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")

# Provide config and version files to be used by other applications
# ===============================

export(PACKAGE ${PROJECT_NAME})

# cmake-modules
CONFIGURE_FILE(${PROJECT_NAME}Config.cmake.in
    ${PROJECT_NAME}Config.cmake
    @ONLY)
CONFIGURE_FILE(${PROJECT_NAME}ConfigVersion.cmake.in
    ${PROJECT_NAME}ConfigVersion.cmake
    @ONLY)
INSTALL(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION "${CMAKE_INSTALL_DIR}"
    COMPONENT dev)
