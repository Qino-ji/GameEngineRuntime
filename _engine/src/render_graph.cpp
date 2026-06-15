#include "engine/render_graph.hpp"

RenderGraph& RenderGraph::add_pass(Pass&& pass) {
    passes_.push_back(std::move(pass));
    return *this;
}

void RenderGraph::execute(WGPUCommandEncoder encoder) {
    (void)encoder;
}

void RenderGraph::reset() {
    passes_.clear();
}