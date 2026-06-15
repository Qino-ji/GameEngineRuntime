#ifndef GER_INPUT_H
#define GER_INPUT_H

#include "core_platform.h"

typedef struct ger_input ger_input_t;

typedef enum {
    GER_KEY_UNKNOWN,
    GER_KEY_SPACE,
    GER_KEY_ENTER,
    GER_KEY_ESCAPE,
    GER_KEY_BACKSPACE,
    GER_KEY_TAB,
    GER_KEY_LEFT,
    GER_KEY_RIGHT,
    GER_KEY_UP,
    GER_KEY_DOWN,
    GER_KEY_W,
    GER_KEY_A,
    GER_KEY_S,
    GER_KEY_D,
    GER_KEY_COUNT,
} ger_key_t;

typedef enum {
    GER_MOUSE_LEFT,
    GER_MOUSE_RIGHT,
    GER_MOUSE_MIDDLE,
    GER_MOUSE_COUNT,
} ger_mouse_button_t;

ger_error_t ger_input_create(ger_input_t** out);
void ger_input_destroy(ger_input_t* in);
void ger_input_begin_frame(ger_input_t* in);
void ger_input_end_frame(ger_input_t* in);
ger_u8 ger_input_is_key_down(ger_input_t* in, ger_key_t key);
ger_u8 ger_input_is_key_pressed(ger_input_t* in, ger_key_t key);
ger_u8 ger_input_is_key_released(ger_input_t* in, ger_key_t key);
void ger_input_get_mouse_pos(ger_input_t* in, ger_f32* x, ger_f32* y);
void ger_input_get_mouse_delta(ger_input_t* in, ger_f32* dx, ger_f32* dy);
ger_f32 ger_input_get_scroll_delta(ger_input_t* in);
ger_u8 ger_input_is_mouse_down(ger_input_t* in, ger_mouse_button_t btn);
ger_u8 ger_input_is_mouse_pressed(ger_input_t* in, ger_mouse_button_t btn);

#endif