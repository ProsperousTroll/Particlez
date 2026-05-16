#include <stdio.h>
#include <raylib.h>
#include <time.h>
#include "../inc/particles.h"

ParticleSystem pSystem;

int run(int w, int h, char* name, int fps);
void init();
void update(float dt);
void draw();

int main(){
	return run(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, WIN_FPS);
}

void init(){
	pSystem = initSystem(200);
}
void update(float dt){
	updateSystem(&pSystem, dt);
}
void draw(){
	ClearBackground(BLACK);
	drawSystem(&pSystem);
	DrawFPS(10, 10);
}

int run(int w, int h, char* name, int fps){
	init();
	InitWindow(w, h, name);
	SetTargetFPS(fps);
	while(!WindowShouldClose()){
		update(GetFrameTime());
		BeginDrawing();
		draw();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
