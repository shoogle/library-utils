# SPDX-License-Identifier: MIT

add_executable(listmylibs listmylibs.c)

target_link_libraries(listmylibs ${CMAKE_DL_LIBS})

install(TARGETS listmylibs DESTINATION bin)
