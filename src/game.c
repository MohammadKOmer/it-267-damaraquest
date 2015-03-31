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
enum GAMESTATES   {G_GAMEPLAY,G_MENU,G_DIALOGUE};
enum PlayerInputs {PI_MovDown,PI_MovLeft,PI_MovUpLeft,PI_MovUp,PI_MovRight,PI_Select,PI_Back,PI_NULL};
enum ButtonStates {Up,Pressed,Released,Down};
Uint32 KeyButtons[PI_NULL]; /* okay thats clever*/
Uint8 inputs[PI_NULL];
Menu *Active;
Dialogue *ActiveDia;
int state,lastState,timeTillNextDialogueInput;
void GetInput();
void MainMenu();

int main( int argc, char* args[] )
{
	 state=G_MENU;
	 lastState=state;
	int timeTillNextMenuInput=0;
	 timeTillNextDialogueInput=0;
    Init_Graphics(0);
	InitSpriteList();
	InitEntityList();
	Init_Text();
	InitSound();

	KeyButtons[PI_MovDown] = SDL_SCANCODE_DOWN;
	KeyButtons[PI_MovLeft] = SDL_SCANCODE_LEFT;
	KeyButtons[PI_MovUp] = SDL_SCANCODE_UP;
	KeyButtons[PI_MovRight] = SDL_SCANCODE_RIGHT;
	KeyButtons[PI_Select] = SDL_SCANCODE_A;
	KeyButtons[PI_Back] = SDL_SCANCODE_S;
	MainMenu();
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