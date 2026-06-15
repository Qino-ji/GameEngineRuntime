#ifndef WGPU_BUFFER_HPP
#define WGPU_BUFFER_HPP

#include "wgpu_context.hpp"

struct WGPUBuffer {
    WGPUBuffer handle;
    uint64_t size;

    static WGPUBuffer create(WGPUContext& ctx, uint64_t size, WGPUBufferUsageFlags usage, const void* data);
    void destroy(WGPUContext& ctx);
    void upload(WGPUContext& ctx, const void* data, uint64_t size);
};

#endif