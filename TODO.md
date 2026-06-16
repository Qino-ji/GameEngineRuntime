# GameEngineRuntime TODO

สถานะล่าสุด: 2026-06-16 20:06 +07:00

## เป้าหมาย

สร้าง Game Engine Runtime ที่เบา เร็ว ปลอดภัย และพกพาได้ โดยใช้:

- D สำหรับ public API, orchestration, ECS, asset management, 2D engine
- C++ สำหรับ wgpu engine, render graph, GPU hot path
- C สำหรับ PAL, FFI boundary, Lua host
- wgpu-native สำหรับ rendering
- Lua สำหรับ scripting
- โครงสร้าง `_api` / `_core` แยกชั้นให้ชัดเจน

## สถานะปัจจุบัน

### ผ่านแล้ว

- โครงสร้าง folder หลักเริ่มถูกจัดใหม่เป็น:
  - `api/`
  - `core/`
  - `engine/`
  - `engine2d/`
  - `lua_host/`
  - `runtime/`
- CMake configure/build ผ่านบน Windows
- Dub package ทำงานได้แล้ว:
  - `api`
  - `engine2d`
  - `runtime`
- `api` Dub test ผ่านแล้ว
- `engine2d` Dub test ผ่านแล้ว
- `runtime` Dub build ผ่านแล้ว
- Runtime smoke test ผ่านในระดับ process:
  - `runtime\ger_runtime.exe` เปิด process ได้และไม่ crash ทันที

### ยังขาด

- public API modules หลายตัว
- 2D engine modules เกือบทั้งหมด
- GPU pipeline/texture/profiler
- Lua binding system ที่สมบูรณ์
- ECS/assets/scene
- tests/CI
- examples/tools/default assets
- cross-platform backends
- performance measurement

---

# Immediate Housekeeping

## TODO-000: Clean artifacts และ commit structure rename

สถานะ: ต้องทำ

### งาน

- ลบ generated artifacts จาก:
  - `api/`
  - `engine2d/`
  - `runtime/`
  - `build/`
- ตรวจสอบ `git status --short`
- commit การ rename structure

### คำสั่ง

```powershell
git clean -fdX -- api engine2d runtime
Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue
git status --short
git add .
git commit -m "aura"
```

### Definition of Done

- `git status --short` ไม่แสดง generated artifacts
- commit structure rename ถูกสร้างแล้ว
- build/test ยังผ่านหลังจาก clean แล้ว

---

# Phase 1: Foundation Stabilization

## TODO-001: จัด build system ให้เป็น baseline ที่มั่นคง

สถานะ: ต้องทำ

### งาน

- แก้ `Makefile` ให้ path ใหม่ถูกต้องทั้งหมด
- แก้ `CMakeLists.txt` ให้ build target ชัดเจน
- เพิ่ม top-level Dub config ถ้าต้องการ build D จาก root
- แยก debug/release output path ให้ไม่ปนกับ source
- ลด Dub warning จาก `buildOptions` ถ้าทำได้

### คำสั่งตรวจสอบ

```powershell
cmake -B build
cmake --build build --config Debug

cd api
dub test --force

cd ..\engine2d
dub test --force

cd ..\runtime
dub build --force
.\ger_runtime.exe
```

### Definition of Done

- `cmake --build build --config Debug` ผ่าน
- `dub test` ใน `api` และ `engine2d` ผ่าน
- `dub build` ใน `runtime` ผ่าน
- runtime เปิด process ได้ไม่ crash ทันที
- ไม่มี path เก่า `_api`, `_core`, `_engine`, `_lua_host`, `_2d`, `_runtime` เหลือใน config หลัก

---

## TODO-002: เติม CTest baseline

สถานะ: ต้องทำ

### งาน

- สร้าง `tests/` หรือ `_tests/`
- เพิ่ม CTest root
- เพิ่ม minimal C test สำหรับ:
  - `core_time`
  - `core_file`
  - `core_memory`
