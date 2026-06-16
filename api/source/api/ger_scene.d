module api.ger_scene;

import api.ger_asset;
import api.ger_ecs;
import api.ger_types;

class Scene {
    private string _name;
    private World world;
    private AssetStore assets;
    private bool active;

    this(string name) {
        _name = name;
        world = new World();
        assets = new AssetStore();
        active = false;
    }

    string name() const {
        return _name;
    }

    void enter() {
        active = true;
        onEnter();
    }

    void update(f32 dt) {
        if (!active) return;
        onUpdate(dt);
    }

    void exit() {
        if (!active) return;
        active = false;
        onExit();
    }

    Entity spawn(string typeName) {
        auto entity = world.createEntity();
        world.addComponent(entity, typeName);
        return entity;
    }

    AssetStore assetStore() {
        return assets;
    }

    World ecs() {
        return world;
    }

protected:
    void onEnter() {}
    void onUpdate(f32 dt) {}
    void onExit() {}
}

unittest {
    auto scene = new Scene("main");
    assert(scene.name == "main");
    scene.enter();
    auto entity = scene.spawn("sprite");
    assert(entity.valid);
    scene.update(0.016f);
    scene.exit();
}
