#include <stdio.h>
#include <glib.h>
#include "menu.h"

void StartGame(char* args){

}
void GoToFile(char* args){
	
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
		i++;
	}
	return newMenu;
}

