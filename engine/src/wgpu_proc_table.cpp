#include "engine/wgpu_proc_table.hpp"
#include <string_view>

namespace {
template <typename Proc>
Proc load_proc(const char* name) {
    WGPUStringView proc_name = {name, WGPU_STRLEN};
    return reinterpret_cast<Proc>(wgpuGetProcAddress(proc_name));
}
}

WgpuProcTable& WgpuProcTable::instance() {
    static WgpuProcTable procs;
    return procs;
}

bool WgpuProcTable::valid() const noexcept {
    return commandEncoderBeginRenderPass != nullptr &&
           renderPassEncoderEnd != nullptr &&
           renderPassEncoderRelease != nullptr;
}

#if defined(GER_ENABLE_REAL_WGPU)
WgpuProcTable::WgpuProcTable() {
    commandEncoderBeginRenderPass = load_proc<WGPUProcCommandEncoderBeginRenderPass>("wgpuCommandEncoderBeginRenderPass");
    renderPassEncoderEnd = load_proc<WGPUProcRenderPassEncoderEnd>("wgpuRenderPassEncoderEnd");
    renderPassEncoderRelease = load_proc<WGPUProcRenderPassEncoderRelease>("wgpuRenderPassEncoderRelease");
}
#else
WgpuProcTable::WgpuProcTable() = default;
#endif
