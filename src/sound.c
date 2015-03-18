#include <SDL.h>
#include <stdio.h>
#include <SDL_mixer.h>

void InitSound()
{
	fprintf(stdout,"got here!\n");
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        
    }
	fprintf(stdout,"got here 2!\n");
}
Mix_Music* LoadMusic(char*soundfile){
	return Mix_LoadMUS( soundfile );
}

