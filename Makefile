# Default target. Creates a clean build and runs tests. Requires token.txt to be created. See README.md for more information.
all: clean build run

# Uses CMake to build the project.
build: init-build
	cd build && \
		cmake ../ -DCMAKE_INSTALL_PREFIX=../ && \
		make install

# Cleans the project by removing the bin and build directories.
clean:
	rm -rf bin
	rm -rf build

# Runs the tests. Requires token.txt to be created. See README.md for more information.
run:
	bin/tests

# Builds the project in debug mode, allowing the executable to be run with gdb.
dbuild: init-build
	cd build && \
		cmake ../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../ && \
		make install
	
# Runs the tests in debug mode using gdb. Requires token.txt to be created. See README.md for more information.
drun:
	gdb bin/tests

# Creates clean build in debug mode and runs tests in gdb. Requires token.txt to be created. See README.md for more information.
debug: clean dbuild drun

# Creates the bin and build directories for storing executable and object files respectively.
init-build:
	mkdir -p bin
	mkdir -p build