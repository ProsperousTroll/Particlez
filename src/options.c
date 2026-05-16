#include "../inc/options.h"
#include "../inc/helper.h"

#include "../inc/assets/grab.h"
#include "../inc/assets/ball.h"

#include <raylib.h>

void initOptions(Options* op){
	op->toolType = GRAB;
	op->winWidth = 1280;
	op->winHeight = 720;
	op->fps = GetMonitorRefreshRate(0);
	op->ballSize = 10.f;
	SetTargetFPS(op->fps);
	op->selecting = false;

	// constants
	op->gravity = 981.f;
	op->ballScaleSpd = 500.f;
	op->ballMin = 5.f;
	op->ballMax = 30.f;

	// Textures
	loadTexture(&op->grab, ".png", grab_png, grab_png_len);
	loadTexture(&op->ball, ".png", ball_png, ball_png_len);
}

void unloadOptions(Options *op){
	UnloadTexture(op->grab);
	UnloadTexture(op->ball);
}
