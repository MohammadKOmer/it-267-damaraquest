#include <SDL.h>
#include <stdio.h>
#include <SDL_mixer.h>

void InitSound(){
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        
    }
}
Mix_Music* LoadMusic(char*soundfile){
	return Mix_LoadMUS( soundfile );
}

