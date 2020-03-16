.PHONY: all
all: format test build

.PHONY: format
format:
	clang-format src/* include/* test/* -i

.PHONY: build
build:
	mkdir -p build
	cd build && \
	conan install .. --build missing && \
	cmake .. && \
	make

.PHONY: debug
debug:
	mkdir -p build
	cd build && \
  	conan install .. --build missing && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make

.PHONY: clean
clean:
	rm -rf build