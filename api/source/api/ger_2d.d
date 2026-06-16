module api.ger_2d;

import api.ger_types;

struct SpriteHandle {
    u32 id;
    bool valid() const { return id != 0; }
}

struct Camera2D {
    Vec2 position;
    f32 zoom;
    Rect bounds;

    static Camera2D create(f32 width, f32 height) {
        Camera2D camera;
        camera.position = Vec2(0, 0);
        camera.zoom = 1;
        camera.bounds = Rect(-width * 0.5f, -height * 0.5f, width, height);
        return camera;
    }
}

struct TilemapHandle {
    u32 id;
    bool valid() const { return id != 0; }
}

struct ParticleEmitterHandle {
    u32 id;
    bool valid() const { return id != 0; }
}

enum DebugDrawMode {
    off,
    bounds,
    collision,
    particles,
}

struct DebugRenderSettings {
    DebugDrawMode mode;
    Color boundsColor;
    Color collisionColor;
    bool showGrid;
    f32 gridSize;

    static DebugRenderSettings create() {
        DebugRenderSettings settings;
        settings.mode = DebugDrawMode.off;
        settings.boundsColor = Color(0, 255, 0, 255);
        settings.collisionColor = Color(255, 0, 0, 255);
        settings.showGrid = false;
        settings.gridSize = 32;
        return settings;
    }
}

SpriteHandle sprite_create() {
    return SpriteHandle(1);
}

void sprite_set_position(ref SpriteHandle sprite, Vec2 position) {
    sprite.id = sprite.valid ? sprite.id : 1;
    cast(void)position;
}

Camera2D camera_create(f32 width, f32 height) {
    return Camera2D.create(width, height);
}

TilemapHandle tilemap_create(u16 width, u16 height) {
    cast(void)width;
    cast(void)height;
    return TilemapHandle(1);
}

ParticleEmitterHandle particle_emitter_create() {
    return ParticleEmitterHandle(1);
}

DebugRenderSettings debug_settings_create() {
    return DebugRenderSettings.create();
}

unittest {
    auto sprite = sprite_create();
    assert(sprite.valid);
    sprite_set_position(sprite, Vec2(10, 20));
    auto camera = camera_create(800, 600);
    assert(camera.zoom == 1);
    assert(tilemap_create(16, 16).valid);
    assert(particle_emitter_create().valid);
}
