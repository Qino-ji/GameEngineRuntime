#include "engine/wgpu_texture.hpp"

GpuTexture GpuTexture::create_empty(WGPUDevice device, uint32_t width, uint32_t height) {
    GpuTexture texture = {};
    if (device == nullptr || width == 0 || height == 0) {
        return texture;
    }

    texture.info.width = width;
    texture.info.height = height;
    texture.info.mip_count = 1;
    texture.info.format = WGPUTextureFormat_RGBA8UnormSrgb;

    WGPUTextureDescriptor desc = {};
    desc.usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst;
    desc.dimension = WGPUTextureDimension_2D;
    desc.size.width = width;
    desc.size.height = height;
    desc.size.depthOrArrayLayers = 1;
    desc.mipLevelCount = 1;
    desc.sampleCount = 1;
    desc.format = texture.info.format;

    texture.handle = wgpuDeviceCreateTexture(device, &desc);
    if (texture.handle != nullptr) {
        WGPUTextureViewDescriptor view_desc = {};
        texture.view = wgpuTextureCreateView(texture.handle, &view_desc);
    }
    return texture;
}

GpuTexture GpuTexture::load(WGPUDevice device, const char* path) {
    (void)device;
    (void)path;
    return {};
}

void GpuTexture::destroy() {
    if (sampler != nullptr) {
        wgpuSamplerRelease(sampler);
        sampler = nullptr;
    }
    if (view != nullptr) {
        wgpuTextureViewRelease(view);
        view = nullptr;
    }
    if (handle != nullptr) {
        wgpuTextureRelease(handle);
        handle = nullptr;
    }
    info = {};
}
