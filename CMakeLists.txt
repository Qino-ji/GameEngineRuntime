cmake_minimum_required(VERSION 3.28)
project(GameEngineRuntime)

include(CTest)

add_subdirectory(core)
add_subdirectory(engine)
add_subdirectory(lua_host)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()