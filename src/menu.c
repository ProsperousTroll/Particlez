#include "../inc/menu.h"
#include "../inc/helper.h"
#include "../inc/raylib.h"
#include "../inc/raymath.h"
#include <stdlib.h>
#include <stdio.h>

// element
void initElement(UXelement* el, Texture2D* t, int x, int y, int w, int h){
	el->bounds.x = x;
	el->bounds.y = y;
	el->bounds.width = w;
	el->bounds.height = h;
	el->texture = t;
}

bool isHovered(UXelement* el){
	return (CheckCollisionPointRec(GetMousePosition(), el->bounds));
}

bool isClicked(UXelement* el){
	return (isHovered(el) && IsMouseButtonPressed(0));
}

void drawElement(UXelement* el){
	if(isHovered(el)){
		//DrawTextureRec(*el->texture, el->bounds, (Vector2){el->bounds.x, el->bounds.y}, ColorAlpha(WHITE, 0.75));
		DrawTextureEx(*el->texture, (Vector2){el->bounds.x, el->bounds.y}, 0.0f, 2.0f, ColorAlpha(WHITE, 0.6f));
	} else DrawTextureEx(*el->texture, (Vector2){el->bounds.x, el->bounds.y}, 0.0f, 2.0f, WHITE);
}

// Menu
void initMenu(Menu* menu, int x, int y, Options *op){
	menu->op = op;
	//menu->selected = NULL;
	menu->x = x; // offsets
	menu->y = y;
	initElement(&menu->grab, &menu->op->grab, 0, 0, 128, 128);
	initElement(&menu->spawn, &menu->op->ball, 0, 0, 128, 128);
	initElement(&menu->erase, &menu->op->erase, 0, 0, 128, 128);
}

void updateMenu(Menu *menu, float dt){
	if(IsKeyPressed(KEY_SPACE)){
		if(menu->visible){
			menu->visible = false;
		} else menu->visible = true;
	}

	if(menu->visible){
		menu->y = Lerp(menu->y, 0, 20.f*dt);
	} else {
		menu->y = Lerp(menu->y, -256, 20.f*dt);
	}
	menu->spawn.bounds.x = menu->op->winWidth / 2.f - menu->spawn.bounds.width / 2.f - 156;
	menu->spawn.bounds.y = 64 + menu->y;
	menu->grab.bounds.x = menu->op->winWidth / 2.f - menu->grab.bounds.width / 2.f;
	menu->grab.bounds.y = 64 + menu->y;
	menu->erase.bounds.x = menu->op->winWidth / 2.f - menu->erase.bounds.width / 2.f + 156;
	menu->erase.bounds.y = 64 + menu->y;

	if(isHovered(&menu->grab) || isHovered(&menu->spawn) || isHovered(&menu->erase)){
		menu->op->selecting = true;
	} else menu->op->selecting = false;

	if(isClicked(&menu->grab)){
		switchTool(menu->op, GRAB);
	}

	if(isClicked(&menu->spawn)){
		switchTool(menu->op, SPAWN);
	}

	if(isClicked(&menu->erase)){
		switchTool(menu->op, ERASE);
	}
}

void drawMenu(Menu *menu){
	drawElement(&menu->grab);
	drawElement(&menu->spawn);
	drawElement(&menu->erase);
}
