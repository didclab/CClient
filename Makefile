THIS_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

##################################################
# Default target: builds project and runs tests. #
##################################################
all: build run

##########################################
# Creates the bin and build directories. #
##########################################
init:
	mkdir -p ${THIS_DIR}/bin
	mkdir -p ${THIS_DIR}/build

##########################################
# Removes the bin and build directories. #
##########################################
clean:
	rm -rf ${THIS_DIR}/bin
	rm -rf ${THIS_DIR}/build

#####################################################################################################
# Uses CMake to build the project in the build directory and install binaries in the bin directory. #
#####################################################################################################
build: init
	cd ${THIS_DIR}/build && \
		cmake ../ -DCMAKE_INSTALL_PREFIX=../bin -DCMAKE_BUILD_TYPE=Debug && \
		make install

####################
# Runs unit tests. #
####################
run:
	${THIS_DIR}/bin/tests