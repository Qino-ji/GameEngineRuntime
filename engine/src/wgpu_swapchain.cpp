#include "engine/wgpu_swapchain.hpp"

WGPUSwapchain WGPUSwapchain::create(WGPUContext& ctx, void* native_handle, uint32_t w, uint32_t h) {
    (void)ctx;
    (void)native_handle;
    WGPUSwapchain sc = {};
    sc.width = w;
    sc.height = h;
    return sc;
}

WGPUTextureView WGPUSwapchain::get_next_texture(WGPUContext& ctx) {
    (void)ctx;
    return nullptr;
}

void WGPUSwapchain::present(WGPUContext& ctx) {
    (void)ctx;
}

void WGPUSwapchain::resize(WGPUContext& ctx, uint32_t w, uint32_t h) {
    (void)ctx;
    width = w;
    height = h;
}

void WGPUSwapchain::destroy(WGPUContext& ctx) {
    (void)ctx;
}