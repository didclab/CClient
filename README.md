CClient
=======

The OneDataShare SDK for C++ 17. To begin working with the SDK, see the
[installation instructions](#install),
the
[documentation](https://didclab.github.io/CClient),
and the
[getting started](getting-started.md)
tutorial.

Table of Contents
-----------------
- [Dependencies](#dependencies)
- [Install](#install)
- [CMake Support](#cmake-support)
- [Build](#build)
- [Examples](#examples)
- [Project Structure](#project-structure)
- [Coding Style](#coding-style)

Dependencies:
-------------
The following are required to build and test this project.
- **g++ 9.3.0** - find at https://gcc.gnu.org/gcc-9/
- **cmake 3.10.0** - find at https://cmake.org/files/v3.10/
- **libcurl 7.47.0** - install with `sudo apt-get install libcurl4-openssl-dev`

Install:
--------

To install the OneDataShare C++ SDK, follow the instructions below. Note that this will require a **C++ 17** compiler,
**CMake** `3.10.0` or greater, and **Libcurl** `7.47.0` or greater.

1. Clone the github repository at https://github.com/didclab/CClient and switch to the created directory with the
following commands:
    ```
    git clone https://github.com/didclab/CClient.git;
    cd CClient
    ```

2. Create and switch to a `build` directory with
    ```
    mkdir build;
    cd build
    ```

3. Next you must initialize the build tree and specify where you want to install the OneDataShare SDK. There are two
ways to do this. To use the default GNU install directory (`/usr/local`), use
    ```
    cmake ../ -DCMAKE_BUILD_TYPE=Release
    ```
    To specify a different directory denoted by `<path>`, use
    ```
    cmake ../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=<path>
    ```

4. Finally, to install the OneDataShare SDK, use
    ```
    sudo make install
    ```

CMake Support
-------------

The OneDataShare SDK fully supports CMake. Once installed, `OneDataShare` can be included in any CMake project by
calling `find_package(OneDataShare)` which will define the following:
 - `OneDataShare_FOUND` - defined if and only if CMake successfully found the `OneDataShare` package.
 - `OneDataShare_VERSION` - the version of the `OneDataShare` installation found by CMake.
 - `OneDataShare::OneDataShare` - the imported `OneDataShare` target
 - `ONEDATASHARE_LIBRARIES` - an alias for `OneDataShare::OneDataShare`

Once found, `OneDataShare::OneDataShare` can be linked with the project as shown below.

### Example ###
Here's a minimal working `CMakeLists.txt` file that finds the OneDataShare package and links the package with the project.
```
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(myproject LANGUAGES CXX)

find_package(OneDataShare 0.1.0 REQUIRED)

add_executable(myproject
    src/main.cpp
)

target_link_libraries(myproject
    OneDataShare::OneDataShare
)

install(TARGETS myproject
        DESTINATION .
)
```

Build:
------
This project is built and tested using `make`. See
[`Makefile`](Makefile)
for more information on targets.

Examples:
---------
To run the examples, a `token.txt` and `url.txt` file must be created in the project root containing the OneDataShare
authentication token and OneDataShare url respectively as shown below.

`token.txt`:
```
YOURAUTHENTICATIONTOKENGOESHERE
```

`url.txt`:
```
http://localhost:8080
```

Do **not** check these files into version control.

Project Structure:
------------------
`bin/` - Local-only directory containing generated binaries. This directory is **not** to be checked into version
control.

`build/` - Local-only directory containing project build tree. This directory is **not** to be checked into version
control.

`cmake/` - Contains templates for generated CMake scripts.

`docs` - Contains generated documentation for hosting on GitHub pages.

`doxygen/` - Contains files for generating documentation.

`examples/` - Contains sample files demonstrating how to use the OneDataShare SDK. These files are not part of the
main project.

`include/` - Contains public header files to be exported with the library.

`src/` - Contains the library's source files.

`tests/` - Contains unit tests for the library.

Coding Style:
-------------
This project follows the
[C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md),
including the [recommended naming and layout rules](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#nl-naming-and-layout-rules).
Note that this project does **not** use the
[Guidelines Support Library](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#gsl-guidelines-support-library).