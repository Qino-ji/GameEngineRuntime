#include "engine/render_graph.hpp"
#include <algorithm>

RenderGraph& RenderGraph::add_pass(Pass&& pass) {
    if (pass.execute) {
        passes_.push_back(std::move(pass));
    }
    return *this;
}

void RenderGraph::execute(WGPUCommandEncoder encoder) {
    (void)encoder;

    for (const Pass& pass : passes_) {
        pass.execute(nullptr);
    }
}

void RenderGraph::reset() {
    passes_.clear();
}