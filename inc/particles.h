#pragma once
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

#include "../inc/options.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define WIN_FPS 144

// const float gravity =  981.f;

// Particle
typedef struct {
	Vector2 pos, vel;
	float radius;
	Color color;
} Particle;

// Particle methods
Particle newParticle(float x, float y, float rad, Color color, Options* op);
void drawParticle(Particle* p);
void updateParticle(Particle* p, float dt, Options* op);

// ParticleSystem
typedef struct {
	bool emplacing;
	Particle* particles;
	Particle* held;
	size_t size, cap;
} ParticleSystem;

// ParticleSystem methods
void initSystem(ParticleSystem* ps, size_t initCount, Options* op);
void drawSystem(ParticleSystem* ps);
void updateSystem(ParticleSystem* ps, float dt, Options* op);
void emplaceParticles(ParticleSystem* ps, size_t inc, Options* op);
void removeParticle(ParticleSystem* ps, size_t index);
void collideParticles(ParticleSystem* ps, float dt);
