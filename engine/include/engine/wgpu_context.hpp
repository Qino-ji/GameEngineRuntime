#ifndef WGPU_CONTEXT_HPP
#define WGPU_CONTEXT_HPP

#include <webgpu.h>
#include <cstdint>

struct WGPUContext {
    WGPUInstance instance;
    WGPUAdapter adapter;
    WGPUDevice device;
    WGPUQueue queue;

    static WGPUContext create(void* native_window_handle, uint32_t width, uint32_t height);
    void destroy();
};

#endif