# GameEngineRuntime TODO

Last updated: 2026-06-16 21:45 +07:00

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
- Dub packages build/test:
  - `api`
  - `engine2d`
  - `runtime`
- Runtime opens an 800x600 window and stays alive until closed.
- Runtime now loads Lua scripting from:
  - `runtime/assets/scripts/main.lua`
- Lua sandbox removes:
  - `os.execute`
  - `os.remove`
  - `os.rename`
  - `os.tmpname`
  - `io`
  - `loadfile`
  - `dofile`
- Lua exposes:
  - `ger.log()`
  - `ger.input_is_key_down()`
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

### Verified recently

```powershell
cmake -B build
cmake --build build --config Debug
```

Passed.

```powershell
cd api
dub test --build=debug --force
```

Passed.

```powershell
cd engine2d
dub test --build=debug --force
```

Passed.

```powershell
cd runtime
dub build --build=debug --force
dub test --build=debug --force
```

Passed.

## TODO status

| ID | Area | Status |
|---|---|---|
| TODO-000 | Clean artifacts and commit structure rename | Partially done; final clean/commit still pending |
| TODO-001 | Stable build system | Done for Windows local baseline |
| TODO-002 | CTest baseline | Not done |
| TODO-003 | Public API modules | Mostly stubbed: `ger_2d`, `ger_ecs`, `ger_asset`, `ger_scene`, `lua_bridge` added |
| TODO-004 | Engine modules | Done as compile-safe stubs: pipeline, texture, profiler, math |
| TODO-005 | Render graph execution | Not done |
| TODO-006 | 2D engine modules | Done as compile-safe stubs |
| TODO-007 | Lua binding system | Done for sandbox + `ger.log()` + `ger.input_is_key_down()` + runtime script |
| TODO-008 | ECS | Stub done |
| TODO-009 | AssetStore | Stub done |
| TODO-010 | Scene | Stub done |
| TODO-011 | CI workflow | Done |
| TODO-012 | Examples | Minimal `01_clear_screen` done |
| TODO-013 | Tools | Done |
| TODO-014 | Performance baseline | Doc added; measurements still pending |
| TODO-015 | Profiler | C++ `GPUProfiler` stub done; deeper integration pending |
| TODO-016 | Linux backend | Not done |
| TODO-017 | macOS backend | Not done |
| TODO-018 | Web/WASM backend | Not done |

## Next actions

1. Final clean:
   ```powershell
   git clean -fdX -- api engine2d runtime
   Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue
   ```

2. Final verify:
   ```powershell
   $env:Path = "C:\Program Files\LDC 1.34\bin;" + $env:Path

   cmake -B build
   cmake --build build --config Debug

   cd api
   dub test --build=debug --force

   cd ..\engine2d
   dub test --build=debug --force

   cd ..\runtime
   dub build --build=debug --force
   dub test --build=debug --force
   ```

3. Commit all changes.

## Important note

The runtime now has Lua scripting. The sample script lives at:

```text
runtime/assets/scripts/main.lua
```

It is loaded by:

```text
runtime/source/app.d
```

The exposed Lua API is intentionally small and safe:

```lua
ger.log("hello")
local spaceDown = ger.input_is_key_down("space")
```
