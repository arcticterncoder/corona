#include "corona.h"

void createCenturia();

void createCenturia(int x, int y, int angle, int team, int size){
	if(corona.nextfree >= 40){
		printf("can't create more units\n");
		return;
	}
	corona.units[corona.nextfree].x = x;
	corona.units[corona.nextfree].y = y;
	corona.units[corona.nextfree].angle = angle;
	corona.units[corona.nextfree].size = size;
	corona.units[corona.nextfree].team = team;
	corona.units[corona.nextfree].alive = 1;
	corona.nextfree++;

}

void gameUpdate(){
	if(corona.pause == -1){

		cPoint(&corona.units[0], &corona.units[1]);
		cMove(&corona.units[1]);
		cTurn(&corona.units[1], 1.2);


	}
	gameEvents();
}

void gameInit(){
	gameClear();

	createCenturia(300, 300, 0, 0, 80);
	createCenturia(400, 100, 210, 1, 80);
}

void gameClear(){
	corona.running = 1;
	corona.pause = -1;
	//next free slot in units[]
	corona.nextfree = 0;
	int i;
	for(i = 0; i < unitlimit; i++){
		corona.units[i].alive = 0;
	}
}

void gameEvents(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT)
			corona.running = 0;
		if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_ESCAPE)
				corona.running = 0;
		}
		if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_p)
				corona.pause *= -1;
		}
		if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_c)
				gameClear();
		}
		if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_r)
				gameInit();
		}
	}
	
}
