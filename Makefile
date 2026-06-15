.PHONY: all debug release clean test package

all: debug

debug:
	cmake -B build/debug -DCMAKE_BUILD_TYPE=Debug -G Ninja
	cmake --build build/debug
	cd _api && dub build --config=debug
	cd _runtime && dub build --config=debug

release:
	cmake -B build/release -DCMAKE_BUILD_TYPE=Release -G Ninja
	cmake --build build/release
	cd _api && dub build --config=release
	cd _runtime && dub build --config=release

clean:
	rm -rf build
	cd _core && rm -rf build
	cd _engine && rm -rf build
	cd _lua_host && rm -rf build
	cd _api && dub clean
	cd _runtime && dub clean
	cd _2d && dub clean

test:
	cd build/debug && ctest --output-on-failure
	cd _api && dub test
	cd _2d && dub test

package: release
	mkdir -p dist
	cp build/release/_runtime/ger_runtime dist/
	strip dist/ger_runtime