#ifndef _TEXT_
#define _TEXT_

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <glib.h>


extern SDL_Color Yellow;
extern SDL_Color Damara;
extern SDL_Color Kanaya;
extern SDL_Color Rose;
extern SDL_Color Latula;
extern SDL_Color White;

typedef struct Text_Object
{
	GString text;
	int x;
	int y;
	SDL_Color textColor;
	SDL_Texture * texture;
	int used;
}GameText;

extern TTF_Font *cour;
/*font stuff*/
void Init_Text();
GameText* AddText(GString text,int x, int y,SDL_Color textColor,int length);
void DrawAllText();
void RemoveText(char *removingText);

#endif