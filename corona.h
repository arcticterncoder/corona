#ifndef _corona_
#define _corona_

#include "stdio.h"
#include "/usr/include/SDL2/SDL.h"
#include "/usr/include/SDL2/SDL_ttf.h"

#define PI 3.14159265
#define unitlimit 40
#define unitspeed 5

struct centuria{
	double x, y;
	int size, team, alive;
	double angle;
};

struct graphics{
	SDL_Window * window;
	SDL_Renderer * renderer;
	TTF_Font * font;
	int frames;
}gfx;

struct game{
	int running;
	int pause;
	struct centuria units[unitlimit];
	int nextfree;

}corona;

void cMove();
void cTranslate();
void cSetPosition();
void cPoint();
void cTurn();
void cSetAngle();

void gameInit();
void gameClear();
void gameUpdate();
void gameEvents();

int graphicsInit();
void graphicsDraw();
int graphicsClose();

int window_width;
int window_height;

#endif
