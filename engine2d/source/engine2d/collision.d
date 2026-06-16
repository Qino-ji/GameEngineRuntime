module engine2d.collision;

import api.ger_types;

enum ShapeType {
    aabb,
    circle,
    line,
}

struct CollisionShape {
    ShapeType type;
    Rect bounds;
    Vec2 center;
    f32 radius;
    Vec2 a;
    Vec2 b;
}

struct CollisionContact {
    u8 hit;
    Vec2 normal;
    f32 penetration;
}

CollisionShape aabbShape(Rect r) {
    CollisionShape shape;
    shape.type = ShapeType.aabb;
    shape.bounds = r;
    return shape;
}

CollisionShape circleShape(Vec2 center, f32 radius) {
    CollisionShape shape;
    shape.type = ShapeType.circle;
    shape.center = center;
    shape.radius = radius;
    return shape;
}

CollisionContact collideAabb(Rect a, Rect b) {
    CollisionContact contact;
    contact.hit = 0;
    contact.normal = Vec2(0, 0);
    contact.penetration = 0;

    f32 ax = a.x + a.w * 0.5f;
    f32 ay = a.y + a.h * 0.5f;
    f32 bx = b.x + b.w * 0.5f;
    f32 by = b.y + b.h * 0.5f;
    f32 dx = bx - ax;
    f32 dy = by - ay;
    f32 px = (a.w + b.w) * 0.5f - absf(dx);
    f32 py = (a.h + b.h) * 0.5f - absf(dy);

    if (px > 0 && py > 0) {
        contact.hit = 1;
        if (px < py) {
            contact.penetration = px;
            contact.normal = dx < 0 ? Vec2(-1, 0) : Vec2(1, 0);
        } else {
            contact.penetration = py;
            contact.normal = dy < 0 ? Vec2(0, -1) : Vec2(0, 1);
        }
    }
    return contact;
}

CollisionContact collideShapes(CollisionShape a, CollisionShape b) {
    if (a.type == ShapeType.aabb && b.type == ShapeType.aabb) {
        return collideAabb(a.bounds, b.bounds);
    }
    if (a.type == ShapeType.circle && b.type == ShapeType.circle) {
        f32 dx = b.center.x - a.center.x;
        f32 dy = b.center.y - a.center.y;
        f32 r = a.radius + b.radius;
        f32 distSq = dx * dx + dy * dy;
        CollisionContact contact;
        if (distSq <= r * r) {
            contact.hit = 1;
            contact.normal = Vec2(dx, dy);
            contact.penetration = r - sqrtf(distSq);
        }
        return contact;
    }
    return CollisionContact();
}

private f32 absf(f32 v) {
    return v < 0 ? -v : v;
}

private f32 sqrtf(f32 v) {
    import core.stdc.math;
    return sqrtf(v);
}

unittest {
    auto a = Rect(0, 0, 10, 10);
    auto b = Rect(5, 5, 10, 10);
    auto hit = collideAabb(a, b);
    assert(hit.hit == 1);
    assert(hit.penetration > 0);
}
