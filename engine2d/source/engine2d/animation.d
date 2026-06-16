module engine2d.animation;

import api.ger_types;

struct AnimationFrame {
    f32 time;
    Rect uv;
}

struct AnimationClip {
    AnimationFrame[64] frames;
    u32 frameCount;
    f32 speed;

    static AnimationClip create() {
        AnimationClip clip;
        clip.speed = 1;
        return clip;
    }

    void addFrame(f32 time, Rect uv) {
        if (frameCount >= 64) return;
        frames[frameCount] = AnimationFrame(time, uv);
        frameCount += 1;
    }

    Rect sample(f32 t) const {
        if (frameCount == 0) return Rect(0, 0, 1, 1);
        f32 local = t * speed;
        u32 idx = cast(u32)local % frameCount;
        return frames[idx].uv;
    }
}

unittest {
    auto clip = AnimationClip.create();
    clip.addFrame(1, Rect(0, 0, 1, 1));
    clip.addFrame(1, Rect(1, 0, 1, 1));
    assert(clip.sample(1.5f).x == 1);
}
