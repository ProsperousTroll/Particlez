#include <raylib.h>
#include "../inc/helper.h"
#include "../inc/particles.h"

ParticleSystem pSystem = {0};
bool DEBUG = false;

int run(int w, int h, char* name, int fps);
void init();
void update(float dt);
void draw();

int main(){
	return run(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, WIN_FPS);
}

void init(){
	SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);
	//SetWindowMonitor(0);

	initSystem(&pSystem, 1);
}
void update(float dt){
	Vector2 mousePos = {0.f, 0.f};
	Vector2 winPos = {0.f, 0.f};
	mousePos = GetMousePosition();
	winPos = GetWindowPosition();
	if(IsMouseButtonDown(1)){
		SetWindowPosition(winPos.x + mousePos.x - (float)WIN_WIDTH/2, winPos.y + mousePos.y - (float)WIN_HEIGHT/2);
	}

	if(IsKeyPressed(KEY_F3) && !DEBUG){
		DEBUG = true;
	} else if(IsKeyPressed(KEY_F3)) DEBUG = false;

	updateSystem(&pSystem, dt);
}
void draw(){
	ClearBackground(BLACK);
	drawSystem(&pSystem);
	if(DEBUG) { 
		DrawFPS(10, 10); 
	}
}

int run(int w, int h, char* name, int fps){
	init();
	InitWindow(w, h, name);
	loadIcon();
	SetTargetFPS(fps);
	while(!WindowShouldClose()){
		update(GetFrameTime());
		BeginDrawing();
		draw();
		EndDrawing();
	}
	CloseWindow();
	free(pSystem.particles);
	return 0;
}
