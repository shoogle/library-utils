findlib
=======

Print the full file path of a library if it can be dynamically loaded.

Demonstrates use of [dlopen] and [dlinfo].

[dlopen]: http://man7.org/linux/man-pages/man3/dlopen.3.html
[dlinfo]: http://man7.org/linux/man-pages/man3/dlinfo.3.html

## Usage

```bash
findlib LIBRARY
```

## Examples

```bash
$ findlib ld-linux-x86-64.so.2
/lib64/ld-linux-x86-64.so.2

$ findlib libc.so.6
/lib/x86_64-linux-gnu/libc.so.6

$ findlib libfoo.so
findlib: libfoo.so: cannot open shared object file: No such file or directory

$ findlib /path/to/foo/libfoo.so
/path/to/foo/libfoo.so

$ LD_LIBRARY_PATH=/path/to/foo findlib libfoo.so
/path/to/foo/libfoo.so
```

## Notes

In interesting case occurs when you call the program with the empty string:

```bash
$ findlib ""

```

Here the output is blank, but we get no error. The man page for [dlopen]
states:

> If filename is NULL, then the returned handle is for the main program.

In other words we just asked `findlib` to load itself!

## Compilation

The program can be built using the [CMake files], or on its own with:

```bash
gcc findlib.c -o findlib -ldl
```

[CMake files]: ../README.md#compiling
