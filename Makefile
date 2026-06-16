.PHONY: all debug release clean test package

all: debug

debug:
	cmake -B build/debug -DCMAKE_BUILD_TYPE=Debug -G Ninja
	cmake --build build/debug
	cd api && dub build --config=debug
	cd runtime && dub build --config=debug

release:
	cmake -B build/release -DCMAKE_BUILD_TYPE=Release -G Ninja
	cmake --build build/release
	cd api && dub build --config=release
	cd runtime && dub build --config=release

clean:
	rm -rf build
	cd core && rm -rf build
	cd engine && rm -rf build
	cd lua_host && rm -rf build
	cd api && dub clean
	cd runtime && dub clean
	cd engine2d && dub clean

test:
	cd build/debug && ctest --output-on-failure
	cd api && dub test
	cd engine2d && dub test

package: release
	mkdir -p dist
	cp build/release/_runtime/ger_runtime dist/
	strip dist/ger_runtime