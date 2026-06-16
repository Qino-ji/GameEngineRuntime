# Performance Baseline

Current baseline is intentionally lightweight because the project is still in early implementation.

## Build targets

- Runtime binary target: `runtime`
- CMake targets:
  - `ger_core`
  - `ger_engine`
  - `lua`
  - `ger_lua`

## Current goals from AGENTS.md

- Full wgpu + Lua binary: <= 3 MB stripped
- Idle RSS: <= 10 MB
- Frame allocation: single arena reset, < 1 us
- Lua call overhead: < 100 ns once bindings are optimized

## What is measured now

- CMake configure/build smoke test
- Dub test for `api`
- Dub test for `engine2d`
- Dub build for `runtime`
- Runtime process smoke test

## Next metrics to add

- Tracy frame profile
- GPU timestamp query
- Draw call count
- Sprite batch benchmark
- ECS query benchmark
- Lua call benchmark

---

ok?