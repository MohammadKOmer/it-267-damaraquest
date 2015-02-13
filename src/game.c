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
	SDL_Color color={0xFF,0xFF,0,0};
    Init_Graphics(0);
	InitSpriteList();
	InitEntityList();
	Init_Text();
	/* test = SpawnSquare(0,0,4);
	 
	 SwitchAnim(test,"testing");*/
	SpawnImage(-400,0,2888,1426,1,"Images/background.png");
	 AddText("Start",500,300,color,100);
	SpawnImage(0,0,143,241,2,"Images/Damara_talksprite.png");
	 AddText("Quit",500,350,color,100);
	while(1)
		{
			
			
			
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