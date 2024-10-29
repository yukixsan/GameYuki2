 #ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Particle.h"
#include <vector>

class ParticleSystem {
public:
    std::vector<Particle> particles;
    Vector2 position;     // Center of the particle system (e.g., explosion origin)
    int maxParticles;     // Max particles to be generated
    float emitRate;       // Rate of particles emitted per second
    float timeSinceLastEmit;

    ParticleSystem(Vector2 pos, int maxParticles, float emitRate);
    void Emit();          // Emit a new particle
    void Update(float deltaTime);
    void Draw();
    bool IsActive() const;
};

#endif
