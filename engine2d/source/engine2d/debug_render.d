module engine2d.debug_render;

import api.ger_types;

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

unittest {
    auto settings = DebugRenderSettings.create();
    assert(settings.showGrid == false);
    assert(settings.gridSize == 32);
}
