#define _GNU_SOURCE
#include <link.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <libgen.h>
#include <string.h>

static const char *la_objsearch_flag_str(unsigned int flag)
{
    switch (flag) {
        case LA_SER_ORIG:       return "LA_SER_ORIG";
        case LA_SER_LIBPATH:    return "LA_SER_LIBPATH";
        case LA_SER_RUNPATH:    return "LA_SER_RUNPATH";
        case LA_SER_DEFAULT:    return "LA_SER_DEFAULT";
        case LA_SER_CONFIG:     return "LA_SER_CONFIG";
        case LA_SER_SECURE:     return "LA_SER_SECURE";
        default:                return "LA_SER_???";
    }
}

static const char *la_activity_flag_str(unsigned int flag)
{
    switch (flag) {
        case LA_ACT_CONSISTENT: return "LA_ACT_CONSISTENT";
        case LA_ACT_ADD:        return "LA_ACT_ADD";
        case LA_ACT_DELETE:     return "LA_ACT_DELETE";
        default:                return "LA_ACT_???";
    }
}

static const char *la_objopen_lmid_str(Lmid_t lmid)
{
    switch (lmid) {
        case LM_ID_BASE:        return "LM_ID_BASE";
        case LM_ID_NEWLM:       return "LM_ID_NEWLM";
        default:                return "LM_ID_???";
    }
}

unsigned int la_version(unsigned int version)
{
    printf("auditlibs: la_version():       %d\n", version);
    return version;
}

char *la_objsearch(const char *name, uintptr_t *cookie, unsigned int flag)
{
    printf("auditlibs: la_objsearch():     %-20p %-20s %s\n", cookie, la_objsearch_flag_str(flag), name);
    return (char *)name; // cast to remove const qualifier from name
}

void la_activity(uintptr_t *cookie, unsigned int flag)
{
    printf("auditlibs: la_activity():      %-20p %s\n", cookie, la_activity_flag_str(flag));
}

unsigned int la_objopen(struct link_map *map, Lmid_t lmid, uintptr_t *cookie)
{
    printf("auditlibs: la_objopen():       %-20p %-20s %s\n",
        cookie,
        la_objopen_lmid_str(lmid),
        map->l_name
        );

    return 0;
}

unsigned int la_objclose(uintptr_t *cookie)
{
    printf("auditlibs: la_objclose():      %p\n", cookie);
    return 0;
}

void la_preinit(uintptr_t *cookie)
{
    printf("auditlibs: la_preinit():       %p\n", cookie);
}

char *help =
"Usage: %s PROGRAM [ARGS...]\n"
"Run PROGRAM and monitor its use of shared libraries.\n"
"\n"
"The exit status code returned is that of PROGRAM itself, unless it could not\n"
"be run in which case the exit code is 127.";

static const ssize_t self_path(char *buf, size_t bufsiz)
{
    const ssize_t nbytes = readlink("/proc/self/exe", buf, bufsiz);

    if (nbytes == -1) {
        perror("readlink failed");
        return -1;
    } else if (nbytes == bufsiz) {
        fputs("path was truncated", stderr);
        return -2;
    }

    buf[nbytes] = '\0'; // terminate string with null byte
    return nbytes;
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        fprintf(stderr, help, basename(argv[0]));
        return 2;
    }

    if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)) {
        printf(help, basename(argv[0]));
        return 0;
    }

    const char *str = "LD_AUDIT=";
    const int len = strlen(str);

    char buf[PATH_MAX + len + 1];
    strcpy(buf, str);

    char *ptr = buf + len;

    if (self_path(ptr, PATH_MAX) < 0)
        return 127;

    putenv(buf);

    // launch the program specified on command line
    execvp(argv[1], argv + 1); // this function does not return
    perror(argv[1]); // only get here if execvp fails
    return 127;
}
