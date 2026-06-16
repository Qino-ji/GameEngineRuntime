module api.ger_asset;

import api.ger_types;
import std.file : readText;

struct AssetRecord {
    string path;
    string text;
    u32 refCount;
}

class AssetStore {
    private AssetRecord[string] records;

    string loadText(string path) {
        auto record = path in records;
        if (record !is null) {
            record.refCount += 1;
            return record.text;
        }
        string text = readText(path);
        records[path] = AssetRecord(path, text, 1);
        return text;
    }

    void addRef(string path) {
        auto record = path in records;
        if (record !is null) record.refCount += 1;
    }

    void release(string path) {
        auto record = path in records;
        if (record is null) return;
        if (record.refCount > 0) record.refCount -= 1;
        if (record.refCount == 0) records.remove(path);
    }

    bool contains(string path) const {
        auto record = path in records;
        return record !is null;
    }
}

unittest {
    auto store = new AssetStore();
    auto text = store.loadText("runtime/assets/scripts/main.lua");
    assert(text.length > 0);
    assert(store.contains("runtime/assets/scripts/main.lua"));
    store.release("runtime/assets/scripts/main.lua");
}
