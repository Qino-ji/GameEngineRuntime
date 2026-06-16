#ifndef WGPU_SHADER_HPP
#define WGPU_SHADER_HPP

#include "wgpu_context.hpp"
#include <string_view>

struct WGPUShader {
    WGPUShaderModule module;

    static WGPUShader create(WGPUContext& ctx, std::string_view wgsl_source);
    void destroy(WGPUContext& ctx);
};

#endif