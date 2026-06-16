#include "engine/gpu_profiler.hpp"
#include <chrono>

namespace {
uint64_t now_ns() {
    using clock = std::chrono::steady_clock;
    return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(
        clock::now().time_since_epoch()).count());
}
}

void GPUProfiler::begin_frame() {
    frame_start_ns_ = now_ns();
}

void GPUProfiler::end_frame() {
    if (frame_start_ns_ != 0) {
        stats_.cpu_ms = static_cast<double>(now_ns() - frame_start_ns_) / 1'000'000.0;
    }
}

void GPUProfiler::record_draw_call(uint32_t triangle_count) {
    stats_.draw_calls += 1;
    stats_.triangles += triangle_count;
}

GPUFrameStats GPUProfiler::snapshot() const noexcept {
    return stats_;
}

void GPUProfiler::reset() noexcept {
    frame_start_ns_ = 0;
    stats_ = {};
}
