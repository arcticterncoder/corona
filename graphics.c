#include "corona.h"

int window_width = 800;
int window_height = 600;

void Text(const char * message, int x, int y);
void Box(int x, int y, int w, int h, int angle, int r, int g, int b, int a);
void updateFPS();
void drawUnits();

void graphicsDraw(){
	SDL_SetRenderDrawColor(gfx.renderer, 0, 0, 0, 255);
	SDL_RenderClear(gfx.renderer);

	updateFPS();
	drawUnits();

	SDL_RenderPresent(gfx.renderer);
}

void drawUnits(){
	int i;
	for(i = 0; i < unitlimit; i++){
		if (corona.units[i].alive == 1){
			int r = 0;
			int g = 0;
			if(corona.units[i].team == 0)
				r = 255;
			if(corona.units[i].team == 1)
				g = 255;
			Box(corona.units[i].x, corona.units[i].y, corona.units[i].size, corona.units[i].size, -corona.units[i].angle, r, g, 0, 255);
		}
	}

}

void updateFPS(){
	char buf[100] = {0};
	sprintf(buf, "%i", gfx.frames);
	Text(buf, 0, 0);

}

void Text(const char * message, int x, int y){
	SDL_Color color = {255, 255, 255, 255};
	SDL_Surface * text = TTF_RenderText_Blended(gfx.font, message, color);
	if(message == NULL){
		printf("text not rendered\n");
		graphicsClose();
	}

	SDL_Texture * texture = SDL_CreateTextureFromSurface(gfx.renderer, text);
	if(texture == NULL){
		printf("text texture not created\n");
		graphicsClose();
	}
	SDL_Rect rect = {x, y, 0, 0};
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);	
	SDL_RenderCopy(gfx.renderer, texture, NULL, &rect);	
	
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(text);

}

void Box(int x, int y, int w, int h, int angle, int r, int g, int b, int a){
	SDL_Rect rect = {x, y, w, h};
	SDL_Texture * texture = SDL_CreateTexture(gfx.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
	SDL_SetRenderTarget(gfx.renderer, texture);
	SDL_SetRenderDrawColor(gfx.renderer, r, g, b, a);
	SDL_RenderClear(gfx.renderer);
	SDL_SetRenderTarget(gfx.renderer, NULL);
	SDL_RenderCopyEx(gfx.renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
	SDL_DestroyTexture(texture);

}

//Init SDL, create window, renderer, font, load font
int graphicsInit(){
	gfx.window = NULL;
	gfx.renderer = NULL;
	gfx.font = NULL;
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("SDL_Init not 0\n");
		return 1;
	}
	if(TTF_Init() != 0){
		printf("TTF_Init not 0\n");
		return 1;
	}

    	gfx.window = SDL_CreateWindow("corona", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, 0);
   	gfx.renderer = SDL_CreateRenderer(gfx.window, -1, SDL_RENDERER_ACCELERATED);

	gfx.font = TTF_OpenFont("media/font.ttf", 28);
	if(gfx.font == NULL){
		printf("Font not loaded\n");
		return 1;
	}

	return 0;
}

//clean up SDL
int graphicsClose(){
	//check if window and renderer exist, destroy them
	if(gfx.window != NULL)
		SDL_DestroyWindow(gfx.window);
	if(gfx.renderer != NULL)
		SDL_DestroyRenderer(gfx.renderer);
	if(gfx.font != NULL)
		TTF_CloseFont(gfx.font);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
