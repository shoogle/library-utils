library-utils
=============

Get information about shared libraries on Linux. Patches for other platforms
welcome!

These programs demonstrate features and code that you may wish to include in a
larger program. Of course you might find them to be useful on their own too.

## Utilities

There is a sub-directory for each program / utility:

- [findlib](findlib) - Locate a library by name and print its full file path.
- [listlibs](listlibs) - List all libraries loaded by a given library.
- [listmylibs](listmylibs) - List all libraries loaded by the program itself.
- [auditlibs](auditlibs) - Monitor another program's use of shared libraries.

[findlib]: findlib
[listlibs]: listlibs
[listmylibs]: listmylibs
[auditlibs]: auditlibs

## Compiling

This is the same as for any [CMake] project:

[CMake]: https://cmake.org/

```bash
mkdir build
cd build
cmake ..                # configure project (generate build system)
cmake --build .         # compile code with native build tool (e.g. GNU make)
sudo cmake --install .  # copy built files to system folders (optional)
```

CMake versions prior to 3.15 do not have the `--install` option. Instead use:

```bash
sudo cmake --build . --target install
```

See the [CMake manual] for more information about the `cmake`, `cmake --build`
and `cmake --install` commands.

[CMake manual]: https://cmake.org/cmake/help/latest/manual/cmake.1.html

## License

This project is released under the MIT License. See [LICENSE.txt] for details.

[LICENSE.txt]: LICENSE.txt
