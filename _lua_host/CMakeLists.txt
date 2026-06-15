cmake_minimum_required(VERSION 3.28)
project(ger_lua C)

set(LUA_SRC
    src/lua_host.c
    src/lua_bindings.c
)

add_library(ger_lua STATIC ${LUA_SRC})
target_include_directories(ger_lua PUBLIC include
    PRIVATE ${CMAKE_SOURCE_DIR}/_deps/lua
)
target_link_libraries(ger_lua PUBLIC ger_core)

set_target_properties(ger_lua PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
)