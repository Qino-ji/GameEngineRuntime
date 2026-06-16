#ifndef GPU_PROFILER_HPP
#define GPU_PROFILER_HPP

#include <cstdint>

struct GPUFrameStats {
    double cpu_ms = 0.0;
    double gpu_ms = 0.0;
    uint32_t draw_calls = 0;
    uint32_t triangles = 0;
};

class GPUProfiler {
public:
    void begin_frame();
    void end_frame();
    void record_draw_call(uint32_t triangle_count);
    GPUFrameStats snapshot() const noexcept;
    void reset() noexcept;

private:
    uint64_t frame_start_ns_ = 0;
    GPUFrameStats stats_;
};

#endif
