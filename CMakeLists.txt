project(TextEditML)

cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)


########################
## Define version

set(TEXTEDITML_MAJOR_VERSION 0)
set(TEXTEDITML_MINOR_VERSION 0)
set(TEXTEDITML_PATCH_VERSION 1)
set(TEXTEDITML_VERSION ${TEXTEDITML_MAJOR_VERSION}.${TEXTEDITML_MINOR_VERSION}.${TEXTEDITML_PATCH_VERSION})

########################
## Define install dirs

set(INSTALL_LIB_DIR     lib${LIB_SUFFIX}/ CACHE PATH "Installation directory for libraries")
set(INSTALL_INCLUDE_DIR include/          CACHE PATH "Installation directory for headers")
set(INSTALL_BIN_DIR     bin/              CACHE PATH "Installation directory for executables")
set(INSTALL_SHARE_DIR   share/TextEditML/        CACHE PATH "Installation directory for data")
set(INSTALL_DOC_DIR     share/doc/TextEditML/    CACHE PATH "Installation directory for documentation")
set(INSTALL_QML_PLUGIN_DIR ${INSTALL_LIB_DIR}/qt5/qml/TextEditML)

if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR cmake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/cmake/TextEditML)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE SHARE DOC CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

#
# Define INSTALL_TARGETS_DEFAULT_ARGS to be used as install target for program and library.
# It will do the right thing on all platform
#
set(INSTALL_TARGETS_DEFAULT_ARGS  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
                                  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
                                  ARCHIVE DESTINATION "${INSTALL_LIB_DIR}" COMPONENT Devel )

########################
## Enable C++11 and all warnings

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

########################
## Find Qt5

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS Quick)

########################
## Find KF5SyntaxHighlighting

find_package(KF5SyntaxHighlighting)

########################
## subdirectories

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(TextEditML)

