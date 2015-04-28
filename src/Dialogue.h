#ifndef _DIALOGUE_
#define _DIALOGUE_
/*contains yaml parser and callback functions */

#include <glib.h>
#include "graphics.h"
#include "text.h"
#include "menu.h"
#include "entity.h"
#include "map.h"


typedef struct Dialogue_T{
	Entity* sprite;
	TileMap* map;
	GString Text;
	GameText* GText;
	GString fileName;
	SDL_Color color;
	Dialogue_T* next;
}Dialogue;


Dialogue* makeDialogueFromFile(char* fileName);
Dialogue* DisplayDialogue(Dialogue* d);
Dialogue* NextDialogue(Dialogue* d);
void freeDialogue(Dialogue* d);

#endif