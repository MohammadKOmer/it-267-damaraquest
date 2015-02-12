#include <SDL.h>
#include <stdio.h>
#include "graphics.h"
#include "entity.h"
#include "text.h"


extern SDL_Renderer * renderer;
extern SDL_Window* window;

/*Screen dimension constants*/
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;


int main( int argc, char* args[] )
{
	Entity* test;
	SDL_Color color={256,0,0};
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
			
			AddText("Hello World",200,200,color,100);
			SDL_PumpEvents();
			ThinkEntities();
			DrawEntities();
			DrawAllText();
			NextFrame(30);

		}

	ClearEntities();
	CloseSprites();
    return 0;
}