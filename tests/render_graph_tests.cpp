#include "engine/render_graph.hpp"
#include <cassert>
#include <functional>

int main() {
    RenderGraph graph;
    bool executed = false;
    graph.add_pass(RenderGraph::Pass{
        "test_pass",
        WGPURenderPassColorAttachment{},
        [&executed](WGPURenderPassEncoder) { executed = true; }
    });
    assert(graph.pass_count_for_test() == 1);
    graph.reset();
    assert(graph.pass_count_for_test() == 0);
    return executed ? 1 : 0;
}
