#include <SDL.h>
#include "map.h"


 TileMap TileMapList[MAXMAPS];
int numMaps;
void InitTileList()
{
	int i;
	numMaps = 0;
	for(i = 0;i < MAXMAPS; i++)
	{
		TileMapList[i].tiles=NULL;
		TileMapList[i].used=0;
	}
	TileMapList[0].used=0;
}
TileMap* CreateTileMapAroundBox(int x, int y, int w, int h){
	int hf,wf,i,j,e;
	TileMap newMap;
	hf=(h+15)/16+1;
	wf=(w+15)/16+1;
	for(e=0;e<MAXMAPS;e++){
		if(TileMapList[e].used==0){
			newMap=TileMapList[e];
		}
	}
	newMap.numTiles=wf*hf;
	
	newMap.tiles=(Tile*)malloc(sizeof(Tile)*newMap.numTiles);
	e=0;
	for(i=0;i<hf;i++){
		for(j=0;j<wf;j++){
			newMap.tiles[e].sprite = LoadSprite("images/dialogBox.png",16,16,8);
			if(j==0){
				newMap.tiles[e].frame=0;
			}else if(j==wf-1){
				newMap.tiles[e].frame=2;
			}else{
				newMap.tiles[e].frame=1;
			}

			if(i==0){
				newMap.tiles[e].frameR=0;
			}else if(i==hf-1){
				newMap.tiles[e].frameR=2;
			}else{
				newMap.tiles[e].frameR=1;
			}
			newMap.tiles[e].size.x=16;
			newMap.tiles[e].size.y=16;
			newMap.tiles[e].s.x=x+16*i;
			newMap.tiles[e].s.y=y+16*j;
			newMap.tiles[e].origin.x=16/2;
			newMap.tiles[e].origin.y=16/2;
			newMap.tiles[e].shown=1;
		}
	}

	return &newMap;
	
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
	TileMap newMap;

	lvl = fopen(fileName,"r"); /*checking to see if we are editing a level or
									making a new one */
	for(e=0;e<MAXMAPS;e++){
		if(TileMapList[e].used==0){
			newMap=TileMapList[e];
		}
	}
	newMap.numTiles=w*h;
	newMap.tiles=(Tile*)malloc(sizeof(Tile)*newMap.numTiles);
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
				newMap.tiles[e].frame=sq;
				newMap.tiles[e].size.x=tileSize;
				newMap.tiles[e].size.y=tileSize;
				newMap.tiles[e].s.x=x+tileSize*i;
				newMap.tiles[e].s.y=y+tileSize*j;
				newMap.tiles[e].origin.x=tileSize/2;
				newMap.tiles[e].origin.y=tileSize/2;
				newMap.tiles[e].sprite=LoadSprite(spritefile,tileSize,tileSize,1);
				newMap.tiles[e].shown=0;
				e++;
			}
			fgetc(lvl); /*to eat up newlines*/
		}
		fclose(lvl);
	}
	return &newMap;
}
void editTileInMap(TileMap* map, int x,int y,int w,int newVal){
	map->tiles[w*x+y].frame=newVal;
}
void convertMapToFile(TileMap* map,char* File,int width){
	int i,j;
	FILE* fp; 
	fp = fopen(File,"w+");
	for( i=0; i<map->numTiles;i++){
		fputc(map->tiles[i].frame+'0',fp);
		j++;
		if(j==width-1){
			fputc('\n',fp);
			j=0;
		}
	}
	fclose(fp);
}
void drawMap(TileMap* map){
	int i;
	for(i-0;i<map->numTiles;i++){
		DrawSprite(map->tiles[i].sprite,map->tiles[i].s.x - Camera.x,map->tiles[i].s.y - Camera.y ,map->tiles[i].frame,map->tiles[i].frameR,1);
	}
}