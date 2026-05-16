#pragma once

#include <raylib.h>
#include "options.h"

typedef struct {
	Texture2D* texture;
	Rectangle bounds;
} UXelement;

// methods
void initElement(UXelement* el, Texture2D* t, int x, int y, int w, int h);
bool isHovered(UXelement* el);
bool isClicked(UXelement* el);
void drawElement(UXelement* el);

typedef struct {
	bool visible;
	int x, y;
	Options* op;
	UXelement* selected;
	UXelement grab, spawn;
} Menu;

// methods
void initMenu(Menu* menu, int x, int y, Options* op);
void updateMenu(Menu* menu, float dt);
void drawMenu(Menu* menu);
