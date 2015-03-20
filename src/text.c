#include <string.h>
#include "text.h"
#include "graphics.h"

 SDL_Color Yellow={0xFF,0xFF,0,0};
 SDL_Color Damara={0xa1,0,0,0};
 SDL_Color Kanaya={0,0x81,0x41,0};
 SDL_Color Rose={0xb5,0x36,0xda,0};
 SDL_Color Latula={0,0x82,0x82,0};
 SDL_Color White={0xFF,0xFF,0xFF,0};



#define MAXTEXTS  128

TTF_Font *cour;
GameText TextList[MAXTEXTS];

extern SDL_Renderer * renderer;

void Init_Text(){
	int i;
	if(TTF_Init()==-1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}
	cour;
	cour=TTF_OpenFont("fonts/courbd.ttf", 24);
	if(!cour) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}
	
	
	for(i = 0;i < MAXTEXTS; i++)
	{
		
		TextList[i].texture=NULL;
		TextList[i].used=0;
		TextList[i].x=0;
		TextList[i].y=0;
	}

	

}
GameText* AddText(GString text,int x, int y,SDL_Color textColor,int length){
	
	int i=0;
	for(i = 0;i < MAXTEXTS; i++)
	{
		if(TextList[i].used==0){
			break;
		}
	}
	TextList[i].text=text;

	TextList[i].texture=SDL_CreateTextureFromSurface(renderer,TTF_RenderText_Blended_Wrapped(cour,(char*)g_strchomp (text.str),textColor,length));
	//fprintf(stdout,"Menu option is %s.\n.......\n",(char*)g_strchomp (text.str));
	TextList[i].used=1;
	TextList[i].x=x;
	TextList[i].y=y;
	return &TextList[i];
}

void DrawAllText(){
	int i;
	int w, h;
	SDL_Rect src,dest;
	for(i = 0;i < MAXTEXTS; i++)
	{
		if(TextList[i].used!=0){
			SDL_QueryTexture(TextList[i].texture, NULL, NULL, &w, &h);
			src.x=0;
			src.y=0;
			src.w=w;
			src.h=h;
			dest.x=TextList[i].x;
			dest.y=TextList[i].y;
			dest.w=w;
			dest.h=h;
			SDL_RenderCopy(renderer,TextList[i].texture,&src,&dest);
		}
	}
	SDL_RenderPresent(renderer);
	
}

void RemoveText(GameText* text){

	text->used=0;
	if(text->texture){
		SDL_DestroyTexture(text->texture);
		text->texture=NULL;
	}


}