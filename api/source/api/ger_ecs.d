module api.ger_ecs;

import api.ger_types;

struct Entity {
    u32 id;

    bool valid() const {
        return id != 0;
    }
}

struct ComponentRecord {
    string name;
    u32 entity;
}

class World {
    private Entity[] entities;
    private ComponentRecord[] components;
    private u32 nextId = 1;

    Entity createEntity() {
        Entity entity = Entity(nextId);
        entities ~= entity;
        nextId += 1;
        return entity;
    }

    void addComponent(Entity entity, string name) {
        if (!entity.valid) return;
        components ~= ComponentRecord(name, entity.id);
    }

    bool hasComponent(Entity entity, string name) const {
        foreach (record; components) {
            if (record.entity == entity.id && record.name == name) return true;
        }
        return false;
    }

    void destroy(Entity entity) {
        if (!entity.valid) return;
        Entity[] alive;
        foreach (candidate; entities) {
            if (candidate.id != entity.id) alive ~= candidate;
        }
        entities = alive;
    }

    size_t entityCount() const {
        return entities.length;
    }
}

unittest {
    auto world = new World();
    auto entity = world.createEntity();
    assert(entity.valid);
    world.addComponent(entity, "sprite");
    assert(world.hasComponent(entity, "sprite"));
    world.destroy(entity);
    assert(!world.hasComponent(entity, "sprite"));
}
