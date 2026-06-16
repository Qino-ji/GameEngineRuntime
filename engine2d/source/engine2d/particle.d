module engine2d.particle;

import api.ger_types;

enum EmitterMode {
    loop,
    burst,
    oneShot,
}

struct Particle {
    Vec2 position;
    Vec2 velocity;
    f32 lifetime;
    f32 age;
    f32 size;
    Color color;
    u8 alive;
}

struct ParticleEmitter {
    Particle[1024] particles;
    Vec2 position;
    Vec2 direction;
    f32 speed;
    f32 spawnRate;
    f32 spawnAccumulator;
    f32 lifetime;
    f32 size;
    Color color;
    EmitterMode mode;
    u32 maxParticles;
    u32 aliveCount;

    static ParticleEmitter create() {
        ParticleEmitter emitter;
        emitter.direction = Vec2(1, 0);
        emitter.speed = 100;
        emitter.spawnRate = 10;
        emitter.lifetime = 1;
        emitter.size = 4;
        emitter.color = Color(255, 255, 255, 255);
        emitter.mode = EmitterMode.loop;
        emitter.maxParticles = 1024;
        return emitter;
    }

    void emitBurst(u32 count) {
        foreach (_; 0 .. count) {
            spawnOne();
        }
    }

    void update(f32 dt) {
        spawnAccumulator += dt * spawnRate;
        if (spawnAccumulator >= 1) {
            spawnAccumulator -= 1;
            spawnOne();
        }
        for (u32 i = 0; i < maxParticles; i += 1) {
            if (!particles[i].alive) continue;
            particles[i].age += dt;
            particles[i].position.x += particles[i].velocity.x * dt;
            particles[i].position.y += particles[i].velocity.y * dt;
            if (particles[i].age >= particles[i].lifetime) {
                particles[i].alive = 0;
                aliveCount -= aliveCount > 0 ? 1 : 0;
            }
        }
    }

private:
    void spawnOne() {
        if (aliveCount >= maxParticles) return;
        foreach (ref particle; particles) {
            if (particle.alive) continue;
            particle.position = position;
            particle.velocity = Vec2(direction.x * speed, direction.y * speed);
            particle.lifetime = lifetime;
            particle.age = 0;
            particle.size = size;
            particle.color = color;
            particle.alive = 1;
            aliveCount += 1;
            return;
        }
    }
}

unittest {
    auto emitter = ParticleEmitter.create();
    emitter.emitBurst(2);
    assert(emitter.aliveCount == 2);
    emitter.update(2);
    assert(emitter.aliveCount == 0);
}
