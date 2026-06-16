cmake_minimum_required(VERSION 3.28)
project(ger_core C)

set(CORE_SRC
    src/core_file.c
    src/core_time.c
    src/core_thread.c
    src/core_memory.c
    src/core_log.c
)

if(WIN32)
    list(APPEND CORE_SRC src/win32/core_window.c src/win32/core_input.c)
elseif(APPLE)
    list(APPEND CORE_SRC src/macos/core_window.c src/macos/core_input.c)
else()
    list(APPEND CORE_SRC src/linux/core_window.c src/linux/core_input.c)
endif()

add_library(ger_core STATIC ${CORE_SRC})
target_include_directories(ger_core PUBLIC include)

if(WIN32)
    target_compile_definitions(ger_core PRIVATE GER_OS_WIN)
elseif(APPLE)
    target_compile_definitions(ger_core PRIVATE GER_OS_MAC)
else()
    target_compile_definitions(ger_core PRIVATE GER_OS_LINUX)
endif()

set_target_properties(ger_core PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
)