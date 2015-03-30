#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "menu.h"
#include "Dialogue.h"

extern int state;
extern int lastState;
extern int timeTillNextDialogueInput;
Dialogue* makeDialogueFromFile(char* fileName){
	Dialogue* head;
	Dialogue* node;
	Dialogue* tail;
	KeyVal KV;
	FILE *f;
	char ln[100];
	char* cmpString;
	char delim = 'l';
	int i=0;
	f = fopen(fileName,"r");
	if(f==NULL){
		fprintf( stderr,"Failed to open file!\n");
		return NULL;
	}
	timeTillNextDialogueInput=SDL_GetTicks()+300;
	node = (Dialogue*)malloc(sizeof(Dialogue));
	while(fgets(ln,1000,f)){

		
		if(i==0){
			head=node;
			i=1;
		}
		KV=makeKeyVal(ln,':');
		cmpString=g_strstrip(KV.keyScaler->str);
		if(strncmp (cmpString,"Damara",6)==0){
			node->Text=*KV.valScaler;
			node->fileName = *g_string_new("Images/Damara_talksprite.png");
			node->color=Damara;
		}else if(strncmp (cmpString,"Rose",4)==0){
			node->Text=*KV.valScaler;
			node->fileName = *g_string_new("Images/Rose_talksprite.png");
			node->color=Rose;
		}else if(strncmp (cmpString,"Kanaya",6)==0){
			node->Text=*KV.valScaler;
			node->fileName = *g_string_new("Images/Kanaya_talksprite.png");
			node->color=Kanaya;
		}else if(strncmp (cmpString,"Porrim",6)==0){
			node->Text=*KV.valScaler;
			node->fileName = *g_string_new("Images/Porrim_talksprite.png");
			node->color=Kanaya;
		}else if(strncmp (cmpString,"Latula",6)==0){
			node->Text=*KV.valScaler;
			node->fileName = *g_string_new("Images/Latula_talksprite.png");
			node->color=Latula;
		}else{
			node=NULL;
			break;
		}
		tail=node;
		node->next=(Dialogue*)malloc(sizeof(Dialogue));
		node=node->next;
	}
	
	tail->next=NULL;
	return head;
}
Dialogue* DisplayDialogue(Dialogue* d){
	int w, h,hf,wf,i,j,x,y,iter; //dialogue sections are 16x16
	d->GText=AddText(d->Text,16,250,d->color,d->Text.len);
	SDL_QueryTexture(d->GText->texture, NULL, NULL, &w, &h);
	hf=(h+15)/16+1;
	wf=(w+15)/16+1;
	x=d->GText->x-8;
	y=d->GText->y-8;
	d->sprite=SpawnImage(0,0,143,241,1,d->fileName.str);
	iter=0;
	d->dilogueBox=(Entity**)malloc(sizeof(Entity*)*wf*hf);
	state=2;
	for(i=0;i<hf;i++){
		for(j=0;j<wf;j++){
			d->dilogueBox[iter] = NewEntity();
			d->dilogueBox[iter]->sprite = LoadSprite("images/dialogBox.png",16,16,8);
			d->dilogueBox[iter]->sprite->Animating=0;
			d->dilogueBox[iter]->size.x = w;
			d->dilogueBox[iter]->size.y = h;
			d->dilogueBox[iter]->fcount=3;
			d->dilogueBox[iter]->drawScale=1;
			d->dilogueBox[iter]->s.x = x+16*j;
			d->dilogueBox[iter]->s.y = y+16*i;
			d->dilogueBox[iter]->origin.x = 8;
			d->dilogueBox[iter]->origin.y = 8;
			if(j==0){
				d->dilogueBox[iter]->frame=0;
			}else if(j==wf-1){
				d->dilogueBox[iter]->frame=2;
			}else{
				d->dilogueBox[iter]->frame=1;
			}

			if(i==0){
				d->dilogueBox[iter]->frameR=0;
			}else if(i==hf-1){
				d->dilogueBox[iter]->frameR=2;
			}else{
				d->dilogueBox[iter]->frameR=1;
			}
			iter++;
		}
	}
	d->dilogueBoxes=iter;
	return d;

}
Dialogue* NextDialogue(Dialogue* d){
	Dialogue* next = d->next;
	freeDialogue(d);
	if(next!=NULL){
		return DisplayDialogue(next);
	}
	return NULL;
}

void freeDialogue(Dialogue* d){
	int i;
	for(i=0;i<d->dilogueBoxes;i++){
		FreeEntity(d->dilogueBox[i]);
	}
	FreeEntity(d->sprite);
	RemoveText(d->GText);
	d=NULL;

}