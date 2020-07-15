##################################################
# Default target: builds project and runs tests. #
##################################################
all: build test

##################################################
# Creates the build, bin, and debug directories. #
################################################## 
init:
	mkdir -p build
	mkdir -p bin
	mkdir -p debug

#########################################################################
# Cleans the project by removing the bin, build, and debug directories. #
#########################################################################
clean:
	rm -rf bin
	rm -rf build
	rm -rf debug

###################################
# Builds the project using CMake. #
###################################
build: init
	cd build && \
		cmake ../ -DCMAKE_INSTALL_PREFIX=../bin && \
		make install

#########################################################################
# Runs the example main.												#
#																		#
# Requires token.txt to be created. See README.md for more information. #
#########################################################################
run:
	bin/main

####################
# Runs unit tests. #
####################
test:
	bin/tests

#################################################################################
# Builds the project in debug mode, allowing the executable to be run with gdb. #
#################################################################################
debug-build: init
	cd build && \
		cmake ../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../debug && \
		make install

#########################################################################
# Runs the example main in debug mode using gdb.						#
#																		#
# Requires token.txt to be created. See README.md for more information. #
#########################################################################
debug-run:
	gdb debug/main

############################################
# Runs unit tests in debug mode using gdb. #
############################################
debug-test:
	gdb debug/tests
