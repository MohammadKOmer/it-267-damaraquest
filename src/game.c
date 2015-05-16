#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>


#include "graphics.h"
#include "entity.h"
#include "text.h"
#include "sound.h"
#include "menu.h"
#include "Dialogue.h"

extern SDL_Renderer * renderer;
extern SDL_Window* window;
extern int state;
extern int lastState;
extern int timeTillNextDialogueInput;
/*Screen dimension constants*/
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 640;
enum GAMESTATES   {G_GAMEPLAY,G_MENU,G_DIALOGUE,G_CREATING};
enum PlayerInputs {PI_0,PI_1,PI_2,PI_3,PI_4,PI_5,PI_6,PI_7,PI_8,PI_9,
	PI_MovDown,PI_MovLeft,PI_MovUpLeft,PI_MovUp,PI_MovRight,PI_Select,PI_Back,PI_NULL};
enum ButtonStates {Up,Pressed,Released,Down};
Uint32 KeyButtons[PI_NULL]; /* okay thats clever*/
Uint8 inputs[PI_NULL];
Menu *Active;
Dialogue *ActiveDia;
int state,lastState,timeTillNextDialogueInput;
void GetInput();
void MainMenu();

int main( int argc, char* argv[] )
{
	int i,x,y;
	TileMap* EditingMap;
	char* editingFile;
	 state=G_MENU;
	 lastState=state;
	int timeTillNextMenuInput=0;
	 timeTillNextDialogueInput=0;
    Init_Graphics(0);
	InitSpriteList();
	InitEntityList();
	Init_Text();
	InitSound();
	for(i = 1;i < argc;i++)
	{
		if(strcmp("-mapedit",argv[i])== 0)
		{
			state = G_CREATING;
			editingFile=argv[i+1];
		}

	}
	EditingMap=createTilemap(0, 0, 20, 20, 128,  "Images/TestSprite.png",  editingFile);
	KeyButtons[PI_MovDown] = SDL_SCANCODE_DOWN;
	KeyButtons[PI_MovLeft] = SDL_SCANCODE_LEFT;
	KeyButtons[PI_MovUp] = SDL_SCANCODE_UP;
	KeyButtons[PI_MovRight] = SDL_SCANCODE_RIGHT;
	KeyButtons[PI_Select] = SDL_SCANCODE_A;
	KeyButtons[PI_Back] = SDL_SCANCODE_S;
	KeyButtons[PI_0]=SDL_SCANCODE_0;
	KeyButtons[PI_1]=SDL_SCANCODE_1;
	KeyButtons[PI_2]=SDL_SCANCODE_2;
	KeyButtons[PI_3]=SDL_SCANCODE_3;
	KeyButtons[PI_4]=SDL_SCANCODE_4;
	KeyButtons[PI_5]=SDL_SCANCODE_5;
	KeyButtons[PI_6]=SDL_SCANCODE_6;
	KeyButtons[PI_7]=SDL_SCANCODE_7;
	KeyButtons[PI_8]=SDL_SCANCODE_8;
	KeyButtons[PI_9]=SDL_SCANCODE_9;
	if(state!=G_CREATING)MainMenu();
	while(1)
		{
			
			NextFrame(30);
			GetInput();
			
			if(state==G_MENU){
				if(timeTillNextMenuInput<SDL_GetTicks()){
					timeTillNextMenuInput=SDL_GetTicks()+300;
					if(inputs[PI_MovDown]){
						MoveToNextOption(Active);
					}else if(inputs[PI_MovUp]){
						MoveToPreviousOption(Active);
					}
				}
				if(inputs[PI_MovDown]==0&&inputs[PI_MovUp]==0){
					timeTillNextMenuInput=0;
				}
				if(inputs[PI_Select]){
					if(Active->Options[Active->activeOption].callback){
						Active->Options[Active->activeOption].callback(Active->Options[Active->activeOption].args);
					}
				}
			}else if(state==G_DIALOGUE){
				if(timeTillNextDialogueInput<SDL_GetTicks()){
					if(inputs[PI_Select]){
						timeTillNextDialogueInput=SDL_GetTicks()+300;
						ActiveDia=NextDialogue(ActiveDia);
						if(ActiveDia==NULL){
							state=lastState;
						}
					}
				}
			}else if(state==G_CREATING){
				if(timeTillNextDialogueInput<SDL_GetTicks()){
					if(inputs[PI_MovUp]){
						
						if(y>0)y--;
					}if(inputs[PI_MovDown]){
						if(y<19)y++;
					}if(inputs[PI_MovLeft]){
						if(x>0)x--;
					}if(inputs[PI_MovRight]){
						if(x<19)x++;
					}
					timeTillNextDialogueInput=SDL_GetTicks()+300;
				}

				if(inputs[PI_0]){
					editTileInMap(EditingMap,  x, y,20, 0);
				}
				else if(inputs[PI_1]){

					editTileInMap(EditingMap,  x, y,20, 1);
				}
				else if(inputs[PI_2]){

					editTileInMap(EditingMap,  x, y,20, 2);
				}
				else if(inputs[PI_3]){

					editTileInMap(EditingMap,  x, y,20, 3);
				}
				else if(inputs[PI_4]){

					editTileInMap(EditingMap,  x, y,20, 4);
				}
				else if(inputs[PI_5]){

					editTileInMap(EditingMap,  x, y,20, 5);
				}
				else if(inputs[PI_6]){

					editTileInMap(EditingMap,  x, y,20, 6);
				}
				else if(inputs[PI_7]){

					editTileInMap(EditingMap,  x, y,20, 7);
				}
				else if(inputs[PI_8]){

					editTileInMap(EditingMap,  x, y,20, 8);
				}else if(inputs[PI_9]){

					editTileInMap(EditingMap,  x, y,20, 9);
				}

			}
			else{
				ThinkEntities();
			}
			DrawEntities();
			DrawAllText();
			SDL_RenderPresent(renderer);
		}

	ClearEntities();
	CloseSprites();
    return 0;
}

void GetInput()
{
	int i;
		SDL_PumpEvents();
	const Uint8* state = SDL_GetKeyboardState(NULL);

	for(i=0;i<PI_NULL;i++){
		inputs[i]=state[KeyButtons[i]];
	}
}

void MainMenu(){
	Active = makeMenuFromFile("yaml/menus/main.yml",500,100,50);
	printf("-----------\n");
	//createMenu(500,300,200,50,"yaml/menus/main.yml");
	SpawnImage(-400,0,2888,1426,1,"Images/background.png");
	
	SpawnImage(0,0,143,241,2,"Images/Damara_talksprite.png");
	
	 Mix_PlayMusic(LoadMusic("music/RustServantTest.wav"),-1);
}