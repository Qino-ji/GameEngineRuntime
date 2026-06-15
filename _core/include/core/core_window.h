#ifndef GER_WINDOW_H
#define GER_WINDOW_H

#include "core_platform.h"

typedef struct ger_window ger_window_t;

typedef struct {
    const char* title;
    ger_i32 width;
    ger_i32 height;
    ger_u8 fullscreen;
    ger_u8 vsync;
    ger_u8 resizable;
} ger_window_desc_t;

ger_error_t ger_window_create(ger_window_desc_t* desc, ger_window_t** out);
void ger_window_destroy(ger_window_t* win);
void ger_window_poll_events(ger_window_t* win);
ger_u8 ger_window_should_close(ger_window_t* win);
void ger_window_get_size(ger_window_t* win, ger_i32* w, ger_i32* h);
uintptr_t ger_window_get_native_handle(ger_window_t* win);

#endif