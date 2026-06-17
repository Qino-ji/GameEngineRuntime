#ifndef RENDER_GRAPH_HPP
#define RENDER_GRAPH_HPP

#include "wgpu_context.hpp"
#include <functional>
#include <string_view>
#include <vector>

class RenderGraph {
public:
    struct Pass {
        std::string_view name;
        WGPURenderPassColorAttachment color_attachment;
        std::function<void(WGPURenderPassEncoder)> execute;
    };

    RenderGraph& add_pass(Pass&& pass);
    void execute(WGPUCommandEncoder encoder);
    void reset();
    size_t pass_count_for_test() const noexcept { return passes_.size(); }

private:
    std::vector<Pass> passes_;
};

#endif