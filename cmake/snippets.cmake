# SPDX-License-Identifier: MIT

# Adapted from https://blog.kitware.com/cmake-and-the-default-build-type/
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    # Set a default build type if none was specified
    if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
        set(default_build_type "Debug")
    else()
        set(default_build_type "Release")
    endif()
    message(STATUS "Setting CMAKE_BUILD_TYPE to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
