#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include <vector>
#include <cstdlib>

class Particle {
public:
    Vector2 position;
    Vector2 velocity;
    Color color;
    float size;
    float lifeTime;       // How long the particle will last
    float age;            // Current age of the particle

    Particle(Vector2 startPos, Vector2 startVel, Color startColor, float startSize, float maxLife);
    bool IsAlive() const; // Checks if the particle's age is within its lifespan
    void Update(float deltaTime);
    void Draw() const;
};

#endif
