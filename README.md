CClient
=======

C++ Client for One Data Share.

Dependencies:
-------------
- **g++ 9.3.0** - find at https://gcc.gnu.org/gcc-9/
- **cmake 3.10.0** - find at https://cmake.org/files/v3.10/
- **libcurl 7.47.0** - install with `sudo apt-get install libcurl4-openssl-dev`

Build:
------
This project is built and tested using `make`. See `Makefile` for more information on targets.

Examples:
---------
To run the examples, a `token.txt` and `url.txt` file must be created in the project root containing the One Data Share
authentication token and One Data Share url to use respectively as shown below.

`token.txt`:
```
YOURAUTHENTICATIONTOKENGOESHERE
```

`url.txt`:
```
http://localhost:8080
```

Do **not** check these files into version control.

Install:
--------
To install the One Data Share C++ SDK, follow the instructions below. Note that this will require CMake `3.10.0` or greater and libcurl `7.47.0` or greater.

1. Clone the github repository at https://github.com/didclab/CClient and switch to the created directory with the following commands:
    ```
    git clone https://github.com/didclab/CClient.git;
    cd CClient
    ```

2. Create and switch to a `build` directory with
    ```
    mkdir build;
    cd build
    ```

3. Next you must initialize the build tree and specify where you want to install the One Data Share SDK. There are two ways to do this. To use the default GNU install directory (`/usr/local`), use
    ```
    cmake ../ -DCMAKE_BUILD_TYPE=Release
    ```
    To specify a different directory denoted by `<path>`, use
    ```
    cmake ../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=<path>
    ```

4. Finally, to install the One Data Share SDK, use
    ```
    make install
    ```

CMake Support
-------------

The One Data Share SDK fully supports CMake. Once installed, `OneDataShare` can be included in any CMake project by using `find_package(OneDataShare)`. Without any other user interaction, `find_package` defines the following:
 - `OneDataShare_FOUND` - defined if and only if CMake successfully found the `OneDataShare` package.
 - `OneDataShare_VERSION` - the version of the `OneDataShare` installation found by CMake.
 - `OneDataShare::OneDataShare` - the imported `OneDataShare` target
 - `ONEDATASHARE_LIBRARIES` - an alias for `OneDataShare::OneDataShare`

Once found, `OneDataShare::OneDataShare` can be linked with the project.

### Example ###
```
cmake_minimum_required(VERSION 3.10)

project(myproject LANGUAGES CXX)

find_package(OneDataShare REQUIRED)

add_executable(myproject
    src/main.cpp
)

target_link_libraries(myproject
    OneDataShare::OneDataShare
)
```