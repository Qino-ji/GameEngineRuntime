#include "core/core_input.h"

#if defined(GER_OS_WIN)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct ger_input {
    ger_u8 keys_down[GER_KEY_COUNT];
    ger_u8 keys_pressed[GER_KEY_COUNT];
    ger_u8 keys_released[GER_KEY_COUNT];
    ger_u8 mouse_down[GER_MOUSE_COUNT];
    ger_u8 mouse_pressed[GER_MOUSE_COUNT];
    ger_f32 mouse_x;
    ger_f32 mouse_y;
    ger_f32 mouse_dx;
    ger_f32 mouse_dy;
    ger_f32 scroll_delta;
};
#endif

#if defined(GER_OS_WIN)
ger_error_t ger_input_create(ger_input_t** out) {
    ger_input_t* in = (ger_input_t*)calloc(1, sizeof(ger_input_t));
    if (!in) return GER_ERR_OUT_OF_MEMORY;
    *out = in;
    return GER_OK;
}

void ger_input_destroy(ger_input_t* in) {
    free(in);
}

void ger_input_begin_frame(ger_input_t* in) {
    for (int i = 0; i < GER_KEY_COUNT; i++) {
        in->keys_pressed[i] = 0;
        in->keys_released[i] = 0;
    }
    for (int i = 0; i < GER_MOUSE_COUNT; i++) {
        in->mouse_pressed[i] = 0;
    }
    in->scroll_delta = 0.0f;
}

void ger_input_end_frame(ger_input_t* in) {
    in->mouse_dx = 0.0f;
    in->mouse_dy = 0.0f;
}

void ger_input_set_key_state(ger_input_t* in, ger_key_t key, ger_u8 down) {
    if (down && !in->keys_down[key]) in->keys_pressed[key] = 1;
    if (!down && in->keys_down[key]) in->keys_released[key] = 1;
    in->keys_down[key] = down;
}

ger_u8 ger_input_is_key_down(ger_input_t* in, ger_key_t key) {
    return in->keys_down[key];
}

ger_u8 ger_input_is_key_pressed(ger_input_t* in, ger_key_t key) {
    return in->keys_pressed[key];
}

ger_u8 ger_input_is_key_released(ger_input_t* in, ger_key_t key) {
    return in->keys_released[key];
}

void ger_input_get_mouse_pos(ger_input_t* in, ger_f32* x, ger_f32* y) {
    if (x) *x = in->mouse_x;
    if (y) *y = in->mouse_y;
}

void ger_input_get_mouse_delta(ger_input_t* in, ger_f32* dx, ger_f32* dy) {
    if (dx) *dx = in->mouse_dx;
    if (dy) *dy = in->mouse_dy;
}

ger_f32 ger_input_get_scroll_delta(ger_input_t* in) {
    return in->scroll_delta;
}

ger_u8 ger_input_is_mouse_down(ger_input_t* in, ger_mouse_button_t btn) {
    return in->mouse_down[btn];
}

ger_u8 ger_input_is_mouse_pressed(ger_input_t* in, ger_mouse_button_t btn) {
    return in->mouse_pressed[btn];
}
#else
ger_error_t ger_input_create(ger_input_t** out) { (void)out; return GER_ERR_UNSUPPORTED; }
void ger_input_destroy(ger_input_t* in) { (void)in; }
void ger_input_begin_frame(ger_input_t* in) { (void)in; }
void ger_input_end_frame(ger_input_t* in) { (void)in; }
ger_u8 ger_input_is_key_down(ger_input_t* in, ger_key_t key) { (void)in; (void)key; return 0; }
ger_u8 ger_input_is_key_pressed(ger_input_t* in, ger_key_t key) { (void)in; (void)key; return 0; }
ger_u8 ger_input_is_key_released(ger_input_t* in, ger_key_t key) { (void)in; (void)key; return 0; }
void ger_input_get_mouse_pos(ger_input_t* in, ger_f32* x, ger_f32* y) { (void)in; if(x)*x=0; if(y)*y=0; }
void ger_input_get_mouse_delta(ger_input_t* in, ger_f32* dx, ger_f32* dy) { (void)in; if(dx)*dx=0; if(dy)*dy=0; }
ger_f32 ger_input_get_scroll_delta(ger_input_t* in) { (void)in; return 0; }
ger_u8 ger_input_is_mouse_down(ger_input_t* in, ger_mouse_button_t btn) { (void)in; (void)btn; return 0; }
ger_u8 ger_input_is_mouse_pressed(ger_input_t* in, ger_mouse_button_t btn) { (void)in; (void)btn; return 0; }
#endif
