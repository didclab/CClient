##################################################
# Default target: builds project and runs tests. #
##################################################
all: build run

##################################################
# Creates the build, bin, and debug directories. #
################################################## 
init:
	mkdir -p bin
	mkdir -p build

#################################################################
# Cleans the project by removing the bin and build directories. #
#################################################################
clean:
	rm -rf bin
	rm -rf build

###########################################################################
# Builds the project using CMake and generates example and test binaries. #
###########################################################################
build: init
	cd build && \
		cmake ../ -DCMAKE_INSTALL_PREFIX=../bin -DCMAKE_BUILD_TYPE=Debug && \
		make install

########################################################################
# Builds the project using CMake and installs the library and headers. #
########################################################################
install: init
	cd build && \
		cmake ../ -DCMAKE_BUILD_TYPE=Release && \
		make install

####################
# Runs unit tests. #
####################
run:
	bin/tests