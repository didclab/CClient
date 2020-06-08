all: clean build run

init-build:
		mkdir -p bin
		mkdir -p build

build: init-build
		cd build; cmake ../ -DCMAKE_INSTALL_PREFIX=../; make install

clean:
	rm -rf bin
	rm -rf build

run:
	bin/tests

dbuild: init-build
		cd build; cmake ../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../; make install

drun:
		gdb -ex run bin/tests

debug: clean dbuild drun