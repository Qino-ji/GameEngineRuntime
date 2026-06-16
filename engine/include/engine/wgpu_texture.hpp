#ifndef WGPU_TEXTURE_HPP
#define WGPU_TEXTURE_HPP

#include "wgpu_context.hpp"
#include <cstdint>
#include <string>

enum class WGPUTextureStatus {
    Ok = 0,
    InvalidDevice,
    InvalidPath,
    UnsupportedFormat,
};

struct WGPUTextureInfo {
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t mip_count = 1;
    WGPUTextureFormat format = WGPUTextureFormat_RGBA8UnormSrgb;
};

struct WGPUTexture {
    WGPUTexture handle = nullptr;
    WGPUTextureView view = nullptr;
    WGPUSampler sampler = nullptr;
    WGPUTextureInfo info;

    static WGPUTexture create_empty(WGPUDevice device, uint32_t width, uint32_t height);
    static WGPUTexture load(WGPUDevice device, const char* path);
    void destroy();
    bool valid() const noexcept { return handle != nullptr; }
};

#endif
