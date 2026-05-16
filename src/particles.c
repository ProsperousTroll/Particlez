#include <raylib.h>
#include <raymath.h>
#include <time.h>
#include <stdio.h>

#include "../inc/particles.h"
#include "../inc/helper.h"

// Particle
Particle newParticle(float x, float y, float rad, Color color){
	Particle p;
	p.vel = (Vector2){0.f, 0.f};
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
void initSystem(ParticleSystem* ps, size_t initCount){
	ps->emplacing = false;
	ps->cap = initCount*2;
	ps->size = initCount;
	ps->particles = (Particle*) malloc(initCount*sizeof(Particle));

	for(size_t i = 0; i < initCount; i++){
		ps->particles[i] = newParticle(getRandom(0.f, WIN_WIDTH), getRandom(0.f, WIN_HEIGHT), getRandom(5.f, 15.f), randomColor());
		ps->particles[i].vel.x = getRandom(-1000.f, 1000.f);
		ps->particles[i].vel.y = getRandom(-1000.f, 1000.f);
	}
}

// methods
void emplaceParticles(ParticleSystem *ps, size_t inc){
	ps->emplacing = true;
	size_t newSize = ps->size+inc;
	float newRad = getRandom(5.f, 15.f);
	Vector2 mousePos = {0.f, 0.f};
	mousePos = GetMousePosition();
	printf("EMPLACING: PARTICLES SIZE: %zu\n", ps->size);
	for(size_t i = ps->size; i < newSize; ++i){
		if(newSize >= ps->cap){
			size_t newCap = ps->cap*2;
			Particle* new = (Particle*)realloc(ps->particles, newCap*sizeof(Particle));
			if(!new){
				printf("HORRIBLE- CANT REALLOC!\n");
				exit(1);
			}
			ps->particles = new;
			ps->cap = newCap;
		} 
		ps->particles[ps->size] = newParticle(mousePos.x, mousePos.y, newRad, randomColor());
		ps->size++;
	}
	ps->emplacing = false;
}

void removeParticle(ParticleSystem *ps, size_t index){
 	if(index >= ps->size ) return;
	ps->particles[index] = ps->particles[ps->size - 1];
	ps->size--;
}

void drawSystem(ParticleSystem* ps){
	int size = ps->size;
	if(ps->emplacing) return;
	for(int i = 0; i < size; ++i){
		if(ps->emplacing) continue;
		drawParticle(&ps->particles[i]);
	}
}


void collideParticles(ParticleSystem* ps, float dt){
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
				float k = ( -(1.f + e) * speed / 2.f );

				a->vel.x += k * nx;
				a->vel.y += k * ny;
				b->vel.x -= k * nx;
				b->vel.y -= k * ny;
				
				float overlap = rad - dist;
				float push = overlap * 0.2f;
				a->pos.x += nx * push;
				a->pos.y += ny * push;
				b->pos.x -= nx * push;
				b->pos.y -= ny * push;
			}
		}
	}
}

void updateSystem(ParticleSystem *ps, float dt){
	if(IsMouseButtonDown(0)){
		emplaceParticles(ps, 1);
	}
	if(IsMouseButtonDown(2) || IsKeyDown(KEY_BACKSPACE)){
		removeParticle(ps, ps->size-1);
	}
	int size = ps->size;
	Vector2 winPos = GetWindowPosition();
	static Vector2 lastPosition;
	Vector2 winDelta = Vector2Subtract(winPos, lastPosition);

	collideParticles(ps, dt);
	for(int i = 0; i < size; ++i){
		if(ps->emplacing) continue;
		updateParticle(&ps->particles[i], dt);

		if(winDelta.x) ps->particles[i].vel.x += winDelta.x*2;
		if(winDelta.y) ps->particles[i].vel.y += winDelta.y*2;
	}
	lastPosition = winPos;
}
