#ifndef _ENTITY_
#define _ENTITY_
#include "graphics.h"
#include "sprite.h"

#define MAXENTITIES   1024
#define MAXSTATES     10


/*random functions stolen shamelessly from quake2*/
#define random()  ((rand () & 0x7fff) / ((float)0x7fff))
#define crandom() (2.0 * (random() - 0.5))

enum ENTTYPES   {ET_Temp,ET_WorldBullet,ET_WorldEnt,ET_PlayerBullet,ET_Player};
enum ENTCLASS   {EC_NULL,EC_AI,EC_PLAYER,EC_BULLET,EC_STATIC};
enum DAMAGE_T   {DT_Saber,DT_Energy,DT_Crushing};
enum STATES     {ST_IDLE,ST_MOVINGH, ST_DIE, ST_DEAD,ST_ALERT,ST_ATTACK1,ST_FORCE,ST_LIFTING,ST_LIFTED};
enum FACE       {F_LEFT,F_RIGHT};
enum AttackFaces {AS_UP,AS_DOWN,AS_FACE};
enum CollisionTypes {C_Static, C_Person, C_Bullet, C_Explosive, C_Force};



typedef struct Point_T
{
	int x,y;
}Point;


typedef struct Entity_T
{
	int used;                 /*used is for keeping track of what entities are free and should NEVER be touched.*/
	Uint32 LastDrawn;         /*another one that should never be touched by anything but the maintainence functions*/


	struct Entity_T *player;  /*this might be a bad idea by i want everything aware of player entity*/


	int EntClass; 
	
	int Unit_Type;            /*ET_* for hit detection masking*/
	char EntName[40];         /*the name of the entity*/
	Sprite *sprite;           /*the sprite for the main part of the entity*/


	struct Entity_T *owner;   /*for bullets, drones and other things spawned by other entities*/
	struct Entity_T *target;  /*used so that the stormtroppers and sith know what they are aiming at*/
	void (*think) (struct Entity_T *self);    /*called by the engine every so often to handle input and make decisions*/
	void (*update) (struct Entity_T *self);   /*called by the engine every so often to update the position and check for collisions*/
	Uint32 NextThink;         /*used for how often the entity thinks*/
	Uint16 ThinkRate;        /*used for incrementing above*/
	Uint32 NextUpdate;        /*used for how often the entity is updated, updating is merely animations*/
	Uint16 UpdateRate;        /*used for incrementing above*/
	
	int shown;                /*if 1 then it will be rendered when it is on screen*/
	int frame;                /*current frame to render*/
	int fcount;               /*used for animation, the loop variable*/
	int frameR;				  /*Which row of the spritesheet is being looped over*/
	int frate;                /*how often we update our frames*/
	Uint32 framedelay;        /*ammount of delay between frames*/
	int face;                 /*the direction we are moving*/
	
	int state;                /*making each entity a finite state machine.*/
	SDL_Rect  Boundingbox;    /*the bounding box for collision detection*/

	
	Point s;                  /*screen coordinates*/

	Point m;                  /*Map coordinate*/
	Point size;               /*mirrors the sprite width and height*/
	Point origin;             /*offset of the center from s*/
	int movespeed;            /*current movement speed*/
	int maxspeed;             /*maximum movement speed*/
	int ordercount;           /*AI use counting variable*/


	int sightrange;           /*how big my sight radius is for detection of the player*/

	int damage;               /*how much damage I can inflict for things that can deal damage*/

	int dtype;                /*what type of Damage I will inflict*/
	int lifetime;			  /*Used for lightsaber only in the midterm build*/
	int timeSinceLastAnim,curAnimIndex,drawScale;
	/*               armor and health                 */

	int health,healthmax;     /*everything will need health.  Resources will use it for how much of a resource it has left*/
}Entity;


/*startup and clean up*/
void InitEntityList();
void ClearEntities();

/*creation and destruction*/
Entity *NewEntity();
void FreeEntity(Entity *ent);

/*update functions*/
void DrawEntity(Entity *ent);
void DrawEntities();
void UpdateEntities();
void ThinkEntities();
void SwitchAnim(Entity *ent,char *AnimName);


/*generic entity support functions*/
int OnScreen(Entity *self);
void DamageTarget(Entity *attacker,Entity *inflictor,Entity *defender,int damage,int dtype,float kick,float kickx,float kicky);

int GetFace(Entity *self);

void UpdateEntityPosition(Entity *self);
int DistanceBetween(Entity *self, Entity *target);/*returns the diference between two entities.*/

Entity* SpawnSquare(int x,int y, int frame);
Entity*  SpawnImage(int x,int y, int w, int h,int scale, char* file);

#endif