#include "Particle.h"

Particle::Particle(Vector2 startPos, Vector2 startVel, Color startColor, float startSize, float maxLife)
    : position(startPos), velocity(startVel), color(startColor), size(startSize), lifeTime(maxLife), age(0.0f) {}

bool Particle::IsAlive() const {
    return age < lifeTime;
}

void Particle::Update(float deltaTime) {
    age += deltaTime;
    if (IsAlive()) {
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;
        color.a = 255 * (1.0f - age / lifeTime);  // Fade out over time
    }
}

void Particle::Draw() const {
    if (IsAlive()) {
        DrawCircleV(position, size, color);
    }
}
