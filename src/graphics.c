#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL_image.h>
#include "graphics.h"



SDL_Renderer * renderer;
SDL_Window* window;
SDL_Rect Camera; /*x & y are the coordinates for the background map, w and h are of the screen*/

Uint32 NOW;  /*this represents the current time for the game loop.  Things move according to time*/



/*some data on the video settings that can be useful for a lot of functions*/
Uint32 rmask,gmask,bmask,amask;
ScreenData  S_Data;


void Init_Graphics(int windowed)
{
	SDL_Window * window;
	SDL_Init(SDL_INIT_EVERYTHING);
	
	window  = SDL_CreateWindow("My SDL Empty Window",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
			   0);
    atexit(SDL_Quit);
	renderer = SDL_CreateRenderer(window, -1, 0);
	IMG_Init(IMG_INIT_PNG);
    SDL_ShowCursor(SDL_DISABLE);
    Camera.x = 0;
    Camera.y = 0;
    Camera.w = 800;
    Camera.h = 600;
}

void NextFrame(int delay)
{
	Uint32 Then;
 SDL_RenderClear(renderer);
  FrameDelay(delay);
  Then = NOW;
  NOW = SDL_GetTicks();
  /* printf(stdout,"Ticks passed this frame: %i\n", NOW - Then);*/
}
/*
  InitSpriteList is called when the program is first started.
  It just sets everything to zero and sets all pointers to NULL.
  It should never be called again.
*/
/*
  makes sure a minimum number of ticks is waited between frames
  this is to ensure that on faster machines the game won't move so fast that
  it will look terrible.
  This is a very handy function in game programming.
*/
void FrameDelay(Uint32 delay)
{
    static Uint32 pass = 100;
    Uint32 dif;
    dif = SDL_GetTicks() - pass;
    if(dif < delay)SDL_Delay( delay - dif);
    pass = SDL_GetTicks();
}