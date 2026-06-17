#ifndef WGPU_PROC_TABLE_HPP
#define WGPU_PROC_TABLE_HPP

#include <webgpu.h>

struct WgpuProcTable {
    WGPUProcCommandEncoderBeginRenderPass commandEncoderBeginRenderPass = nullptr;
    WGPUProcRenderPassEncoderEnd renderPassEncoderEnd = nullptr;
    WGPUProcRenderPassEncoderRelease renderPassEncoderRelease = nullptr;

    static WgpuProcTable& instance();
    bool valid() const noexcept;
};

#endif
