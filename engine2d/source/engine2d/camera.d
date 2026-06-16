module engine2d.camera;

import api.ger_types;

enum CameraFollowMode {
    none,
    lerp,
    instant,
    boundsClamped,
}

struct Camera {
    Vec2 position;
    f32 zoom;
    f32 rotation;
    f32 width;
    f32 height;
    CameraFollowMode followMode;
    f32 followLerp;
    Rect bounds;
    Vec2 shakeOffset;

    static Camera create(f32 viewportWidth, f32 viewportHeight) {
        Camera camera;
        camera.position = Vec2(0, 0);
        camera.zoom = 1;
        camera.rotation = 0;
        camera.width = viewportWidth;
        camera.height = viewportHeight;
        camera.followMode = CameraFollowMode.none;
        camera.followLerp = 8;
        camera.bounds = Rect(-1000, -1000, 2000, 2000);
        camera.shakeOffset = Vec2(0, 0);
        return camera;
    }

    Vec2 worldToScreen(Vec2 world) {
        return Vec2((world.x - position.x) * zoom + width * 0.5f,
                    (world.y - position.y) * zoom + height * 0.5f);
    }

    Vec2 screenToWorld(Vec2 screen) {
        return Vec2((screen.x - width * 0.5f) / zoom + position.x,
                    (screen.y - height * 0.5f) / zoom + position.y);
    }

    Rect boundsInWorld() {
        return Rect(position.x - width * 0.5f / zoom,
                    position.y - height * 0.5f / zoom,
                    width / zoom,
                    height / zoom);
    }

    void setViewport(f32 w, f32 h) {
        width = w;
        height = h;
    }

    void setZoom(f32 z) {
        zoom = z > 0.001f ? z : 1;
    }

    void follow(Vec2 target, f32 dt) {
        Vec2 next = target;
        if (followMode == CameraFollowMode.lerp) {
            f32 t = 1 - __pow(__e(-followLerp * dt));
            next = Vec2(position.x + (target.x - position.x) * t,
                        position.y + (target.y - position.y) * t);
        }
        if (followMode == CameraFollowMode.boundsClamped) {
            next = clampToBounds(next);
        }
        position = next;
    }

    void addShake(f32 x, f32 y) {
        shakeOffset = Vec2(x, y);
    }

    void clearShake() {
        shakeOffset = Vec2(0, 0);
    }

private:
    Vec2 clampToBounds(Vec2 p) {
        Vec2 result = p;
        if (result.x < bounds.x) result.x = bounds.x;
        if (result.y < bounds.y) result.y = bounds.y;
        if (result.x > bounds.x + bounds.w) result.x = bounds.x + bounds.w;
        if (result.y > bounds.y + bounds.h) result.y = bounds.y + bounds.h;
        return result;
    }
}

private f32 __e(f32 x) {
    import core.stdc.math : expf;
    return expf(x);
}

private f32 __pow(f32 x) {
    import core.stdc.math : powf;
    return powf(x, 1);
}

unittest {
    auto camera = Camera.create(800, 600);
    camera.setZoom(2);
    camera.follow(Vec2(10, 20), 0.016f);
    assert(camera.width == 800);
    assert(camera.height == 600);
    assert(camera.zoom == 2);
}
