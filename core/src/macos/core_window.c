#include "core/core_platform.h"
#include "core/core_input.h"
#include "core/core_window.h"

ger_error_t ger_window_create(ger_window_desc_t* desc, ger_window_t** out) {
    if (!desc || !out) return GER_ERR_INVALID_ARG;
    *out = 0;
    return GER_ERR_UNSUPPORTED;
}

void ger_window_destroy(ger_window_t* win) {
    (void)win;
}

void ger_window_poll_events(ger_window_t* win) {
    (void)win;
}

void ger_window_request_close(ger_window_t* win) {
    (void)win;
}

int ger_window_should_close(ger_window_t* win) {
    (void)win;
    return 1;
}

uintptr_t ger_window_get_native_handle(ger_window_t* win) {
    (void)win;
    return 0;
}

ger_error_t ger_input_create(ger_input_t** out) {
    if (!out) return GER_ERR_INVALID_ARG;
    *out = 0;
    return GER_ERR_UNSUPPORTED;
}

void ger_input_destroy(ger_input_t* input) {
    (void)input;
}

void ger_input_begin_frame(ger_input_t* input) {
    (void)input;
}

void ger_input_end_frame(ger_input_t* input) {
    (void)input;
}

int ger_input_is_key_down(ger_input_t* input, ger_key_t key) {
    (void)input;
    (void)key;
    return 0;
}

int ger_input_is_mouse_button_down(ger_input_t* input, ger_mouse_button_t button) {
    (void)input;
    (void)button;
    return 0;
}

void ger_input_set_key_state(ger_input_t* input, ger_key_t key, int down) {
    (void)input;
    (void)key;
    (void)down;
}
