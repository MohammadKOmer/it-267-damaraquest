#ifndef _GRAPHICS_
#define _GRAPHICS_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>


extern SDL_Rect Camera;
extern SDL_Renderer * renderer;






typedef struct	Screen_T
{
    int xres,yres,depth;
}ScreenData;

/*the basics, im gonna keep it all even if i dont nessesarily need it all*/
void Init_Graphics(int windowed);



/*frame handling functions*/

void FrameDelay(Uint32 delay);
void ResetBuffer();
void NextFrame(int delay);
void EndGame(char* args);

#endif
