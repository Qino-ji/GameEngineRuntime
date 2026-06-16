#ifndef WGPU_PIPELINE_HPP
#define WGPU_PIPELINE_HPP

#include "wgpu_context.hpp"
#include <cstdint>

enum class WGPUPipelineStatus {
    Ok = 0,
    InvalidDevice,
    InvalidShaderModule,
};

struct WGPUVertexLayout {
    const char* shader_location_name = nullptr;
    uint32_t location = 0;
    WGPUVertexFormat format = WGPUVertexFormat_Float32x2;
    uint64_t offset = 0;
};

struct WGPUPipelineDesc {
    WGPUDevice device = nullptr;
    WGPUShaderModule shader = nullptr;
    WGPUTextureFormat color_format = WGPUTextureFormat_RGBA8UnormSrgb;
    bool blend_enabled = false;
    bool depth_enabled = false;
};

struct WGPUPipeline {
    WGPURenderPipeline handle = nullptr;

    static WGPUPipeline create(const WGPUPipelineDesc& desc);
    void destroy();
    bool valid() const noexcept { return handle != nullptr; }
};

#endif
