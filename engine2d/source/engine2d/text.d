module engine2d.text;

import api.ger_types;

struct GlyphMetrics {
    u32 codepoint;
    Rect uv;
    f32 advance;
}

struct BitmapFont {
    GlyphMetrics[128] glyphs;
    u32 glyphCount;
    u32 textureHandle;
    f32 size;

    static BitmapFont create() {
        BitmapFont font;
        font.textureHandle = 0xFFFFFFFF;
        font.size = 16;
        return font;
    }

    void setGlyph(u32 codepoint, Rect uv, f32 advance) {
        if (codepoint >= 128 || glyphCount >= 128) return;
        glyphs[codepoint] = GlyphMetrics(codepoint, uv, advance);
        glyphCount += 1;
    }

    f32 measure(string text) {
        f32 width = 0;
        foreach (ch; text) {
            u32 cp = cast(u32)ch;
            if (cp < 128 && glyphs[cp].advance > 0) {
                width += glyphs[cp].advance;
            }
        }
        return width;
    }
}

unittest {
    auto font = BitmapFont.create();
    font.setGlyph(cast(u32)'A', Rect(0, 0, 1, 1), 8);
    assert(font.measure("A") == 8);
}
