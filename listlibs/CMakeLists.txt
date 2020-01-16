# SPDX-License-Identifier: MIT

add_executable(listlibs listlibs.c)

target_link_libraries(listlibs ${CMAKE_DL_LIBS})

install(TARGETS listlibs DESTINATION bin)
