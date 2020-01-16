# SPDX-License-Identifier: MIT

fn__required_program(ECLINT
    "Enforce .editorconfig coding rules <https://github.com/jedmao/eclint>"
    eclint
    )

add_custom_target(lint_checks ALL
    COMMAND "${ECLINT}" check
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    )
