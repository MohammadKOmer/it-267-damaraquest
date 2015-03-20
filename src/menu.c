#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "menu.h"

void StartGame(char* args){

}
void GoToFile(char* args){
	
}
void EndGame(char* args){
	exit(0);
}
KeyVal makeKeyVal(char* ln, char delim){
	KeyVal KV={g_string_new(""),g_string_new("")};
	int i=0;
	while(ln[i]!= delim){
		g_string_append_c(KV.keyScaler,ln[i]);
		i++;
	}
	
	i++;
	while(ln[i]!= NULL){
		g_string_append_c(KV.valScaler,ln[i]);
		i++;
	}
	return KV;

}
void readFile(char* fileName){
	KeyVal KV;
	FILE *f;
	char ln[100];
	f = fopen(fileName,"r");
	if(f==NULL){
		fprintf( stderr,"Failed to open file!\n");
		return ;
	}
	while(fgets(ln,100,f)){
		
		KV=makeKeyVal(ln,':');
		g_print ("Key is %s, Value is %s \n",KV.keyScaler->str,KV.valScaler->str);
	}
	return;
}
Menu* makeMenuFromFile(char* fileName, int x, int y, int spacing){
	Menu* newMenu = (Menu*)malloc(sizeof(Menu));
	KeyVal KV;
	FILE *f;
	char ln[100];
	int i=0;
	f = fopen(fileName,"r");
	if(f==NULL){
		fprintf( stderr,"Failed to open file!\n");
		return NULL;
	}
	while(fgets(ln,100,f)){
		
		KV=makeKeyVal(ln,':');
		newMenu->Options[i].Text=AddText(*KV.keyScaler,x,y+spacing*i,White,KV.keyScaler->len);
		if(strncmp (KV.valScaler->str,"C_StartGame",11)==0){
			newMenu->Options[i].callback=StartGame;
		}else if(strncmp (KV.valScaler->str,"C_QuitGame",10)==0){
			newMenu->Options[i].callback=EndGame;
		}
		i++;
	}
	newMenu->activeOption=0;
	newMenu->numOpts=i;
	return newMenu;
}
void MoveToNextOption(Menu* m){
	RemoveText(m->Options[m->activeOption].Text);
	m->Options[m->activeOption].Text=AddText(m->Options[m->activeOption].Text->text,m->Options[m->activeOption].Text->x,m->Options[m->activeOption].Text->y,White,m->Options[m->activeOption].Text->text.len);
	m->activeOption=m->activeOption+1;
	if(m->activeOption>m->numOpts-1){
		m->activeOption=0;
	}
	RemoveText(m->Options[m->activeOption].Text);
	m->Options[m->activeOption].Text=AddText(m->Options[m->activeOption].Text->text,m->Options[m->activeOption].Text->x,m->Options[m->activeOption].Text->y,Yellow,m->Options[m->activeOption].Text->text.len);
}
void MoveToPreviousOption(Menu* m){
	RemoveText(m->Options[m->activeOption].Text);
	
	m->Options[m->activeOption].Text=AddText(m->Options[m->activeOption].Text->text,m->Options[m->activeOption].Text->x,m->Options[m->activeOption].Text->y,White,m->Options[m->activeOption].Text->text.len);
	m->activeOption=m->activeOption-1;
	if(m->activeOption<0){
		m->activeOption=m->numOpts;
	}
	RemoveText(m->Options[m->activeOption].Text);
	m->Options[m->activeOption].Text=AddText(m->Options[m->activeOption].Text->text,m->Options[m->activeOption].Text->x,m->Options[m->activeOption].Text->y,Yellow,m->Options[m->activeOption].Text->text.len);
}

