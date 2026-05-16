#include <raylib.h>
#include <raymath.h>
#include "../inc/menu.h"
#include "../inc/options.h"
#include "../inc/helper.h"
#include "../inc/particles.h"

#define WIN_NAME "Particlez"

Options options = {0};
Menu menu = {0};
ParticleSystem pSystem = {0};
Particle* held = NULL;
bool DEBUG = false;

int run(int w, int h, char* name, int fps);
void init();
void update(float dt);
void draw();
void unload();

int main(){
	return run(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, options.fps);
}

void init(){
	initOptions(&options);
	initMenu(&menu, 0, 0, &options);

	initSystem(&pSystem, 1, &options);
}
void update(float dt){
	options.winWidth = GetRenderWidth();
	options.winHeight = GetRenderHeight();
	
	options.ballSize -= (int)GetMouseWheelMove()*dt*options.ballScaleSpd;
	options.ballSize = Clamp(options.ballSize, options.ballMin, options.ballMax);

	// bypass windows freezing the window when being moved by just moving it myself
	#ifdef _WIN32

	Vector2 mousePos = {0.f, 0.f};
	Vector2 winPos = {0.f, 0.f};
	mousePos = GetMousePosition();
	winPos = GetWindowPosition();
	if(IsMouseButtonDown(1)){
		SetWindowPosition(winPos.x + mousePos.x - (float)options.winWidth/2, winPos.y + mousePos.y - (float)options.winHeight/2);
	}

	#endif

	if(IsKeyPressed(KEY_F3) && !DEBUG){
		DEBUG = true;
	} else if(IsKeyPressed(KEY_F3)) DEBUG = false;
	updateMenu(&menu, dt);

	updateSystem(&pSystem, dt, &options);
}

void draw(){
	ClearBackground(BLACK);
	drawSystem(&pSystem);
	switch(options.toolType){
		case SPAWN:
			DrawCircle((int)GetMousePosition().x-(int)options.ballSize/8, (int)GetMousePosition().y-(int)options.ballSize/8, options.ballSize, ColorAlpha(WHITE, 0.5f));
			break;
		case GRAB:
			break;
	}
	drawMenu(&menu);
	if(DEBUG) { 
		DrawFPS(10, 10); 
		DrawText(TextFormat("Balls: [%d], Ball Size: [%f]", pSystem.size, options.ballSize), 100, 10, 19, GREEN);
	}
}

void unload(){
	free(pSystem.particles);
	unloadOptions(&options);
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
	unload();
	CloseWindow();
	return 0;
}
