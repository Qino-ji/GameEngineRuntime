cmake_minimum_required(VERSION 3.28)
project(ger_lua C)

set(LUA_CORE_SRC
    ${CMAKE_SOURCE_DIR}/_deps/lua/lapi.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lauxlib.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lbaselib.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lcode.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lctype.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lcorolib.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/ldblib.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/ldebug.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/ldo.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/ldump.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lfunc.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lgc.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/linit.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/liolib.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/llex.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lmathlib.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lmem.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/loadlib.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lobject.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lopcodes.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/loslib.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lparser.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lstate.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lstring.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lstrlib.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/ltable.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/ltablib.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/ltm.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lundump.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lutf8lib.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lvm.c
    ${CMAKE_SOURCE_DIR}/_deps/lua/lzio.c
)

set(LUA_SRC
    src/lua_host.c
    src/lua_bindings.c
)

add_library(lua STATIC ${LUA_CORE_SRC})
target_include_directories(lua PUBLIC ${CMAKE_SOURCE_DIR}/_deps/lua)
target_compile_definitions(lua PRIVATE LUA_COMPAT_5_3)

add_library(ger_lua STATIC ${LUA_SRC})
target_include_directories(ger_lua PUBLIC include)
target_link_libraries(ger_lua PUBLIC lua ger_core)

set_target_properties(ger_lua lua PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
)