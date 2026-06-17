#include "core/core_memory.h"
#include "core/core_time.h"
#include <assert.h>
#include <stdint.h>

int main(void) {
    unsigned char arena_buffer[1024];
    ger_arena_t arena;
    ger_arena_init(&arena, arena_buffer, sizeof(arena_buffer));
    void* ptr = ger_arena_alloc(&arena, 64, 8);
    assert(ptr != 0);
    ger_arena_reset(&arena);
    void* ptr2 = ger_arena_alloc(&arena, 64, 8);
    assert(ptr == ptr2);

    ger_timer_t timer;
    ger_timer_start(&timer);
    ger_time_sleep_ms(1);
    ger_timer_tick(&timer);
    assert(ger_timer_get_elapsed(&timer) >= 0.0);

    return 0;
}
