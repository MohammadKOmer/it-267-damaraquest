#include <string.h>
#include <SDL_image.h>
#include "sprite.h"
#include "graphics.h"

#define MaxSprites    511

Sprite SpriteList[MaxSprites];

int NumSprites;
void InitSpriteList()
{
  int x;
  NumSprites = 0;
  memset(SpriteList,0,sizeof(Sprite) * MaxSprites);
  for(x = 0;x < MaxSprites;x++)SpriteList[x].texture = NULL;
}

/*Create a sprite from a file, the most common use for it.*/
Sprite *LoadSprite(char *filename,int sizex, int sizey, int layer){
	SDL_Surface *image;
	SDL_Texture * texture;
	int i;
	for(i = 0; i < NumSprites; i++)
	{
		if(strncmp(filename,SpriteList[i].filename,40)==0)
		{
			SpriteList[i].used++;
			return &SpriteList[i];
		}
	}

	if(NumSprites + 1 >= MaxSprites)
	{
		printf(  "Maximum Sprites Reached.\n");
		exit(1);
	}
	/*if its not already in memory, then load it.*/
	NumSprites++;
	for(i = 0;i <= NumSprites;i++)
	{
		if(!SpriteList[i].used)break;
	}
	
	texture = IMG_LoadTexture(renderer,filename);
	SpriteList[i].texture = texture;

	/*then copy the given information to the sprite*/
	strncpy(SpriteList[i].filename,filename,20);
	/*now sprites don't have to be 16 frames per line, but most will be.*/
	SpriteList[i].framesperline = 16;
	SpriteList[i].w = sizex;
	SpriteList[i].h = sizey;
	SpriteList[i].layer=layer;
	SpriteList[i].used++;
	return &SpriteList[i];
}
/*
 * When we are done with a sprite, lets give the resources back to the system...
 * so we can get them again later.
 */
void FreeSprite(Sprite *sprite)
{
  /*first lets check to see if the sprite is still being used.*/
  sprite->used--;
  if(sprite->used == 0)
  {
  strcpy(sprite->filename,"\0");
     /*just to be anal retentive, check to see if the image is already freed*/
  if(sprite->texture != NULL){
	  SDL_DestroyTexture(sprite->texture);
  }
  sprite->texture = NULL;
  }
 /*and then lets make sure we don't leave any potential seg faults 
  lying around*/
}
void CloseSprites()
{
  int i;
   for(i = 0;i < MaxSprites;i++)
   {
      FreeSprite(&SpriteList[i]);
   }
    IMG_Quit();

}
void AddAnimToSprite(Sprite *sprite,int frames[],int delays[],int scales[],int length, int row, char *AnimName){
	int i;
	int k;
	Anim NewAnim;
	for(i=0;i<MaxAnimations;i++){
		if(sprite->AnimList[i].used==0){
			break;
		}
	}
	
	
	for(k = 0; k < length ; k++)
	{
		 NewAnim.frames[k]=frames[k];
		 NewAnim.delays[k]=delays[k];
		 NewAnim.scales[k]=scales[k];
	}
	NewAnim.length=length;
	NewAnim.row=row;
	NewAnim.used=1;

	strncpy(NewAnim.AnimName,AnimName,20);
	sprite->AnimList[i]=NewAnim;
	
}

void DrawSprite(Sprite *sprite,int sx,int sy, int frame, int frow,int scale)
{
    SDL_Rect src,dest;
    src.x = frame* sprite->w;
    src.y = frow * sprite->h;
    src.w = sprite->w;
    src.h = sprite->h;
    dest.x = sx;
    dest.y = sy;
    dest.w = sprite->w*scale;
    dest.h = sprite->h*scale;
	SDL_RenderCopy(renderer, sprite->texture, &src, &dest); 

   /* SDL_BlitSurface(sprite->image, &src, surface, &dest);*/
}