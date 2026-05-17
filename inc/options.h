#pragma once

#include "raylib.h"

typedef enum {
	GRAB,
	SPAWN,
	ERASE,
} ToolType;

typedef struct {
	Texture2D grab, ball, erase;
	ToolType toolType;
	int winWidth, winHeight, fps;
	float ballSize;
	float gravity;
	float ballScaleSpd;
	float ballMin;
	float ballMax;
	bool selecting;
} Options;

// methods
void initOptions(Options* op);
void unloadOptions(Options* op);
