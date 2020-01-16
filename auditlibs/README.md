auditlibs
========

Monitor another program's use of shared libraries.

Demonstrates use of [rtld-audit] and [execvp].

[rtld-audit]: http://man7.org/linux/man-pages/man7/rtld-audit.7.html
[execvp]:     http://man7.org/linux/man-pages/man3/execvp.3.html

## Usage

```bash
LD_AUDIT=/path/to/auditlibs PROGRAM [ARGS...]
```

Or equivalently:

```bash
auditlibs PROGRAM [ARGS...]
```

The second method works because `auditlibs` has a `main()` function that
does the job of setting the `LD_AUDIT` environment variable for you.

## Examples

```bash
$ auditlibs echo "Hello, World!"
auditlibs: la_version():       1
auditlibs: la_objopen():       0x7f8fb25eb608       LM_ID_BASE
auditlibs: la_objopen():       0x7f8fb25eae68       LM_ID_BASE           /lib64/ld-linux-x86-64.so.2
auditlibs: la_activity():      0x7f8fb25eb608       LA_ACT_ADD
auditlibs: la_objsearch():     0x7f8fb25eb608       LA_SER_ORIG          libc.so.6
auditlibs: la_objsearch():     0x7f8fb25eb608       LA_SER_CONFIG        /lib/x86_64-linux-gnu/libc.so.6
auditlibs: la_objopen():       0x7f8fb23aeff8       LM_ID_BASE           /lib/x86_64-linux-gnu/libc.so.6
auditlibs: la_activity():      0x7f8fb25eb608       LA_ACT_CONSISTENT
auditlibs: la_preinit():       0x7f8fb25eb608
Hello, World!
```

Or equivalently:

```bash
$ LD_AUDIT=/path/to/auditlibs /bin/echo "Hello, World!"
auditlibs: la_version():       1
auditlibs: la_objopen():       0x7fdf531c7608       LM_ID_BASE
auditlibs: la_objopen():       0x7fdf531c6e68       LM_ID_BASE           /lib64/ld-linux-x86-64.so.2
auditlibs: la_activity():      0x7fdf531c7608       LA_ACT_ADD
auditlibs: la_objsearch():     0x7fdf531c7608       LA_SER_ORIG          libc.so.6
auditlibs: la_objsearch():     0x7fdf531c7608       LA_SER_CONFIG        /lib/x86_64-linux-gnu/libc.so.6
auditlibs: la_objopen():       0x7fdf52f8af78       LM_ID_BASE           /lib/x86_64-linux-gnu/libc.so.6
auditlibs: la_activity():      0x7fdf531c7608       LA_ACT_CONSISTENT
auditlibs: la_preinit():       0x7fdf531c7608
Hello, World!
```

Here we gave the full path to the `/bin/echo` binary to avoid calling the
`echo` command built-in to most shells. This was not necessary in the first
example because launching a binary via `auditlibs` (i.e. via [execvp]) avoids
the shell.

## Notes

The first call to `la_objopen()` always shows a blank filename. This refers
to the executable itself (i.e. `echo` in the examples above).

The [rtld-audit] manual says that the `LD_AUDIT` environment variable should
point to a shared library. However, the example above appears to show that
`auditlibs` is a program rather than a library. In fact it is *both*!
Technically, it is an executable that was compiled with the `-rdynamic` flag,
but you could also think of it as a library that happens to have a function
called `main()`.

## Compilation

The program can be built using the [CMake files], or on its own with:

```bash
gcc -fPIE -pie -rdynamic auditlibs.c -o auditlibs
```

[CMake files]: ../README.md#compiling
