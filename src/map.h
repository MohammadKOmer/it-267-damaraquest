#ifndef _MAP_
#define _MAP_
#include "entity.h"
#include <SDL_image.h>
#define MAXMAPS   16
//static TileMapList[MAXMAPS];
/*contains map and tile manager*/
typedef struct Tile_Object{
	Sprite *sprite;      
	SDL_Rect  Boundingbox;    /*the bounding box for collision detection*/
	Point s; 

	int shown;                /*if 1 then it will be rendered when it is on screen*/
	int frame;                /*current frame to render*/

	Point size;               /*mirrors the sprite width and height*/
	Point origin;             /*offset of the center from s*/
}Tile;
typedef struct Tilemap_Object{
	Tile* tiles;
	int numTiles;
}TileMap;

TileMap* ReadTileMapFromFile(char* fileName);
TileMap* CreateTileMapAroundBox(int x, int y, int w, int h);
void FreeTileMap(TileMap* t);
void createTilemap(int w, int h, char* fileName);
#endif