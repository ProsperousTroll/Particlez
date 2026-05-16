#include <raylib.h>
#include "../inc/options.h"
#include "../inc/helper.h"
#include "../inc/particles.h"

#define WIN_NAME "Particlez"

Options options = {0};

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
	initOptions(&options);

	initSystem(&pSystem, 1, &options);
}
void update(float dt){
	Vector2 mousePos = {0.f, 0.f};
	Vector2 winPos = {0.f, 0.f};
	mousePos = GetMousePosition();
	winPos = GetWindowPosition();
	options.winWidth = GetRenderWidth();
	options.winHeight = GetRenderHeight();
	
	if(IsKeyDown(KEY_UP)) options.ballSize+=dt*5.f;
	if(IsKeyDown(KEY_DOWN)) options.ballSize-=dt*5.f;

	if(IsMouseButtonDown(1)){
		SetWindowPosition(winPos.x + mousePos.x - (float)WIN_WIDTH/2, winPos.y + mousePos.y - (float)WIN_HEIGHT/2);
	}

	if(IsKeyPressed(KEY_F3) && !DEBUG){
		DEBUG = true;
	} else if(IsKeyPressed(KEY_F3)) DEBUG = false;

	updateSystem(&pSystem, dt, &options);
}
void draw(){
	ClearBackground(BLACK);
	drawSystem(&pSystem);
	if(DEBUG) { 
		DrawFPS(10, 10); 
		DrawText(TextFormat("Balls: [%d], Ball Size: [%f]", pSystem.size, options.ballSize), 100, 10, 19, WHITE);
	}
}

int run(int w, int h, char* name, int fps){
	SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN | FLAG_WINDOW_RESIZABLE);
	InitWindow(w, h, name);
	init();
	loadIcon();
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
