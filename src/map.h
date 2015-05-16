#ifndef _MAP_
#define _MAP_
#include "entity.h"
#include <SDL_image.h>
#define MAXMAPS   16

/*contains map and tile manager*/
typedef struct Tile_Object{
	Sprite *sprite;      
	SDL_Rect  Boundingbox;    /*the bounding box for collision detection*/
	Point s; 

	int shown;                /*if 1 then it will be rendered when it is on screen*/
	int frame;                /*current frame to render*/
	int frameR;
	Point size;               /*mirrors the sprite width and height*/
	Point origin;             /*offset of the center from s*/
}Tile;
typedef struct Tilemap_Object{
	Tile* tiles;
	int numTiles;
	int used;
}TileMap;


TileMap* CreateTileMapAroundBox(int x, int y, int w, int h);
void FreeTileMap(TileMap* t);
TileMap* createTilemap(int x, int y, int w, int h, int tileSize, char* spritefile, char* fileName);
void editTileInMap(TileMap* map, int x,int y,int w,int newVal);
void drawMap(TileMap* map);
void convertMapToFile(TileMap* map,char* File,int width);
#endif