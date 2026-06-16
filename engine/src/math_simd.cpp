#include "engine/math_simd.hpp"

namespace ger {
namespace math {

Mat4 make_identity_mat4() noexcept {
    Mat4 m = {};
    m.m[0] = 1.0f;
    m.m[5] = 1.0f;
    m.m[10] = 1.0f;
    m.m[15] = 1.0f;
    return m;
}

}
}
