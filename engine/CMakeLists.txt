cmake_minimum_required(VERSION 3.28)
project(ger_engine CXX)

set(ENGINE_SRC
    src/wgpu_context.cpp
    src/wgpu_swapchain.cpp
    src/wgpu_shader.cpp
    src/render_graph.cpp
)

add_library(ger_engine STATIC ${ENGINE_SRC})
target_include_directories(ger_engine PUBLIC include
    PRIVATE ${CMAKE_SOURCE_DIR}/_deps/wgpu-native/ffi
    PRIVATE ${CMAKE_SOURCE_DIR}/_deps/wgpu-native/ffi/webgpu-headers
)
target_link_libraries(ger_engine PUBLIC ger_core)

set_target_properties(ger_engine PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)