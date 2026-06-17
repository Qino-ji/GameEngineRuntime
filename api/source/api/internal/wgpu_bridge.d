module api.internal.wgpu_bridge;

struct FrameStats {
    double cpuMs;
    double gpuMs;
    uint frameDrawCalls;
    uint frameTriangles;
}

class WgpuBridge {
    private FrameStats _stats;

    void beginFrame() {
        _stats.cpuMs = 0;
        _stats.gpuMs = 0;
        _stats.frameDrawCalls = 0;
        _stats.frameTriangles = 0;
    }

    void endFrame(double cpuMs, double gpuMs) {
        _stats.cpuMs = cpuMs;
        _stats.gpuMs = gpuMs;
    }

    void recordDrawCall(uint triangles) {
        _stats.frameDrawCalls += 1;
        _stats.frameTriangles += triangles;
    }

    FrameStats snapshot() const {
        return _stats;
    }

    void reset() {
        _stats = FrameStats.init;
    }
}
