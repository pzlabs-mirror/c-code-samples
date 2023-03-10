# C Code Samples

[![build](https://github.com/pzlabs-mirror/c-code-samples/actions/workflows/test-all.yml/badge.svg)](https://github.com/pzlabs-mirror/c-code-samples/actions/workflows/test-all.yml)

A collection of simple code samples and examples for projects in the C programming language.

## Contents
  * "hello\_world": a Hello, World program
  * "swap\_vars": swapping values of two variables (3 solutions)
  * "fizzbuz": FizzBuzz (6 solutions)
  * "canvas": drawing on a 2D canvas with ASCII and PPM6 output
  * "search": linear and binary search implementations
  * "variadic\_fold": a left fold implementation using variadic arguments and pointers to functions (3 solutions)
  * "strview": a custom string view type inspired by C++'s `std::string_view`
  * "stack\_machine": a simple programmable stack machine
  * "slist": a singly linked list implementation
  * "dlist": a doubly linked list implementation
  * "lab1": lab1 examples (task 1, task 2)
  * "lab2": lab2 example (task 2)
  * "lab3": lab3 example (task 2)
  * "lab4": lab4 example (task 2)

### Extras
  * "extra/test1": test 1 helper app

## Building

> :information_source: These instructions describe how to run CMake commands manually. You can simply open
the `CMakeLists.txt` in any IDE that supports CMake, including (but not limited to Qt Creator,
Visual Studio, KDevelop, and CLion.

1. Install `git`, a `C` compiler, `CMake`, and a build system available as a `CMake` generator
(e.g. `Ninja`, `GNU Make`, `MSBuild`, `NMake`, `Jom`).
2. Download this repository.
    ```bash
    $ git clone https://gitlab.com/pzlabs/c-code-samples.git
    $ cd c-code-samples
    ```
3. Run the configuration stage in a build directory. Change the name of this directory if needed.
Multiple build directories are supported and encouraged in case of multiple configurations.
    ```bash
    $ mkdir build-reldeb
    $ cmake -B build-reldeb -D CMAKE_BUILD_TYPE=RelWithDebInfo
    ```
    The following [configurations](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html#variable:CMAKE_BUILD_TYPE)
    specified by the `CMAKE_BUILD_TYPE` option are supported by default: `Debug`, `MinSizeRel`, `RelWithDebInfo`, `Release`.
4. Build every target.
    ```bash
    $ cmake --build build-reldeb
    ```

    To build a specific executable, run `cmake --build ${MY_BUILD_DIR} --target ${MY_TARGET}`:
    ```bash
    $ cmake --build build-reldeb --target hello_world
    ```

5. You can cleanup binaries in the build directory by running the `clean` target:
    ```bash
    $ cmake --build build-reldeb --target clean
    ```

6. (Optionally) Install binaries.
    ```bash
    $ cmake --build build-reldeb --target install
    ```
    CMake will copy all the executable from the build directory to the install path.
    This project sets that the default install directory is called `install` and resides in the project root.
    This behavior can be changed by specifying `CMAKE_INSTALL_PREFIX` explicitly during configuration:
    ```bash
    $ cmake -B build-reldeb -D CMAKE_INSTALL_PREFIX=${MY_CUSTOM_INSTALL_PREFIX}
    ```

## Running

After being built, the binaries can be found in the build directory:
```bash
$ build-reldeb/hello_world
```
You can also run the optionally installed executables from the installation folder:
```bash
$ install/bin/hello_world
```
