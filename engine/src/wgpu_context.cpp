#include "engine/wgpu_context.hpp"
#include <cstdlib>

WGPUContext WGPUContext::create(void* native_window_handle, uint32_t width, uint32_t height) {
    WGPUContext ctx = {};
    (void)native_window_handle;
    (void)width;
    (void)height;
    return ctx;
}

void WGPUContext::destroy() {
}