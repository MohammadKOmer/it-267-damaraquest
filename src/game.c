#include <SDL.h>
#include <stdio.h>
#include "graphics.h"
#include "entity.h"



extern SDL_Renderer * renderer;
extern SDL_Window* window;

/*Screen dimension constants*/
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;


int main( int argc, char* args[] )
{

    Init_Graphics(0);
	InitSpriteList();
	InitEntityList();
	while(1);
		{
			
			
			SDL_PumpEvents();
			ThinkEntities();
			DrawEntities();
			NextFrame(30);
		}

	ClearEntities();
	CloseSprites();
    return 0;
}