- เพิ่ม minimal C++ test สำหรับ:
  - `render_graph`
  - `wgpu_context` แบบ headless ถ้าทำได้
- เพิ่ม minimal D test สำหรับ:
  - `ger_math`
  - `ger_input`
  - `ger_script`

### Definition of Done

- `ctest --test-dir build --output-on-failure` ผ่าน
- D tests ผ่าน
- มี smoke test อย่างน้อย 1 ตัว

---

# Phase 2: Public API Surface

## TODO-003: เติม public API modules ที่ขาด

สถานะ: ต้องทำ

### งาน

สร้าง modules เหล่านี้ใน `api/source/api/`:

- `ger_graphics.d`
- `ger_ecs.d`
- `ger_asset.d`
- `ger_scene.d`
- `ger_2d.d`
- `ger_audio.d`
- `source/api/internal/wgpu_bridge.d`
- `source/api/internal/lua_bridge.d`

### ลำดับแนะนำ

1. `ger_graphics.d`
   - wrapper พื้นฐานสำหรับ graphics context
   - texture/shader/pipeline handle
   - draw call abstraction

2. `ger_asset.d`
   - asset store
   - load file path
   - cache/refcount แบบง่าย

3. `ger_ecs.d`
   - `World`
   - `Entity`
   - basic component registry
   - system loop

4. `ger_scene.d`
   - scene lifecycle
   - entity spawner
   - connect กับ ECS

5. `ger_2d.d`
   - facade ไปยัง `engine2d`
   - sprite/camera/tilemap APIs

6. `ger_audio.d`
   - stub interface ก่อนเชื่อม miniaudio

7. `wgpu_bridge.d`
   - C++ engine wrapper สำหรับ D

8. `lua_bridge.d`
   - Lua host wrapper สำหรับ D

### Definition of Done

- `api` Dub test ผ่าน
- `runtime` Dub build ผ่าน
- `api` สามารถ expose API พื้นฐานโดยไม่ circular dependency

---

# Phase 3: GPU Engine

## TODO-004: เติม engine modules ที่ขาด

สถานะ: ต้องทำ

### งาน

สร้าง modules เหล่านี้ใน `engine/include/engine/` และ `engine/src/`:

- `wgpu_pipeline.hpp/.cpp`
- `wgpu_texture.hpp/.cpp`
- `gpu_profiler.hpp/.cpp`
- `math_simd.hpp/.cpp`

### ลำดับแนะนำ

1. `wgpu_pipeline`
   - vertex layout
   - blend state
   - depth state
   - pipeline creation

2. `wgpu_texture`
   - load KTX2/PNG
   - mip generation
   - texture view/sampler

3. `gpu_profiler`
   - timestamp query
   - frame timing
   - optional Tracy hook

4. `math_simd`
   - vector/matrix helpers
   - SIMD fallback
   - cache-friendly layout

### Definition of Done

- `cmake --build build --config Debug` ผ่าน
- มี unit test สำหรับ pipeline builder
- มี unit test สำหรับ texture metadata
- มี profiler API อย่างน้อยแบบ stub

---

## TODO-005: เติม render graph execution

สถานะ: ต้องทำ

### งาน

- ทำให้ `RenderGraph` สร้าง pass/add resource/execute ได้จริง
- เพิ่ม validation:
  - no missing color attachment
  - no duplicate resource declaration
  - no invalid pass order
- เพิ่ม minimal two-pass test
- เชื่อมกับ `wgpu_swapchain`

### Definition of Done

- render graph สามารถ clear screen ได้
- render graph สามารถ two-pass post process แบบ dummy ได้
- มี C++ test สำหรับ validation

---

# Phase 4: 2D Engine

## TODO-006: เติม 2D engine modules

สถานะ: ต้องทำ

### งาน

สร้าง modules เหล่านี้ใน `engine2d/source/engine2d/`:

