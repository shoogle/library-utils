listmylibs
==========

List all libraries loaded by this program.

Demonstrates use of [dlopen] and [dl_iterate_phdr].

[dlopen]:          http://man7.org/linux/man-pages/man3/dlopen.3.html
[dl_iterate_phdr]: http://man7.org/linux/man-pages/man3/dl_iterate_phdr.3.html

## Usage

```bash
listmylibs [LIBRARY...]
```

## Examples

```bash
$ listmylibs

linux-vdso.so.1
/lib/x86_64-linux-gnu/libdl.so.2
/lib/x86_64-linux-gnu/libc.so.6
/lib64/ld-linux-x86-64.so.2

$ listmylibs libstdc++.so.6

linux-vdso.so.1
/lib/x86_64-linux-gnu/libdl.so.2
/lib/x86_64-linux-gnu/libc.so.6
/lib64/ld-linux-x86-64.so.2
/lib/x86_64-linux-gnu/libstdc++.so.6
/lib/x86_64-linux-gnu/libm.so.6
/lib/x86_64-linux-gnu/libgcc_s.so.1
```

# Notes

The first line of output is always blank. This line is actually the empty
string (""), and it refers to the `listmylibs` executable itself. See
[dl_iterate_phdr] for details.

## Compilation

The program can be built using the [CMake files], or on its own with:

```bash
gcc findlib.c -o findlib -ldl
```

[CMake files]: ../README.md#compiling
