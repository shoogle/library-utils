# SPDX-License-Identifier: MIT
# Functions are prefixed with "fn__" so you can trace them back to this file.

# Ensure that a required build dependency is installed
function(fn__required_program
        PATHV       # location of the program returned in this variable
        DESCRIPTION # what it does and where it can be found/downloaded
        COMMAND     # the name of the program on the command line
        # ARGN      any alternative names for the command
        )
    find_program(${PATHV} NAMES ${COMMAND} ${ARGN} DOC "${DESCRIPTION}")
    if(NOT ${PATHV} OR NOT EXISTS "${${PATHV}}")
        message(FATAL_ERROR
            "Program not found: ${COMMAND} - ${DESCRIPTION}\n"
            "Please ensure it is installed and then run CMake again."
            )
    endif()
endfunction()
