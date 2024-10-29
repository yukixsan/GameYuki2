#include "ParticleSystem.h"
#include "raylib.h"

ParticleSystem::ParticleSystem(Vector2 pos, int maxParticles, float emitRate)
    : position(pos), maxParticles(maxParticles), emitRate(emitRate), timeSinceLastEmit(0.0f) {}

void ParticleSystem::Emit() {
    if (particles.size() < maxParticles) {
        Vector2 velocity = { (float)(GetRandomValue(-50, 50)), (float)(GetRandomValue(-50, 50)) };
        Color color = { (unsigned char)GetRandomValue(150, 255), 50, 50, 255 };
        float size = (float)GetRandomValue(3, 6);
        float lifeTime = 0.5f + (float)GetRandomValue(0, 100) / 100.0f;

        particles.emplace_back(position, velocity, color, size, lifeTime);
    }
}

void ParticleSystem::Update(float deltaTime) {
    timeSinceLastEmit += deltaTime;

    while (timeSinceLastEmit > 1.0f / emitRate) {
        Emit();
        timeSinceLastEmit -= 1.0f / emitRate;
    }

    for (auto it = particles.begin(); it != particles.end(); ) {
        it->Update(deltaTime);
        if (!it->IsAlive()) {
            it = particles.erase(it); // Remove dead particles
        } else {
            ++it;
        }
    }
}

void ParticleSystem::Draw() {
    for (const Particle& particle : particles) {
        particle.Draw();
    }
}

bool ParticleSystem::IsActive() const {
    return !particles.empty();
}
