#include "../inc/options.h"
#include <raylib.h>

void initOptions(Options* op){
	op->winWidth = 1280;
	op->winHeight = 720;
	op->fps = GetMonitorRefreshRate(0);
	SetTargetFPS(op->fps);
	op->gravity = 981.f;
	op->ballSize = 10.f;
}
