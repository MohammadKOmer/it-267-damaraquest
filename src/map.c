#include <SDL.h>
#include "map.h"


static TileMap* TileMapList[MAXMAPS];

TileMap* CreateTileMapAroundBox(int x, int y, int w, int h){
	int hf,wf,i,j,e;
	TileMap* newMap=(TileMap*) malloc(sizeof(TileMap));
	hf=(h+15)/16+1;
	wf=(w+15)/16+1;
	newMap->numTiles=wf*hf;
	
	newMap->tiles=(Tile*)malloc(sizeof(Tile)*newMap->numTiles);
	e=0;
	for(i=0;i<hf;i++){
		for(j=0;j<wf;j++){
			newMap->tiles[e].sprite = LoadSprite("images/dialogBox.png",16,16,8);
			if(j==0){
				newMap->tiles[e].frame=0;
			}else if(j==wf-1){
				newMap->tiles[e].frame=2;
			}else{
				newMap->tiles[e].frame=1;
			}

			if(i==0){
				newMap->tiles[e].frameR=0;
			}else if(i==hf-1){
				newMap->tiles[e].frameR=2;
			}else{
				newMap->tiles[e].frameR=1;
			}
			newMap->tiles[e].size.x=16;
			newMap->tiles[e].size.y=16;
			newMap->tiles[e].s.x=x+16*i;
			newMap->tiles[e].s.y=y+16*j;
			newMap->tiles[e].origin.x=16/2;
			newMap->tiles[e].origin.y=16/2;
			newMap->tiles[e].shown=1;
		}
	}

	return newMap;
	
}
void FreeTile(Tile *t){
	FreeSprite(t->sprite);
	free(t);	
}
void FreeTileMap(TileMap* t){
	int i;
	for(i=0;i<t->numTiles;i++){
		FreeTile(&(t->tiles[i]));

	}
	free(t);
	t=NULL;
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