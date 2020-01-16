listlibs
========

List all libraries loaded by a given library.

Demonstrates use of [dlmopen] and [dlinfo].

[dlmopen]: http://man7.org/linux/man-pages/man3/dlmopen.3.html
[dlinfo]:  http://man7.org/linux/man-pages/man3/dlinfo.3.html

## Usage

```bash
listlibs LIBRARY
```

## Examples

```bash
$ listlibs libstdc++.so.6
/lib/x86_64-linux-gnu/libstdc++.so.6
/lib/x86_64-linux-gnu/libm.so.6
/lib/x86_64-linux-gnu/libgcc_s.so.1
```

## Notes

The first line of output is always refers to the library specified on the
command line. This is because it is the first object file loaded within its
namespace (see [dlmopen]).

If we were to swap the call to [dlmopen] with a call to [dlopen] then the
library would be loaded into the `listlibs` executable's own namespace. The
programs behaviour would then be similar to that of the [listmylibs] utility.

[listmylibs]: ../listmylibs

## Compilation

The program can be built using the [CMake files], or on its own with:

```bash
gcc listlibs.c -o listlibs -ldl
```

[CMake files]: ../README.md#compiling
