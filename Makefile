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