- `tilemap.d`
- `camera.d`
- `particle.d`
- `animation.d`
- `text.d`
- `collision.d`
- `layer.d`
- `debug_render.d`

### ลำดับแนะนำ

1. `camera.d`
   - orthographic projection
   - follow mode
   - bounds clamp
   - shake

2. `collision.d`
   - AABB
   - circle
   - line
   - spatial hash stub

3. `layer.d`
   - z-order
   - render queue ordering

4. `tilemap.d`
   - chunked map
   - culling
   - autotile rule stub

5. `animation.d`
   - sprite sheet frame timing

6. `particle.d`
   - CPU emitter stub
   - GPU compute hook later

7. `text.d`
   - bitmap font stub
   - SDF glyph cache later

8. `debug_render.d`
   - wireframe
   - bounds boxes

### Definition of Done

- `engine2d` Dub test ผ่าน
- มี minimal render command ที่ `api` ใช้ได้
- มี collision unit test

---

# Phase 5: Lua Scripting

## TODO-007: เติม Lua binding system

สถานะ: ต้องทำ

### งาน

- เติม `lua_serializer.h/.c`
- เติม `lua_bridge.d`
- sandbox Lua:
  - remove `os.execute`
  - remove `io.*`
  - remove `loadfile`
  - remove `dofile`
  - expose `ger.*`
- เพิ่ม `ger.log()`
- เพิ่ม `ger.input_is_key_down()`
- เพิ่ม `ger.sprite_create()` stub
- เพิ่ม `update(dt)` loop

### Definition of Done

- Lua script เรียก `ger.log()` ได้
- Lua script เรียก `ger.input_is_key_down()` ได้
- sandbox ป้องกัน `os.execute` และ `io.open`
- มี Lua integration test

---

# Phase 6: ECS, Assets, Scene

## TODO-008: เติม ECS พื้นฐาน

สถานะ: ต้องทำ

### งาน

- `World`
- `Entity`
- component registry
- archetype หรือ sparse-set อย่างง่าย
- system loop
- query API

### Definition of Done

- สร้าง entity ได้
- เพิ่ม component ได้
- system iterate over entities ได้
- destroy entity ได้
- มี unit test

---

## TODO-009: เติม AssetStore

สถานะ: ต้องทำ

### งาน

- load file
- cache by path
- refcount
- unload
- texture asset stub
- shader asset stub

### Definition of Done

- load file ผ่าน
- cache path ทำงาน
- unload/refcount ทำงาน
- มี unit test

---

## TODO-010: เติม Scene

สถานะ: ต้องทำ

### งาน

- scene lifecycle
- entity spawner
- connect กับ ECS
- connect กับ 2D engine
- save/load JSON stub

### Definition of Done

- scene init/update/shutdown ทำงาน
- spawner สร้าง entity ได้
- มี unit test

---

# Phase 7: Tests, CI, Examples

## TODO-011: สร้าง CI workflow

สถานะ: ต้องทำ

### งาน

สร้าง:

- `.github/workflows/ci.yml`
- `.github/workflows/nightly.yml`

### CI ขั้นต่ำ

- Windows:
  - CMake configure
  - CMake build
  - ctest
  - Dub test `api`
  - Dub test `engine2d`
  - Dub build `runtime`
- Linux/macOS:
  - placeholder workflow หรือ build minimal core ก่อน

### Definition of Done

- CI workflow syntax ผ่าน
- Windows job ทำงานได้บน GitHub Actions

---

## TODO-012: สร้าง examples

สถานะ: ต้องทำ

### งาน

สร้าง:

- `examples/01_clear_screen/`
- `examples/02_sprite_move/`
- `examples/03_tilemap_scroll/`
- `examples/04_lua_game/`
- `examples/05_particles/`

### Definition of Done

- `examples/01_clear_screen` รันได้
- README ในแต่ละ example อธิบายวิธีรัน
- root Makefile มี target `example/01_clear_screen`

---

## TODO-013: สร้าง tools

