Last updated: 2026-06-17 17:36 +07:00

## Project target

Build a light, fast, safe Game Engine Runtime with:

- D for public API, orchestration, ECS, asset management, and 2D engine
- C++ for wgpu engine, render graph, and GPU hot path
- C for PAL, FFI boundary, and Lua host
- Lua scripting through a sandboxed `ger.*` API
- wgpu-native rendering
- Clean `api` / `core` separation

## Current status

### Done

- Folder structure renamed and paths updated:
  - `api/`
  - `core/`
  - `engine/`
  - `engine2d/`
  - `lua_host/`
  - `runtime/`
- CMake baseline builds on Windows.
- CTest baseline passes:
  - `core_tests`
  - `render_graph_tests`
- Dub packages build/test:
  - `api`
  - `engine2d`
  - `runtime`
- Runtime opens an 800x600 window and stays alive until closed.
- Runtime loads Lua scripting from:
  - `runtime/assets/scripts/main.lua`
- Lua sandbox removes:
  - `os.execute`
  - `os.remove`
  - `os.rename`
  - `os.tmpname`
  - `io`
  - `loadfile`
  - `dofile`
- Lua exposes game APIs:
  - `ger.log()`
  - `ger.input_is_key_down()`
  - `ger.sprite_create()`
  - `ger.sprite_set_pos()`
  - `ger.sprite_set_color()`
- 2D engine modules added as compile-safe stubs:
  - `sprite`
  - `camera`
  - `collision`
  - `layer`
  - `tilemap`
  - `animation`
  - `particle`
  - `text`
  - `debug_render`
- API facade added:
  - `ger_2d`
  - `ger_graphics`
  - `ger_ecs`
  - `ger_asset`
  - `ger_scene`
  - `ger_audio`
- ECS/Asset/Scene stubs added:
  - `ger_ecs`
  - `ger_asset`
  - `ger_scene`
- CI workflows added:
  - `.github/workflows/ci.yml`
  - `.github/workflows/nightly.yml`
- Minimal example added:
  - `examples/01_clear_screen`
- Tools added:
  - `tools/shader_compiler.py`
  - `tools/pack_assets.py`
- Performance baseline doc added:
  - `docs/performance.md`
- Profiler stub added:
  - C++ `GPUProfiler`
  - D `WgpuBridge` / `ger_graphics` frame stats API
- Cross-platform stub backends added:
  - `core/src/linux/core_window.c`
  - `core/src/macos/core_window.c`

### TODO status

| ID | Area | Status |
|---|---|---|
| TODO-000 | Clean artifacts and commit structure rename | Pending final clean/commit |
| TODO-001 | Stable build system | Done for Windows local baseline |
| TODO-002 | CTest baseline | Done |
| TODO-003 | Public API modules | Stubbed |
| TODO-004 | Engine modules | Done as stubs |
| TODO-005 | Render graph execution | Done as callback executor |
| TODO-006 | 2D engine modules | Done as stubs |
| TODO-007 | Lua binding system | Done for game scripting foundation |
| TODO-008 | ECS | Stub done |
| TODO-009 | AssetStore | Stub done |
| TODO-010 | Scene | Stub done |
| TODO-011 | CI workflow | Done |
| TODO-012 | Examples | Minimal `01_clear_screen` done |
| TODO-013 | Tools | Done |
| TODO-014 | Performance baseline | Doc added; real measurements pending |
| TODO-015 | Profiler | Stub done; deeper integration pending |
| TODO-016 | Linux backend | Stub only |
| TODO-017 | macOS backend | Stub only |
| TODO-018 | Web/WASM backend | Not done |

## Next actions

1. Rebuild and test after Lua sprite API:
   ```powershell
   $env:Path = "C:\Program Files\LDC 1.34\bin;" + $env:Path

   cmake -B build
   cmake --build build --config Debug
   ctest --test-dir build -C Debug --output-on-failure

   cd api
   dub test --build=debug --force

   cd ..\engine2d
   dub test --build=debug --force

   cd ..\runtime
   dub build --build=debug --force
   dub test --build=debug --force
   ```

2. Clean artifacts:
   ```powershell
   cd ..
   git clean -fdX -- api engine2d runtime
   Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue
   ```

3. Final verify after clean:
   ```powershell
   $env:Path = "C:\Program Files\LDC 1.34\bin;" + $env:Path

   cmake -B build
   cmake --build build --config Debug
   ctest --test-dir build -C Debug --output-on-failure

   cd api
   dub test --build=debug --force

   cd ..\engine2d
   dub test --build=debug --force

   cd ..\runtime
   dub build --build=debug --force
   dub test --build=debug --force
   ```

4. Commit:
   ```powershell
   git add .
   git commit -m "Add Lua game scripting foundation"
   ```

## Lua game scripting

The runtime now loads:

```text
runtime/assets/scripts/main.lua
```

Example API:

```lua
local player = ger.sprite_create()
ger.sprite_set_pos(player, 100, 100)
ger.sprite_set_color(player, 255, 255, 255, 255)

function update(dt)
    ger.log("dt:", dt)
end
```
