cmake_minimum_required(VERSION 3.28)
project(GameEngineRuntime)

option(GER_ENABLE_REAL_WGPU "Link against wgpu-native and execute real WebGPU render passes" OFF)
option(GER_ENABLE_LINUX_BACKEND "Build Linux window/input backend" OFF)
option(GER_ENABLE_MACOS_BACKEND "Build macOS window/input backend" OFF)
option(GER_ENABLE_WASM_BACKEND "Build WebAssembly backend target" OFF)

include(CTest)

add_subdirectory(core)
add_subdirectory(engine)
add_subdirectory(lua_host)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()