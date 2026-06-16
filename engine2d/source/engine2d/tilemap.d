module engine2d.tilemap;

import api.ger_types;

enum : u16 {
    TileEmpty = 0,
    TileSolid = 1,
}

struct TilemapChunk {
    i32 chunkX;
    i32 chunkY;
    u16[16 * 16] tiles;
    bool dirty;

    static TilemapChunk create(i32 x, i32 y) {
        TilemapChunk chunk;
        chunk.chunkX = x;
        chunk.chunkY = y;
        chunk.dirty = true;
        return chunk;
    }

    void setTile(u8 tx, u8 ty, u16 tile) {
        if (tx >= 16 || ty >= 16) return;
        tiles[ty * 16 + tx] = tile;
        dirty = true;
    }

    u16 getTile(u8 tx, u8 ty) const {
        if (tx >= 16 || ty >= 16) return TileEmpty;
        return tiles[ty * 16 + tx];
    }
}

struct Tilemap {
    u16 tileWidth;
    u16 tileHeight;
    u32 textureHandle;
    TilemapChunk[64] chunks;
    u32 chunkCount;

    static Tilemap create(u16 width, u16 height) {
        Tilemap map;
        map.tileWidth = width;
        map.tileHeight = height;
        map.textureHandle = 0xFFFFFFFF;
        return map;
    }

    void setTexture(u32 handle) {
        textureHandle = handle;
    }

    Rect worldBounds() const {
        return Rect(0, 0, tileWidth * 16, tileHeight * 16);
    }

    u8 isVisibleIn(Rect viewport) const {
        auto bounds = worldBounds();
        return rectOverlap(bounds, viewport) ? 1 : 0;
    }

private:
    u8 rectOverlap(Rect a, Rect b) const {
        return (a.x <= b.x + b.w && a.x + a.w >= b.x &&
                a.y <= b.y + b.h && a.y + a.h >= b.y) ? 1 : 0;
    }
}

unittest {
    auto map = Tilemap.create(2, 2);
    assert(map.worldBounds().w == 32);
    auto chunk = TilemapChunk.create(0, 0);
    chunk.setTile(1, 2, TileSolid);
    assert(chunk.getTile(1, 2) == TileSolid);
}
