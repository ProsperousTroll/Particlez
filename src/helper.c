#include "../inc/helper.h"
#include "../inc/assets/icon.h"
#include "../inc/raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

float getRandom(float min, float max){
	static int seeded = 0;
	if(!seeded){
		srand((unsigned int)time(NULL));
		seeded = 1;
	}
	int x = (int)(min*100);
	int y = (int)(max*100);
	int res = x + rand() % (y+100 - x);
	return (float)res / 100;
}

Color randomColor(){
	int res = (int)getRandom(0.f, 5.f);
	switch(res){
		case 5: return PURPLE; break;
		case 4: return BLUE; break;
		case 3: return GREEN; break;
		case 2: return YELLOW; break;
		case 1: return ORANGE; break;
		default: return RED; break;
	}
}

void loadIcon(){
	Image icon = LoadImageFromMemory(".png", icon_png, icon_png_len);
	SetWindowIcon(icon);
	UnloadImage(icon);
}

void switchTool(Options *op, ToolType tool){
	op->toolType = tool;
}

void loadTexture(Texture2D* texture, const char* fileType, const unsigned char* fileData, int dataSize){
	Image img = LoadImageFromMemory(fileType, fileData, dataSize);
	*texture = LoadTextureFromImage(img);
	UnloadImage(img);
}
