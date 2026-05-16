#pragma once

typedef struct {
	int winWidth, winHeight, fps;
	float gravity;
	float ballSize;
} Options;

// methods
void initOptions(Options* op);
