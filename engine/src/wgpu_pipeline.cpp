#include "engine/wgpu_pipeline.hpp"

WGPUPipeline WGPUPipeline::create(const WGPUPipelineDesc& desc) {
    WGPUPipeline pipeline = {};
    if (desc.device == nullptr || desc.shader == nullptr) {
        return pipeline;
    }

    WGPUBlendComponent color_blend = {};
    color_blend.operation = WGPUBlendOperation_Add;
    color_blend.srcFactor = WGPUBlendFactor_SrcAlpha;
    color_blend.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;

    WGPUBlendComponent alpha_blend = color_blend;

    WGPUBlendState blend_state = {};
    blend_state.color = color_blend;
    blend_state.alpha = alpha_blend;

    WGPUColorTargetState color_target = WGPU_COLOR_TARGET_STATE_INIT;
    color_target.format = desc.color_format;
    color_target.blend = desc.blend_enabled ? &blend_state : nullptr;

    WGPUStringView main_entry = { "main", WGPU_STRLEN };

    WGPUFragmentState fragment_state = WGPU_FRAGMENT_STATE_INIT;
    fragment_state.module = desc.shader;
    fragment_state.entryPoint = main_entry;
    fragment_state.targetCount = 1;
    fragment_state.targets = &color_target;

    WGPURenderPipelineDescriptor pipeline_desc = WGPU_RENDER_PIPELINE_DESCRIPTOR_INIT;
    pipeline_desc.layout = nullptr;
    pipeline_desc.vertex.module = desc.shader;
    pipeline_desc.vertex.entryPoint = main_entry;
    pipeline_desc.fragment = &fragment_state;

    pipeline.handle = wgpuDeviceCreateRenderPipeline(desc.device, &pipeline_desc);
    return pipeline;
}

void WGPUPipeline::destroy() {
    if (handle != nullptr) {
        wgpuRenderPipelineRelease(handle);
        handle = nullptr;
    }
}
