#ifndef _TEXT_
#define _TEXT_
#include <SDL_image.h>
#include <SDL_ttf.h>
typedef struct Text_Object
{
	char *text;
	int x;
	int y;
	SDL_Color textColor;
	SDL_Texture * texture;
	int used;
}GameText;

extern TTF_Font *cour;
/*font stuff*/
void Init_Text();
GameText* AddText(char *text,int x, int y,SDL_Color textColor,int length);
void DrawAllText();


#endif