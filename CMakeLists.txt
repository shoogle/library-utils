# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.0)

project(LIBRARY_UTILS
    VERSION 0.1.0
    LANGUAGES C
    )

set(PROJECT_NAME_PRETTY "library-utils")
set(${PROJECT_NAME}_PRETTY "${PROJECT_NAME_PRETTY}")

set(PROJECT_DESCRIPTION "Get information about shared libraries on Linux.")
set(${PROJECT_NAME}_DESCRIPTION "${PROJECT_DESCRIPTION}")

set(PROJECT_HOMEPAGE_URL "https://github.com/shoogle/library-utils")
set(${PROJECT_NAME}_HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")

message(
    "Configuring project ${PROJECT_NAME} (${PROJECT_NAME_PRETTY} ${PROJECT_VERSION})\n"
    "   Description: ${PROJECT_DESCRIPTION}\n"
    "   Homepage:    <${PROJECT_HOMEPAGE_URL}>"
    )

option(LINT_CHECKS "Check code for common mistakes before building." ON)

# Compile with -fPIC / -fPIE so that dlopen can handle our executables
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# Link with -pie. See https://gitlab.kitware.com/cmake/cmake/issues/14983
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pie")

include(cmake/functions.cmake)
include(cmake/snippets.cmake)

if(LINT_CHECKS)
    include(cmake/lint_checks.cmake)
endif()

add_subdirectory(findlib)
add_subdirectory(listlibs)
add_subdirectory(listmylibs)
add_subdirectory(auditlibs)
