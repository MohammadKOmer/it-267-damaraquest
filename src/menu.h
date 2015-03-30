#ifndef _MENU_
#define _MENU_
/*contains yaml parser and callback functions */

#include <glib.h>
#include "graphics.h"
#include "text.h"
#define MAXOPTIONS   16
typedef struct KeyVal{
	GString* keyScaler;
	GString* valScaler;
}KeyValue;
typedef struct Menu_Option
{
	GameText* Text;
	void (*callback) (GString* args);  
	GString* args;
}Option;

typedef struct Menu_Object{
	Option Options[MAXOPTIONS];
	int activeOption;
	int numOpts;
}Menu;
KeyVal makeKeyVal(char* ln, char delim);
/*callback functions*/
void StartGame(GString* args);
void GoToFile(GString* args);
void readFile(GString* fileName);
Menu* makeMenuFromFile(char* fileName, int x, int y, int spacing);
void MoveToNextOption(Menu* m);
void MoveToPreviousOption(Menu* m);
#endif