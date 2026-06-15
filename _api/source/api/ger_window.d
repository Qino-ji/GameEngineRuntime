module api.ger_window;

import api.ger_types;
import core_sys = core;

extern(C) {
    struct ger_window_desc {
        const(char)* title;
        i32 width;
        i32 height;
        u8 fullscreen;
        u8 vsync;
        u8 resizable;
    }

    i32 ger_window_create(ger_window_desc* desc, void** out);
    void ger_window_destroy(void* win);
    void ger_window_poll_events(void* win);
    u8 ger_window_should_close(void* win);
    void ger_window_get_size(void* win, i32* w, i32* h);
    size_t ger_window_get_native_handle(void* win);
}

class Window {
    private void* _handle;
    private int _width;
    private int _height;

    this(string title, int width, int height, bool fullscreen = false, bool vsync = true, bool resizable = false) {
        _width = width;
        _height = height;
        ger_window_desc desc;
        desc.title = title.ptr;
        desc.width = width;
        desc.height = height;
        desc.fullscreen = fullscreen ? 1 : 0;
        desc.vsync = vsync ? 1 : 0;
        desc.resizable = resizable ? 1 : 0;
        auto err = ger_window_create(&desc, &_handle);
        assert(err == GER_OK, "Window creation failed");
    }

    ~this() {
        if (_handle) ger_window_destroy(_handle);
    }

    void pollEvents() {
        ger_window_poll_events(_handle);
    }

    bool shouldClose() {
        return ger_window_should_close(_handle) != 0;
    }

    void getSize(out int w, out int h) {
        ger_window_get_size(_handle, &w, &h);
        _width = w;
        _height = h;
    }

    size_t nativeHandle() {
        return ger_window_get_native_handle(_handle);
    }

    @property int width() { return _width; }
    @property int height() { return _height; }
}