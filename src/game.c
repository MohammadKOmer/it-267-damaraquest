#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <yaml.h>

#include "graphics.h"
#include "entity.h"
#include "text.h"
#include "sound.h"
#include "menu.h"


extern SDL_Renderer * renderer;
extern SDL_Window* window;

/*Screen dimension constants*/
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;


int main( int argc, char* args[] )
{
	Entity* test;
	yaml_parser_t parser;
    Init_Graphics(0);
	InitSpriteList();
	InitEntityList();
	Init_Text();
	InitSound();
	/* test = SpawnSquare(0,0,4);
	 
	 SwitchAnim(test,"testing");*/
	displayMenu(0,0,200,"yaml/menus/main.yml");
	SpawnImage(-400,0,2888,1426,1,"Images/background.png");
	 AddText("Start",500,300,Yellow,100);
	SpawnImage(0,0,143,241,2,"Images/Damara_talksprite.png");
	 AddText("Quit",500,350,Yellow,100);
	 Mix_PlayMusic(LoadMusic("music/RustServantTest.wav"),-1);
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