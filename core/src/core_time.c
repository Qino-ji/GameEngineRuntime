#include "core/core_time.h"

#if defined(GER_OS_WIN)
#include <windows.h>
#elif defined(GER_OS_MAC)
#include <mach/mach_time.h>
#else
#include <time.h>
#include <unistd.h>
#endif

ger_u64 ger_time_now_ns(void) {
#if defined(GER_OS_WIN)
    LARGE_INTEGER freq, count;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&count);
    return (ger_u64)(count.QuadPart * 1000000000ULL / freq.QuadPart);
#elif defined(GER_OS_MAC)
    static mach_timebase_info_data_t info = {0};
    if (info.denom == 0) mach_timebase_info(&info);
    ger_u64 ticks = mach_absolute_time();
    return ticks * info.numer / info.denom;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ger_u64)ts.tv_sec * 1000000000ULL + (ger_u64)ts.tv_nsec;
#endif
}

void ger_time_sleep_ms(ger_u32 ms) {
#if defined(GER_OS_WIN)
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

void ger_timer_start(ger_timer_t* t) {
    t->start_ns = ger_time_now_ns();
    t->current_ns = t->start_ns;
    t->delta_s = 0.0;
}

void ger_timer_tick(ger_timer_t* t) {
    ger_u64 now = ger_time_now_ns();
    t->delta_s = (ger_f64)(now - t->current_ns) / 1000000000.0;
    t->current_ns = now;
}

ger_f64 ger_timer_get_delta(ger_timer_t* t) {
    return t->delta_s;
}

ger_f64 ger_timer_get_elapsed(ger_timer_t* t) {
    return (ger_f64)(t->current_ns - t->start_ns) / 1000000000.0;
}