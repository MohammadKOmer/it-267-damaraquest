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
	Entity* test;

    Init_Graphics(0);
	InitSpriteList();
	InitEntityList();
	 test = SpawnSquare(0,0,4);
	 SwitchAnim(test,"testing");
	while(1)
		{
			
			/*test->frame++;
			if(test->frame>test->fcount){
				test->frame=0;
			}
			test->s.x++;
			*/
			
			SDL_PumpEvents();
			ThinkEntities();
			DrawEntities();
			NextFrame(30);

		}

	ClearEntities();
	CloseSprites();
    return 0;
}