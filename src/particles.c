#include <raylib.h>
#include <raymath.h>
#include <time.h>
#include <stdio.h>

#include "../inc/particles.h"
#include "../inc/helper.h"

// Particle
Particle newParticle(float x, float y, float rad, Color color){
	Particle p;
	p.radius = rad;
	p.color = color;

	// make sure particles spawn outside the win/width
	if(x+rad > WIN_WIDTH){
		p.pos.x = WIN_WIDTH-rad;
	} else if (x-rad < 0){
		p.pos.x = rad;
	} else {
		p.pos.x = x;
	}

	if(y+rad > WIN_HEIGHT){
		p.pos.y = WIN_HEIGHT-rad;
	} else if (y-rad < 0){
		p.pos.y = rad;
	} else {
		p.pos.y = y;
	}

	return p;
}

// methods

void drawParticle(Particle *p){
	DrawCircle(p->pos.x, p->pos.y, p->radius, p->color);
}

void updateParticle(Particle *p, float dt){
	p->vel.y += 981.f*dt;

	if(p->vel.y <= 3.0f && p->vel.y >= -3.f){
		p->vel.y = 0.f;
	} else { p->pos.y += p->vel.y*dt; }
		
	if(p->vel.x <= 3.0f && p->vel.x >= -3.f){
		p->vel.x = 0.f;	
	} else {p->pos.x += p->vel.x*dt;}

	if(p->pos.x+p->radius > WIN_WIDTH){
		p->pos.x = WIN_WIDTH - p->radius;
		p->vel.x *= -0.78f;
	} else if (p->pos.x - p->radius < 0){
		p->pos.x = p->radius;
		p->vel.x *= -0.78f;
	}

	if(p->pos.y+p->radius > WIN_HEIGHT){
		//p->pos.y-=p->vel.y*dt;
		p->pos.y = WIN_HEIGHT - p->radius;
		p->vel.y *= -0.78f;
	} else if (p->pos.y - p->radius < 0){
		p->pos.y = p->radius;
		p->vel.y *= -0.78f;
	}
}

// ParticleSystem
ParticleSystem initSystem(size_t initCount){
	ParticleSystem ps;
	ps.cap = initCount*2;
	ps.size = initCount;
	ps.particles = (Particle*) malloc(initCount*sizeof(Particle));

	for(size_t i = 0; i < initCount; ++i){
		ps.particles[i] = newParticle(getRandom(0.f, WIN_WIDTH), getRandom(0.f, WIN_HEIGHT), getRandom(5.f, 15.f), WHITE);
		ps.particles[i].vel.x = getRandom(-1000.0f, 1000.0f);
		ps.particles[i].vel.y = getRandom(-1000.0f, 1000.0f);
	}
	return ps;
}

// methods
void emplaceParticles(ParticleSystem *ps, size_t inc){
	if(ps->size+inc >= ps->cap){
		ps->cap*=2;
		ps->particles = realloc(ps->particles, ps->size+inc+sizeof(Particle));
	}
	for(size_t i = ps->size; i < ps->size+inc; ++i){
		ps->particles[++ps->size] = newParticle(getRandom(0.f, WIN_WIDTH), getRandom(0.f, WIN_HEIGHT), getRandom(5.f, 15.f), WHITE);
	}
}

void drawSystem(ParticleSystem* ps){
	for(int i = 0; i < ps->size; ++i){
		drawParticle(&ps->particles[i]);
	}
}


void collideParticles(ParticleSystem* ps){
	for(int i=0; i < ps->size; i++){
		for(int j=i+1; j < ps->size; j++){
			Particle* a = &ps->particles[i];
			Particle* b = &ps->particles[j];
			if(CheckCollisionCircles(a->pos, a->radius, b->pos, b->radius)){
				float dx = a->pos.x - b->pos.x;
				float dy = a->pos.y - b->pos.y;
				float distSq = dx*dx + dy*dy;
				float rad = a->radius + b->radius;

				if(distSq > rad*rad) continue;

				float dist = sqrtf(distSq);
				if(dist == 0.f){
					dx = 1.f;
					dy = 0.f;
					dist = 1.f;
				}

				float nx = dx / dist;
				float ny = dy / dist;

				float rvx = a->vel.x - b->vel.x;
				float rvy = a->vel.y - b->vel.y;
				
				float speed = rvx * nx + rvy * ny;
				if(speed > 0.f) continue;

				float e = 0.78f;
				float k = -(1.f + e) * speed / 2.f;

				a->vel.x += k * nx;
				a->vel.y += k * ny;
				b->vel.x -= k * nx;
				b->vel.y -= k * ny;
				
				float overlap = rad - dist;
				float push = overlap * 0.5f;
				a->pos.x += nx * push;
				a->pos.y += ny * push;
				b->pos.x -= nx * push;
				b->pos.y -= ny * push;
			}
		}
	}
}

void updateSystem(ParticleSystem *ps, float dt){
	Vector2 winPos = GetWindowPosition();
	static Vector2 lastPosition;
	Vector2 winDelta = Vector2Subtract(winPos, lastPosition);
	collideParticles(ps);
	for(int i = 0; i < ps->size; ++i){
		updateParticle(&ps->particles[i], dt);

		if(winDelta.x) ps->particles[i].vel.x += winDelta.x*2;
		if(winDelta.y) ps->particles[i].vel.y += winDelta.y*2;
	}
	lastPosition = winPos;
}
