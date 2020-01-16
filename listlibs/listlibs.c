// SPDX-License-Identifier: MIT
/* listlibs.c
* Load a shared object file and list the other shared object files it loads.
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
"Usage: %s OBJECT_FILE\n"
"List the full paths to all libraries loaded by OBJECT_FILE.\n"
"\n"
"The list includes libraries loaded directly, as well as libraries loaded by\n"
"those libraries, and so on.\n"
"\n"
"OBJECT_FILE can be any library or executable in ELF format.\n"
"\n"
"Exit status codes:\n"
"  0 - Success!\n"
"  1 - Failed to load OBJECT_FILE (or one of its dependencies).\n"
"  2 - Other error(s) occurred.\n"
"\n"
"OBJECT_FILE will fail to load if any of the following are true:\n"
"  - The file is corrupt.\n"
"  - It is not found in any of the library search paths (see `man ld.so`).\n"
"  - It was compiled for a different architecture to that of this program.\n"
"  - It depends (via DT_NEEDED) on another library that fails to load.\n"
"\n"
"Hint: You can use the `file` command to show the processor architecture that\n"
"any ELF library or executable (including this program) was compiled for.\n";

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, help, basename(argv[0]));
        return 2;
    }

    if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)) {
        printf(help, basename(argv[0]));
        return 0;
    }

    // Use dlmopen rather than dlopen to load the shared object into a new
    // namespace. This avoids confusing its libraries with our own.
    void *lib = dlmopen(LM_ID_NEWLM, argv[1], RTLD_LAZY);

    if (lib == NULL) {
        fprintf(stderr, "%s: %s\n", basename(argv[0]), dlerror());
        return 1;
    }

    struct link_map * map;

    // dlinfo can return information about objects loaded with dlmopen
    if (dlinfo(lib, RTLD_DI_LINKMAP, &map) == -1) {
        fprintf(lib, "%s: %s\n", basename(argv[0]), dlerror());
        return 2;
    }

    while (map->l_prev)
        map = map->l_prev; // make sure we start on the first in the series

    while (map) {
        printf("%s\n", map->l_name);
        map = map->l_next;
    }

    return 0;
}
