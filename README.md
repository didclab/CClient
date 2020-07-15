CClient
=======

C++ Client for One Data Share.

Dependencies:
-------------
- g++ 9.3.0 - find at https://gcc.gnu.org/gcc-9/
- cmake 3.10.0 - find at https://cmake.org/files/v3.10/
- libcurl 7.47.0 - install with `sudo apt-get install libcurl4-openssl-dev`

Build:
------
This project is built and tested using `make`. See `Makefile` for more information on targets.

To run tests, a `token.txt` file must be created in the project root. This file should contain your One Data Share url
on the first line and your One Data Share authentication token on the second line as shown below:
```
http://localhost:8080
YOURAUTHENTICATIONTOKENGOESHERE
```
Do **not** check this file into version control.

A more sophisticated method of defining these fields will be introduced at a later time.