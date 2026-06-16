module api.ger_types;

alias i8 = byte;
alias u8 = ubyte;
alias i16 = short;
alias u16 = ushort;
alias i32 = int;
alias u32 = uint;
alias i64 = long;
alias u64 = ulong;
alias f32 = float;
alias f64 = double;

alias ger_error_t = i32;

enum i32 GER_OK = 0;
enum i32 GER_ERR_UNKNOWN = 1;
enum i32 GER_ERR_OUT_OF_MEMORY = 2;
enum i32 GER_ERR_INVALID_ARG = 3;
enum i32 GER_ERR_NOT_FOUND = 4;
enum i32 GER_ERR_IO = 5;
enum i32 GER_ERR_UNSUPPORTED = 6;
enum i32 GER_ERR_ALREADY_EXISTS = 7;
enum i32 GER_ERR_TIMEOUT = 8;

struct Vec2 {
    f32 x;
    f32 y;
}

unittest {
    auto v = Vec2(1, 2);
    assert(v.x == 1);
    assert(v.y == 2);
}

struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
}

struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
}

unittest {
    auto c = Color(1, 2, 3, 4);
    assert(c.r == 1);
    assert(c.g == 2);
    assert(c.b == 3);
    assert(c.a == 4);
}

struct Rect {
    f32 x;
    f32 y;
    f32 w;
    f32 h;
}

enum Key {
    unknown,
    space,
    enter,
    escape,
    backspace,
    tab,
    left,
    right,
    up,
    down,
    w,
    a,
    s,
    d,
}

enum MouseButton {
    left,
    right,
    middle,
}

unittest {
    assert(GER_OK == 0);
    assert(Key.space == Key.space);
    assert(MouseButton.left == MouseButton.left);
}