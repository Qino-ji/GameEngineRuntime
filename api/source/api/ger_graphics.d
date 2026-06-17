module api.ger_graphics;

import api.ger_types;
import api.internal.wgpu_bridge;

struct TextureHandle {
    u32 id;
    bool valid() const { return id != 0; }
}

struct ShaderHandle {
    u32 id;
    bool valid() const { return id != 0; }
}

struct PipelineHandle {
    u32 id;
    bool valid() const { return id != 0; }
}

struct GraphicsContext {
    WgpuBridge profiler;

    void beginFrame() {
        profiler.beginFrame();
    }

    void endFrame(f64 cpuMs, f64 gpuMs) {
        profiler.endFrame(cpuMs, gpuMs);
    }

    void recordDrawCall(uint triangleCount) {
        profiler.recordDrawCall(triangleCount);
    }

    FrameStats frameStats() const {
        return profiler.snapshot();
    }
}

unittest {
    GraphicsContext ctx;
    ctx.beginFrame();
    ctx.recordDrawCall(3);
    ctx.endFrame(1.0, 2.0);
    auto stats = ctx.frameStats();
    assert(stats.frameDrawCalls == 1);
    assert(stats.frameTriangles == 3);
    assert(stats.cpuMs == 1.0);
}
