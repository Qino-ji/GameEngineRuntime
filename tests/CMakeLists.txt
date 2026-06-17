cmake_minimum_required(VERSION 3.28)

include(CTest)

add_executable(core_tests
    core_tests.c
)
target_link_libraries(core_tests PRIVATE ger_core)
target_include_directories(core_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/core/include
)
add_test(NAME core_tests COMMAND core_tests)

add_executable(render_graph_tests
    render_graph_tests.cpp
)
set_target_properties(render_graph_tests PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
target_link_libraries(render_graph_tests PRIVATE ger_engine)
target_include_directories(render_graph_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/engine/include
    ${CMAKE_SOURCE_DIR}/_deps/wgpu-native/ffi
    ${CMAKE_SOURCE_DIR}/_deps/wgpu-native/ffi/webgpu-headers
)
add_test(NAME render_graph_tests COMMAND render_graph_tests)
