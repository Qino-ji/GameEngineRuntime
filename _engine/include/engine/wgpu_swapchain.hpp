#ifndef WGPU_SWAPCHAIN_HPP
#define WGPU_SWAPCHAIN_HPP

#include "wgpu_context.hpp"

struct WGPUSwapchain {
    WGPUSurface surface;
    void* swap_chain;
    uint32_t width;
    uint32_t height;

    static WGPUSwapchain create(WGPUContext& ctx, void* native_handle, uint32_t w, uint32_t h);
    WGPUTextureView get_next_texture(WGPUContext& ctx);
    void present(WGPUContext& ctx);
    void resize(WGPUContext& ctx, uint32_t w, uint32_t h);
    void destroy(WGPUContext& ctx);
};

#endif