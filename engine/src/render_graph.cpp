#include "engine/render_graph.hpp"
#include <algorithm>

#if defined(GER_ENABLE_REAL_WGPU)
#include "engine/wgpu_proc_table.hpp"
#endif

RenderGraph& RenderGraph::add_pass(Pass&& pass) {
    if (pass.execute) {
        passes_.push_back(std::move(pass));
    }
    return *this;
}

void RenderGraph::execute(WGPUCommandEncoder encoder) {
    if (encoder == nullptr) return;

    for (const Pass& pass : passes_) {
#if defined(GER_ENABLE_REAL_WGPU)
        auto& procs = WgpuProcTable::instance();
        if (!procs.valid()) {
            pass.execute(nullptr);
            continue;
        }

        WGPURenderPassDescriptor render_pass_desc = WGPU_RENDER_PASS_DESCRIPTOR_INIT;
        render_pass_desc.colorAttachmentCount = 1;
        render_pass_desc.colorAttachments = &pass.color_attachment;
        WGPURenderPassEncoder render_pass = procs.commandEncoderBeginRenderPass(encoder, &render_pass_desc);
        if (render_pass == nullptr) continue;
        pass.execute(render_pass);
        procs.renderPassEncoderEnd(render_pass);
        procs.renderPassEncoderRelease(render_pass);
#else
        pass.execute(nullptr);
#endif
    }
}

void RenderGraph::reset() {
    passes_.clear();
}