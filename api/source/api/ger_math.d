module api.ger_math;

import api.ger_types;

Vec2 vec2(f32 x, f32 y) {
    return Vec2(x, y);
}

Vec2 vec2_add(Vec2 a, Vec2 b) {
    return Vec2(a.x + b.x, a.y + b.y);
}

Vec2 vec2_sub(Vec2 a, Vec2 b) {
    return Vec2(a.x - b.x, a.y - b.y);
}

Vec2 vec2_scale(Vec2 v, f32 s) {
    return Vec2(v.x * s, v.y * s);
}

f32 vec2_dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

f32 vec2_length(Vec2 v) {
    import core.stdc.math;
    return sqrtf(v.x * v.x + v.y * v.y);
}

Vec2 vec2_normalize(Vec2 v) {
    f32 len = vec2_length(v);
    if (len > 0.0001f) return Vec2(v.x / len, v.y / len);
    return Vec2(0, 0);
}

struct Mat3 {
    f32[9] data;
}

Mat3 mat3_identity() {
    Mat3 m;
    m.data[0] = 1; m.data[4] = 1; m.data[8] = 1;
    return m;
}

Mat3 mat3_translate(f32 tx, f32 ty) {
    Mat3 m = mat3_identity();
    m.data[6] = tx;
    m.data[7] = ty;
    return m;
}

Mat3 mat3_scale(f32 sx, f32 sy) {
    Mat3 m;
    m.data[0] = sx; m.data[4] = sy; m.data[8] = 1;
    return m;
}

Vec2 mat3_mul_vec2(Mat3 m, Vec2 v) {
    return Vec2(
        m.data[0] * v.x + m.data[3] * v.y + m.data[6],
        m.data[1] * v.x + m.data[4] * v.y + m.data[7]
    );
}

Rect rect(f32 x, f32 y, f32 w, f32 h) {
    return Rect(x, y, w, h);
}

u8 rect_contains(Rect r, Vec2 p) {
    return (p.x >= r.x && p.x <= r.x + r.w && p.y >= r.y && p.y <= r.y + r.h);
}

Color color(u8 r, u8 g, u8 b, u8 a) {
    return Color(r, g, b, a);
}