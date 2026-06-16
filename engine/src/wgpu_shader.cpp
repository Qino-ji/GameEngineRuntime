#include "engine/wgpu_shader.hpp"
#include <string_view>

WGPUShader WGPUShader::create(WGPUContext& ctx, std::string_view wgsl_source) {
    (void)ctx;
    (void)wgsl_source;
    WGPUShader shader = {};
    return shader;
}

void WGPUShader::destroy(WGPUContext& ctx) {
    (void)ctx;
}