#include "engine/wgpu_pipeline.hpp"

WGPUPipeline WGPUPipeline::create(const WGPUPipelineDesc& desc) {
    WGPUPipeline pipeline = {};
    if (desc.device == nullptr || desc.shader == nullptr) {
        return pipeline;
    }

    WGPUColorTargetState color_target = {};
    color_target.format = desc.color_format;
    if (desc.blend_enabled) {
        WGPUBlendComponent blend_component = {};
        blend_component.operation = WGPUBlendOperation_Add;
        blend_component.srcFactor = WGPUBlendFactor_SrcAlpha;
        blend_component.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
        color_target.blend = &blend_component;
    }

    WGPURenderPipelineDescriptor pipeline_desc = {};
    pipeline_desc.layout = nullptr;
    pipeline_desc.vertex.module = desc.shader;
    pipeline_desc.vertex.entryPoint = "main";
    pipeline_desc.fragment.module = desc.shader;
    pipeline_desc.fragment.entryPoint = "main";
    pipeline_desc.fragment.targetCount = 1;
    pipeline_desc.fragment.targets = &color_target;

    pipeline.handle = wgpuDeviceCreateRenderPipeline(desc.device, &pipeline_desc);
    return pipeline;
}

void WGPUPipeline::destroy() {
    if (handle != nullptr) {
        wgpuRenderPipelineRelease(handle);
        handle = nullptr;
    }
}
