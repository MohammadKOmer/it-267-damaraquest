#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "entity.h"
#include "graphics.h"


#define   RPixel_W    256
#define   RPixel_H    256




extern SDL_Rect Camera;
extern Uint32 NOW;
extern Entity *ThePlayer;
extern SDL_Renderer * renderer;

Entity EntityList[MAXENTITIES];
int NumEnts = 0;
int EnemyPresent;

void InitEntityList()
{
	int i;
	NumEnts = 0;
	for(i = 0;i < MAXENTITIES; i++)
	{
		EntityList[i].sprite = NULL;
		EntityList[i].owner = NULL;
		EntityList[i].think = NULL;
		EntityList[i].target = NULL;
		EntityList[i].update = NULL;
		EntityList[i].shown = 0;
		EntityList[i].used = 0;
	}

	NewEntity();
}


void DrawEntities()
{
	int i;
	for(i = 0;i < MAXENTITIES;i++)
	{
		if(EntityList[i].used == 1)
		{
			if(((EntityList[i].s.x + EntityList[i].size.x) >= Camera.x - 200)&&(EntityList[i].s.x <= (Camera.x + Camera.w + 200))&&((EntityList[i].s.y + EntityList[i].size.y) >= Camera.y - 200)&&(EntityList[i].s.y <= (Camera.y + Camera.h) + 200))
			{
				DrawEntity(&EntityList[i]);
			}
		}
	}
	SDL_RenderPresent(renderer);
}


void ThinkEntities()
{
	int i;
	int checked = 0;
	EnemyPresent=0;
	for(i = 0;i < MAXENTITIES;i++)
	{
		if(EntityList[i].used)
		{
			checked++;
			if(EntityList[i].NextThink < NOW)
			{
				if(EntityList[i].think != NULL)
				{
					EntityList[i].think(&EntityList[i]);
					EntityList[i].NextThink = NOW + EntityList[i].ThinkRate;
				}
					
			}
			if(EntityList[i].Unit_Type==EC_AI){
				EnemyPresent++;
			
			}
		}
	}
}
void UpdateEntities()
{
  int i;
  int checked = 0;
  for(i = 0;i < MAXENTITIES;i++)
  {
      if(EntityList[i].used)
      {
		     checked++;
        if(EntityList[i].NextUpdate < NOW)
        {
          if(EntityList[i].update != NULL)
          {
            EntityList[i].update(&EntityList[i]);
            EntityList[i].NextUpdate = NOW + EntityList[i].UpdateRate;
          }

        }
		
      }
  }
  
} 
void DrawEntity(Entity *ent)
{

    if(ent->sprite != NULL){

		DrawSprite(ent->sprite,ent->s.x - Camera.x,ent->s.y - Camera.y ,ent->frame,ent->frameR,ent->drawScale);
	  if(ent->sprite->Animating!=0){
		  ent->timeSinceLastAnim++;
		  if(ent->sprite->curAnim.delays[ent->curAnimIndex] < ent->timeSinceLastAnim){
			  ent->curAnimIndex++;
			 
			  if(ent->curAnimIndex== ent->sprite->curAnim.length){
				
				  ent->curAnimIndex=0;
			  }
			  ent->frame=ent->sprite->curAnim.frames[ent->curAnimIndex];
			   ent->drawScale=ent->sprite->curAnim.scales[ent->curAnimIndex];
			  ent->timeSinceLastAnim=0;
		  }
	  }
	
	}
  
}
Entity *NewEntity()
{
	int i;
	if(NumEnts + 1 >= MAXENTITIES)
	{
		return NULL;
	}
	NumEnts++;
	for(i = 0;i < MAXENTITIES;i++)
	{
		if(!EntityList[i].used)break;
	}
	EntityList[i].used = 1;
	return &EntityList[i];
}


void FreeEntity(Entity *ent)
{
	ent->used = 0;
	NumEnts--;
	if(ent->sprite != NULL)FreeSprite(ent->sprite);
	ent->sprite = NULL;
	ent->owner = NULL;
	ent->think = NULL;
	ent->target = NULL;
	ent->update = NULL;
	
}


void ClearEntities()
{
	int i;
	for(i = 0;i < MAXENTITIES;i++)
	{
		FreeEntity(&EntityList[i]);
	}
}



void DamageTarget(Entity *attacker,Entity *inflictor,Entity *defender,int damage,int dtype,float kick,float kickx,float kicky)
{     
}

int GetFace(Entity *self)
{
	return 1;
}


void UpdateEntityPosition(Entity *self)
{
	
}



int OnScreen(Entity *self)
{
  if(((self->s.x + self->size.x) >= Camera.x)&&(self->s.x <= (Camera.x + Camera.w))&&((self->s.y + self->size.y) >= Camera.y)&&(self->s.y <= (Camera.y + Camera.h)))
    return 1;
  return 0;
}

Entity*  SpawnSquare(int x,int y, int frame)
{
	int frames[4]={3,4,6,1};
	int delays[4]={60,120,60,120};
	int scales[4]={1,2,2,1};
	Entity *newent = NULL;
	newent = NewEntity();
	
	if(newent == NULL)
	{
		printf( "Unable to generate player entity; %s",SDL_GetError());
		exit(0);
	}
	strcpy(newent->EntName,"testsprite\0");
	newent->sprite = LoadSprite("images/TestSprite.png",256,256);
	newent->sprite->Animating=1;
	newent->size.x = 256;
	newent->size.y = 256;
	AddAnimToSprite(newent->sprite,frames,delays,scales,4,0,"testing");
	newent->fcount=9;
	
	newent->Unit_Type = ET_WorldEnt;

	newent->healthmax = 100;
	newent->health = 100;
	newent->frame = frame;


	newent->frate = 0;
	newent->state = ST_IDLE;
	newent->EntClass=EC_STATIC;


	newent->s.x = x;
	newent->s.y = y;

	newent->maxspeed = 0;
	newent->movespeed = 0;

	newent->Boundingbox.x = 0;
	newent->Boundingbox.y = 0;
	newent->Boundingbox.w = 256;
	newent->Boundingbox.h = 256;  
	newent->origin.x = 128;
	newent->origin.y = 128;

}
void SwitchAnim(Entity *ent,char *AnimName){
	int i;
	for(i=0;i<MaxAnimations;i++){
		if(ent->sprite->AnimList[i].used==0){
			printf("Could not find sprite");
		}
		if(strncmp(ent->sprite->AnimList[i].AnimName,AnimName,20)==0){
			break;
		}
	}
	ent->frame=ent->sprite->AnimList[i].frames[0];
	ent->frameR=ent->sprite->AnimList[i].row;
	ent->sprite->curAnim=ent->sprite->AnimList[i];
	
}

