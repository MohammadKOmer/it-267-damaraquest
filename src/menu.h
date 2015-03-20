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
	void (*callback) (char* args);  
	GString args;
}Option;

typedef struct Menu_Object{
	Option Options[MAXOPTIONS];
	int activeOption;
	int numOpts;
}Menu;
KeyValue makeKeyVal(char* ln);
/*callback functions*/
void StartGame(char* args);
void GoToFile(char* args);
void readFile(char* fileName);
Menu* makeMenuFromFile(char* fileName, int x, int y, int spacing);
void MoveToNextOption(Menu* m);
void MoveToPreviousOption(Menu* m);
#endif