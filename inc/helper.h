#pragma once
#include "options.h"
#include <raylib.h>

void loadIcon();
float getRandom(float min, float max);
Color randomColor();
void switchTool(Options* op, ToolType tool);
void loadTexture(Texture2D* texture, const char* fileType, const unsigned char* fileData, int dataSize);
