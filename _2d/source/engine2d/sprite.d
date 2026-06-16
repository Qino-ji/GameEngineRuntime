module engine2d.sprite;

import api.ger_types;

struct Sprite {
    Vec2 position;
    Vec2 scale;
    Color color;
    f32 rotation;
    u8 layer;
    u8 visible;
    u32 textureHandle;
    f32 uv[4];

    static Sprite create() {
        Sprite s;
        s.position = Vec2(0, 0);
        s.scale = Vec2(1, 1);
        s.color = Color(255, 255, 255, 255);
        s.rotation = 0;
        s.layer = 0;
        s.visible = 1;
        s.textureHandle = 0xFFFFFFFF;
        s.uv = [0, 0, 1, 1];
        return s;
    }

    void setPosition(f32 x, f32 y) { position = Vec2(x, y); }
    void setScale(f32 x, f32 y) { scale = Vec2(x, y); }
    void setColor(u8 r, u8 g, u8 b, u8 a) { color = Color(r, g, b, a); }
    void setLayer(u8 l) { layer = l; }
    void setVisible(bool v) { visible = v ? 1 : 0; }
}

struct SpriteVertex {
    f32 px, py;
    f32 u, v;
    u32 color;
    u32 texIndex;
}

struct SpriteBatch {
    SpriteVertex[4096] vertices;
    u32[8192] indices;
    u32 vertexCount;
    u32 indexCount;
    u32 textureCount;

    void begin() {
        vertexCount = 0;
        indexCount = 0;
        textureCount = 0;
    }

    void push(Sprite sp) {
        if (vertexCount + 4 > 4096) return;
        if (!sp.visible) return;

        u32 idx = vertexCount;
        u32 packedColor = packColor(sp.color);
        vertices[idx] = SpriteVertex(sp.position.x - sp.scale.x * 0.5f, sp.position.y - sp.scale.y * 0.5f, sp.uv[0], sp.uv[1], packedColor, sp.textureHandle);
        vertices[idx + 1] = SpriteVertex(sp.position.x + sp.scale.x * 0.5f, sp.position.y - sp.scale.y * 0.5f, sp.uv[2], sp.uv[1], packedColor, sp.textureHandle);
        vertices[idx + 2] = SpriteVertex(sp.position.x + sp.scale.x * 0.5f, sp.position.y + sp.scale.y * 0.5f, sp.uv[2], sp.uv[3], packedColor, sp.textureHandle);
        vertices[idx + 3] = SpriteVertex(sp.position.x - sp.scale.x * 0.5f, sp.position.y + sp.scale.y * 0.5f, sp.uv[0], sp.uv[3], packedColor, sp.textureHandle);
        indices[indexCount] = idx; indices[indexCount + 1] = idx + 1; indices[indexCount + 2] = idx + 2;
        indices[indexCount + 3] = idx; indices[indexCount + 4] = idx + 2; indices[indexCount + 5] = idx + 3;
        vertexCount += 4;
        indexCount += 6;
    }
}

private u32 packColor(Color c) {
    return cast(u32)c.r | (cast(u32)c.g << 8) | (cast(u32)c.b << 16) | (cast(u32)c.a << 24);
}

unittest {
    auto sp = Sprite.create();
    sp.setPosition(10, 20);
    sp.setScale(4, 5);
    sp.setColor(1, 2, 3, 4);

    assert(sp.position.x == 10);
    assert(sp.position.y == 20);
    assert(sp.scale.x == 4);
    assert(sp.scale.y == 5);
    assert(packColor(sp.color) == 0x04030201);

    SpriteBatch batch;
    batch.begin();
    batch.push(sp);
    assert(batch.vertexCount == 4);
    assert(batch.indexCount == 6);
}