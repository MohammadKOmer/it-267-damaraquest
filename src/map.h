#ifndef _MAP_
#define _MAP_
#include "entity.h"
/*contains map and tile manager*/
typedef struct Tile_Object{
	Sprite *sprite;      
	SDL_Rect  Boundingbox;    /*the bounding box for collision detection*/
	Point s; 

	int shown;                /*if 1 then it will be rendered when it is on screen*/
	int frame;                /*current frame to render*/
	int fcount;               /*used for animation, the loop variable*/
	int frameR;				  /*Which row of the spritesheet is being looped over*/
	int frate;                /*how often we update our frames*/

	Point size;               /*mirrors the sprite width and height*/
	Point origin;             /*offset of the center from s*/
}Tile;
typedef struct Tilemap_Object{
	Tile* tiles;
	int numTiles;
}TileMap;

TileMap* ReadTileMapFromFile();
TileMap* CreateTileMapAroundTexture():
void FreeTileMap();

#endif