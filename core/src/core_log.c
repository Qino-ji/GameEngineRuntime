#include "core/core_log.h"
#include <stdio.h>
#include <stdarg.h>

static const char* level_strings[] = {
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
};

void ger_log_write(ger_log_level_t level, const char* file, int line, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "[%s] %s:%d: ", level_strings[level], file, line);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}