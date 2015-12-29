#include "corona.h"

int framelimit = 60;

int main(){
	
	if(graphicsInit() != 0){
		graphicsClose();
	}
	gameInit();
	
	while(corona.running == 1){
	
		Uint32 begintime = SDL_GetTicks();

		gameUpdate();
		graphicsDraw();

		Uint32 frametime = SDL_GetTicks() - begintime;		
		double delay = (1000.f / framelimit) -frametime;		
		if(delay > 0)
			SDL_Delay(delay);

		//framerate is estimated from loop's excecution time
		gfx.frames = 1000.f / (SDL_GetTicks() - begintime);		
		
	}

	if(graphicsClose() != 0)
		printf("graphicsClose didn't return 0\n");
	return 0;
}
