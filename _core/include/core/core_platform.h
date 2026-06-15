#ifndef GER_PLATFORM_H
#define GER_PLATFORM_H

#if defined(_WIN32) || defined(_WIN64)
#define GER_OS_WIN 1
#elif defined(__APPLE__)
#define GER_OS_MAC 1
#else
#define GER_OS_LINUX 1
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef int8_t ger_i8;
typedef uint8_t ger_u8;
typedef int16_t ger_i16;
typedef uint16_t ger_u16;
typedef int32_t ger_i32;
typedef uint32_t ger_u32;
typedef int64_t ger_i64;
typedef uint64_t ger_u64;
typedef float ger_f32;
typedef double ger_f64;

typedef enum {
    GER_OK = 0,
    GER_ERR_UNKNOWN,
    GER_ERR_OUT_OF_MEMORY,
    GER_ERR_INVALID_ARG,
    GER_ERR_NOT_FOUND,
    GER_ERR_IO,
    GER_ERR_UNSUPPORTED,
    GER_ERR_ALREADY_EXISTS,
    GER_ERR_TIMEOUT,
} ger_error_t;

#endif