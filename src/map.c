#include <SDL.h>
#include "map.h"


TileMap* CreateTileMapAroundBox(int x, int y, int w, int h){
	return NULL;
}
void FreeTileMap(TileMap* t){

}



TileMap* createTilemap(int x, int y, int w, int h, int tileSize, char* spritefile, char* fileName){
	FILE  *lvl;
	int creating,i,j,e,sq;
	TileMap* newMap;

	lvl = fopen(fileName,"r"); /*checking to see if we are editing a level or
									making a new one */

	newMap = (TileMap*)malloc(sizeof(TileMap));
	newMap->numTiles=w*h;
	newMap->tiles=(Tile*)malloc(sizeof(Tile)*newMap->numTiles);
	if( lvl == NULL )
	{
		printf("Creating new level\n");
		creating = 1;
	}else{
		creating = 0;
		e=0;
		for(i = 0 ; i<w;i++){
			for(j=0;j<h;j++){
				sq=fgetc(lvl) - '0';
				if(sq==0){
					continue;
				}
				newMap->tiles[e].frame=sq;
				newMap->tiles[e].size.x=tileSize;
				newMap->tiles[e].size.y=tileSize;
				newMap->tiles[e].s.x=x+tileSize*i;
				newMap->tiles[e].s.y=y+tileSize*j;
				newMap->tiles[e].origin.x=tileSize/2;
				newMap->tiles[e].origin.y=tileSize/2;
				newMap->tiles[e].sprite=LoadSprite(spritefile,tileSize,tileSize,1);
				newMap->tiles[e].shown=0;
				e++;
			}
			fgetc(lvl); /*to eat up newlines*/
		}
		fclose(lvl);
	}
	return newMap;
	
	

}