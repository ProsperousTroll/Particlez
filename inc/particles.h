#pragma once
#include <stdlib.h>
#include <raylib.h>
#include <raymath.h>

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define WIN_NAME "Particles"
#define WIN_FPS 144

// const float gravity =  981.f;

// Particle
typedef struct {
	Vector2 pos, vel;
	float radius;
	Color color;
} Particle;

// Particle methods
Particle newParticle(float x, float y, float rad, Color color);
void drawParticle(Particle* p);
void updateParticle(Particle* p, float dt);

// ParticleSystem
typedef struct {
	Particle* particles;
	size_t size, cap;
} ParticleSystem;

// ParticleSystem methods
ParticleSystem initSystem(size_t initCount);
void drawSystem(ParticleSystem* ps);
void updateSystem(ParticleSystem* ps, float dt);
void emplaceParticles(ParticleSystem* ps, size_t inc);
void collideParticles(ParticleSystem* ps);
