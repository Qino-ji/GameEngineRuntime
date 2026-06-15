#ifndef GER_TIME_H
#define GER_TIME_H

#include "core_platform.h"

typedef struct {
    ger_u64 start_ns;
    ger_u64 current_ns;
    ger_f64 delta_s;
} ger_timer_t;

void ger_timer_start(ger_timer_t* t);
void ger_timer_tick(ger_timer_t* t);
ger_f64 ger_timer_get_delta(ger_timer_t* t);
ger_f64 ger_timer_get_elapsed(ger_timer_t* t);
ger_u64 ger_time_now_ns(void);
void ger_time_sleep_ms(ger_u32 ms);

#endif