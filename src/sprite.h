#ifndef _SPRITE_
#define _SPRITE_
#include <SDL_image.h>
#include "graphics.h"

#define MaxAnimations 10
#define maxAnimFrames 10
typedef struct Anim_T
{
	int row;
	char AnimName[20];
	int frames[maxAnimFrames];
	int delays[maxAnimFrames];
	int scales[maxAnimFrames];
	int used;
	int length;
}Anim;

typedef struct Sprite_T
{
  SDL_Texture * texture;		/*pointer to the texture in memory*/
  char filename[40];			/*the name of the file, keep them short*/
  int w, h;						/*the width and height of the frames of the sprites, not the file itself*/
  int framesperline;			/*default is 16*/
  int color1,color2,color3;		/*if the file was palette swapped these are the colors that were changed*/
  int used;						/*used by the maintanenc functions to keep track of how many times a single sprite is being used*/
  int Animating;
  Anim AnimList[MaxAnimations];
  Anim curAnim;
  int layer;
}Sprite;
/*sprite functions*/
void InitSpriteList();
void FreeSprite(Sprite *img);
Sprite *LoadSprite(char *filename,int sizex, int sizey, int layer);
void DrawSprite(Sprite *sprite,int sx,int sy, int frame, int frow,int scale);
void CloseSprites();
void AddAnimToSprite(Sprite *sprite,int frames[],int delays[],int scales[],int length, int row, char *AnimName);

#endif