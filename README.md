# C Code Samples

A collection of simple code samples and examples for projects in C.

## Contents
  * `hello_world`
  * `swap`
  * `lab1`
  * More samples coming soon.
  
## Building

> :information_source: This instruction describes how to run CMake commands manually. You can simply open
the `CMakeLists.txt` in any IDE that supports CMake, including but not limited to Qt Creator,
Visual Studio, KDevelop, and CLion.

1. Install `git`, a `C` compiler, `CMake`, and a build system available as a `CMake` generator
(e.g. `Ninja`, `GNU Make`, `MSBuild`, `NMake`, `Jom`).
2. Download this repository.
    ```bash
    $ git clone https://gitlab.com/pzlabs/c-code-samples.git
    $ cd c-code-samples
    ```
3. Run the configuration step in a build directory. Change the name of this directory if needed.
Multiple build directories are supported and encouraged in case of multiple configurations.
    ```bash
    $ cmake -B build 
    ```
4. Build every target.
    ```bash
    $ cmake --build build 
    ```

    To build a specific executable, run `cmake --build ${MY_BUILD_DIR} --target ${MY_TARGET}`:
    ```bash
    $ cmake --build build --target hello_world
    ```

5. You can cleanup binaries in the build directory by running the `clean` target:
    ```bash
    $ cmake --build build --target clean
    ```

6. (Optionally) Install binaries.
    ```bash
    $ cmake --build build --target install
    ```
    CMake will copy all the executable from the build directory to the install path.
    By default, the install directory is called `install` and resides in the project root.
    This behavior can be changed by specifying `CMAKE_INSTALL_PREFIX` explicitly during configuration:
    ```bash
    $ cmake -B build -D CMAKE_INSTALL_PREFIX=${MY_CUSTOM_INSTALL_PREFIX}
    ```

## Running

After being built, the binaries can be found in the build directory:
```bash
$ build/hello_world
```
You can also run installed programs from the installation folder:
```bash
$ install/bin/hello_world
```
