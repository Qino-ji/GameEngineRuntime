module api.ger_types;

import core_sys = core;

alias i8 = core_sys.ger_i8;
alias u8 = core_sys.ger_u8;
alias i16 = core_sys.ger_i16;
alias u16 = core_sys.ger_u16;
alias i32 = core_sys.ger_i32;
alias u32 = core_sys.ger_u32;
alias i64 = core_sys.ger_i64;
alias u64 = core_sys.ger_u64;
alias f32 = core_sys.ger_f32;
alias f64 = core_sys.ger_f64;

struct Vec2 {
    f32 x;
    f32 y;
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