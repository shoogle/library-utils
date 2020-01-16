# SPDX-License-Identifier: MIT

add_executable(auditlibs auditlibs.c)

target_link_libraries(auditlibs ${CMAKE_DL_LIBS})

install(TARGETS auditlibs DESTINATION bin)
