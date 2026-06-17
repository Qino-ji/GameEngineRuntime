module api.ger_audio;

import api.ger_types;

struct AudioSource {
    f32 volume;
    bool looping;

    static AudioSource create() {
        AudioSource source;
        source.volume = 1;
        source.looping = false;
        return source;
    }

    void setVolume(f32 v) {
        volume = v < 0 ? 0 : (v > 1 ? 1 : v);
    }

    void play() {}
    void stop() {}
}

unittest {
    auto source = AudioSource.create();
    source.setVolume(2);
    assert(source.volume == 1);
}