สถานะ: ต้องทำ

### งาน

สร้าง:

- `tools/shader_compiler.py`
- `tools/pack_assets.py`

### Definition of Done

- shader compiler สามารถ compile WGSL เป็น SPIR-V ได้ถ้า toolchain พร้อม
- asset packer สามารถสร้าง atlas metadata ได้
- root Makefile มี target `tools` หรือ `tools/shader_compiler.py`

---

# Phase 8: Performance and Packaging

## TODO-014: วัด binary size และ memory

สถานะ: ต้องทำ

### งาน

- build release
- strip binary
- วัดขนาด
- วัด RSS idle
- บันทึกผลใน `docs/performance.md` หรือ `README.md`

### Definition of Done

- binary size รู้ค่าจริง
- idle memory รู้ค่าจริง
- target:
  - full wgpu + Lua ≤ 3 MB stripped
  - idle RSS ≤ 10 MB

---

## TODO-015: เติม profiler

สถานะ: ต้องทำ

### งาน

- Tracy optional integration
- GPU timestamp query
- scoped profile macro
- frame time logger

### Definition of Done

- frame time วัดได้
- draw call count นับได้
- GPU timestamp ทำงานเมื่อ backend รองรับ

---

# Cross-Platform Backlog

## TODO-016: Linux backend

สถานะ: ยังไม่เริ่ม

### งาน

- X11 backend
- Wayland backend
- POSIX file/time/thread
- Vulkan/wgpu path

### Definition of Done

- Linux build ผ่าน
- window เปิด/ปิดได้
- input polling ทำงาน

---

## TODO-017: macOS backend

สถานะ: ยังไม่เริ่ม

### งาน

- Cocoa window
- IOKit HID input
- Metal/wgpu path
- POSIX file/time/thread

### Definition of Done

- macOS build ผ่าน
- window เปิด/ปิดได้
- input polling ทำงาน

---

## TODO-018: Web/WASM backend

สถานะ: ยังไม่เริ่ม

### งาน

- Emscripten path
- Canvas surface
- browser events
- WebGPU/wgpu path

### Definition of Done

- WASM build ผ่าน
- browser sample รันได้

---

# Next Actions

## แนะนำให้ทำทันที

1. ทำ `TODO-000` ให้เสร็จก่อน:
   - clean artifacts
   - commit structure rename

2. ทำ `TODO-001` ต่อ:
   - ให้ root build/test เป็น baseline ที่เสถียร

3. ทำ `TODO-003`:
   - เติม public API modules ที่ขาด
   - เริ่มจาก `ger_graphics.d` และ `ger_asset.d`

4. ทำ `TODO-004`:
   - เติม `wgpu_pipeline` และ `wgpu_texture`

5. ทำ `TODO-006`:
   - เติม `camera.d` และ `collision.d` ก่อน
   - เพราะ 2D engine ต้องมี camera/collision ก่อน tilemap/particle/text

6. ทำ `TODO-007`:
   - Lua sandbox + `ger.log()` + `ger.input_is_key_down()`

## ลำดับที่ห้ามข้าม

- อย่าสร้าง 2D renderer ก่อน `ger_graphics`
- อย่าสร้าง Lua game API ก่อน sandbox
- อย่าสร้าง ECS scene ก่อน ECS core
- อย่าเพิ่ม CI ก่อน local build/test baseline ผ่าน
- อย่าเพิ่ม cross-platform ก่อน Windows baseline มั่นคง

## Acceptance Criteria รวม

โปรเจกต์จะถือว่าเข้าใกล้ AGENTS.md ได้มากขึ้นเมื่อ:

- root build/test ทำงานด้วยคำสั่งเดียว
- public API ครบตาม module list
- 2D engine มี camera/collision/sprite/tilemap
- Lua sandbox ทำงานและปลอดภัย
- ECS/assets/scene ทำงานร่วมกันได้
- มี CI workflow
- มี minimal examples
- มี performance baseline
