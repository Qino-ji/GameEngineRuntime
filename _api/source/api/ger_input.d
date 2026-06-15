module api.ger_input;

import api.ger_types;
import core_sys = core;

extern(C) {
    i32 ger_input_create(void** out);
    void ger_input_destroy(void* in);
    void ger_input_begin_frame(void* in);
    void ger_input_end_frame(void* in);
    u8 ger_input_is_key_down(void* in, int key);
    u8 ger_input_is_key_pressed(void* in, int key);
    u8 ger_input_is_key_released(void* in, int key);
    void ger_input_get_mouse_pos(void* in, f32* x, f32* y);
    void ger_input_get_mouse_delta(void* in, f32* dx, f32* dy);
    f32 ger_input_get_scroll_delta(void* in);
    u8 ger_input_is_mouse_down(void* in, int btn);
    u8 ger_input_is_mouse_pressed(void* in, int btn);
}

class Input {
    private void* _handle;

    this() {
        ger_input_create(&_handle);
    }

    ~this() {
        if (_handle) ger_input_destroy(_handle);
    }

    void beginFrame() { ger_input_begin_frame(_handle); }
    void endFrame() { ger_input_end_frame(_handle); }

    bool isKeyDown(Key key) { return ger_input_is_key_down(_handle, cast(int)key) != 0; }
    bool isKeyPressed(Key key) { return ger_input_is_key_pressed(_handle, cast(int)key) != 0; }
    bool isKeyReleased(Key key) { return ger_input_is_key_released(_handle, cast(int)key) != 0; }

    Vec2 mousePosition() {
        f32 x, y;
        ger_input_get_mouse_pos(_handle, &x, &y);
        return Vec2(x, y);
    }

    Vec2 mouseDelta() {
        f32 dx, dy;
        ger_input_get_mouse_delta(_handle, &dx, &dy);
        return Vec2(dx, dy);
    }

    f32 scrollDelta() { return ger_input_get_scroll_delta(_handle); }

    bool isMouseDown(MouseButton btn) { return ger_input_is_mouse_down(_handle, cast(int)btn) != 0; }
    bool isMousePressed(MouseButton btn) { return ger_input_is_mouse_pressed(_handle, cast(int)btn) != 0; }
}