#include "core/core_window.h"

#if defined(GER_OS_WIN)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>

struct ger_window {
    HWND hwnd;
    HDC hdc;
    ger_i32 width;
    ger_i32 height;
    ger_u8 should_close;
};

static LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
    ger_window_t* win = (ger_window_t*)GetWindowLongPtrA(hwnd, GWLP_USERDATA);
    switch (msg) {
        case WM_CLOSE:
            if (win) win->should_close = 1;
            return 0;
        case WM_SIZE: {
            RECT r;
            GetClientRect(hwnd, &r);
            if (win) { win->width = (ger_i32)(r.right - r.left); win->height = (ger_i32)(r.bottom - r.top); }
            return 0;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcA(hwnd, msg, w, l);
}

ger_error_t ger_window_create(ger_window_desc_t* desc, ger_window_t** out) {
    HINSTANCE inst = GetModuleHandleA(0);
    WNDCLASSEXA wc = {0};
    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = wnd_proc;
    wc.hInstance = inst;
    wc.hCursor = LoadCursorA(0, IDC_ARROW);
    wc.lpszClassName = "GER_WINDOW";
    RegisterClassExA(&wc);

    DWORD style = WS_OVERLAPPEDWINDOW;
    if (desc->resizable) style |= WS_SIZEBOX;
    if (desc->fullscreen) style = WS_POPUP | WS_VISIBLE;

    RECT r = {0, 0, desc->width, desc->height};
    AdjustWindowRect(&r, style, 0);

    HWND hwnd = CreateWindowExA(0, "GER_WINDOW", desc->title ? desc->title : "Game",
        style, CW_USEDEFAULT, CW_USEDEFAULT,
        r.right - r.left, r.bottom - r.top,
        0, 0, inst, 0);
    if (!hwnd) return GER_ERR_UNKNOWN;

    ger_window_t* win = (ger_window_t*)calloc(1, sizeof(ger_window_t));
    if (!win) { DestroyWindow(hwnd); return GER_ERR_OUT_OF_MEMORY; }

    win->hwnd = hwnd;
    win->hdc = GetDC(hwnd);
    win->width = desc->width;
    win->height = desc->height;
    win->should_close = 0;
    SetWindowLongPtrA(hwnd, GWLP_USERDATA, (LONG_PTR)win);
    ShowWindow(hwnd, SW_SHOW);
    *out = win;
    return GER_OK;
}

void ger_window_destroy(ger_window_t* win) {
    if (!win) return;
    DestroyWindow(win->hwnd);
    if (win->hdc) ReleaseDC(win->hwnd, win->hdc);
    free(win);
}

void ger_window_poll_events(ger_window_t* win) {
    (void)win;
    MSG msg;
    while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}

ger_u8 ger_window_should_close(ger_window_t* win) {
    return win->should_close;
}

void ger_window_get_size(ger_window_t* win, ger_i32* w, ger_i32* h) {
    if (w) *w = win->width;
    if (h) *h = win->height;
}

uintptr_t ger_window_get_native_handle(ger_window_t* win) {
    return (uintptr_t)win->hwnd;
}

#else
ger_error_t ger_window_create(ger_window_desc_t* desc, ger_window_t** out) { (void)desc; (void)out; return GER_ERR_UNSUPPORTED; }
void ger_window_destroy(ger_window_t* win) { (void)win; }
void ger_window_poll_events(ger_window_t* win) { (void)win; }
ger_u8 ger_window_should_close(ger_window_t* win) { (void)win; return 1; }
void ger_window_get_size(ger_window_t* win, ger_i32* w, ger_i32* h) { (void)win; if(w)*w=800; if(h)*h=600; }
uintptr_t ger_window_get_native_handle(ger_window_t* win) { (void)win; return 0; }
#endif