// SPDX-License-Identifier: MIT
/* listmylibs.c
* List all the shared object files loaded by this program.
* Part of library-utls - https://github.com/shoogle/library-utils
* Copyright (c) 2020 Peter Jonas
*/
#define _GNU_SOURCE
#include <link.h>
#include <dlfcn.h>
#include <libgen.h>
#include <string.h>
#include <stdio.h>

char *help =
"Usage: %s [LIBRARY...]\n"
"List the full paths to all libraries used by this program.\n"
"\n"
"The list includes libraries that the program was linked against at compile\n"
"time, as well as any libraries loaded by those libraries, and so on.\n"
"\n"
"Optionally specify additional libraries to load before computing the list.\n"
"\n"
"Exit status codes:\n"
"  0 - Success!\n"
"  1 - Failed to load LIBRARY (or one of its dependencies).\n"
"\n"
"LIBRARY will fail to load if any of the following are true:\n"
"  - The file is corrupt.\n"
"  - It is not found in any of the library search paths (see `man ld.so`).\n"
"  - It was compiled for a different architecture to that of this program.\n"
"  - It depends (via DT_NEEDED) on another library that fails to load.\n"
"\n"
"Hint: You can use the `file` command to show the processor architecture that\n"
"any ELF library or executable (including this program) was compiled for.\n";

// callback function for use with dl_phdr_info
static int callback(struct dl_phdr_info *info, size_t size, void *data)
{
    printf("%s\n", info->dlpi_name);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)) {
            printf(help, basename(argv[0]));
            return 0;
        }
    }

    for (int i = 1; i < argc; i++) {
        // dlopen enables us to load shared objects during execution
        if (dlopen(argv[i], RTLD_LAZY) == NULL) {
            fprintf(stderr, "%s: %s\n", basename(argv[0]), dlerror());
            return 1;
        }
    }

    // dl_iterate_phdr calls a callback function on all our shared objects
    dl_iterate_phdr(callback, NULL);
    return 0;
}
