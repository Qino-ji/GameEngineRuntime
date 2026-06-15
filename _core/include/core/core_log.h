#ifndef GER_LOG_H
#define GER_LOG_H

#include "core_platform.h"

#define LOG_D(fmt, ...) ger_log_write(GER_LOG_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_I(fmt, ...) ger_log_write(GER_LOG_INFO, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_W(fmt, ...) ger_log_write(GER_LOG_WARN, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_E(fmt, ...) ger_log_write(GER_LOG_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

typedef enum {
    GER_LOG_DEBUG,
    GER_LOG_INFO,
    GER_LOG_WARN,
    GER_LOG_ERROR,
} ger_log_level_t;

void ger_log_write(ger_log_level_t level, const char* file, int line, const char* fmt, ...);

#endif