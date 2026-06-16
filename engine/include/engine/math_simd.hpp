#ifndef MATH_SIMD_HPP
#define MATH_SIMD_HPP

#include <cstdint>

namespace ger {
namespace math {

struct Vec2 {
    float x = 0.0f;
    float y = 0.0f;
};

struct Vec4 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;
};

struct Mat4 {
    float m[16] = {};
};

inline Vec2 operator+(Vec2 a, Vec2 b) noexcept {
    return {a.x + b.x, a.y + b.y};
}

inline Vec2 operator*(Vec2 v, float s) noexcept {
    return {v.x * s, v.y * s};
}

inline float dot(Vec2 a, Vec2 b) noexcept {
    return a.x * b.x + a.y * b.y;
}

inline uint32_t pack_rgba8(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept {
    return (static_cast<uint32_t>(r) << 24) |
           (static_cast<uint32_t>(g) << 16) |
           (static_cast<uint32_t>(b) << 8) |
           static_cast<uint32_t>(a);
}

}
}

#endif
