#include <SDL.h>
#include "map.h"


TileMap* ReadTileMapFromFile(char* fileName){
	return NULL;
}
TileMap* CreateTileMapAroundBox(int x, int y, int w, int h){
	return NULL;
}
void FreeTileMap(TileMap* t){

}

void createTilemap(int w, int h, int tileSize, char* spritefile, char* fileName){
	FILE  *lvl;
	int creating,i,j,x;
	char* lvlArray=(char*)malloc( sizeof(char) * ( w*h ) );
	lvl = fopen(fileName,"r"); /*checking to see if we are editing a level or
									making a new one */

	if( lvl == NULL )
	{
		printf("Creating new level\n");
		creating = 1;
	}else{
		creating = 0;
		x=0;
		for(i = 0 ; i<w;i++){
			for(j=0;j<h;j++){
				lvlArray[x]=fgetc(lvl);
				x++;
			}
			fgetc(lvl); /*to eat up newlines*/
		}
		fclose(lvl);
	}

}