// mc_audio.cpp
//////////////////////////////////////////////////////////////////////

#include "SDL.h"
#include <string>
#include "math.h"
#include "stb_vorbis.hpp"
#include "mc_audio.hpp"
#include "mc_util.hpp"


///////////////////////////////////////////////////////////////
MCAudio::MCAudio( MCGame* newGame )
{
    game = newGame;
}


///////////////////////////////////////////////////////////////
MCAudio::~MCAudio()
{
}



//=======================================================================================
// C AUDIO CALLBACK
void callback_c( void *audioObject, Uint8 *stream, int len ) 
{
    ((MCAudio*)audioObject)->callback( stream, len );
}



/////////////////////////////////////////////////////////////////////////////////////////
// C++ AUDIO CALLBACK
void MCAudio::callback( Uint8* stream, int len )
{
    if( (playbackOffset + len) > (audioFileLength*2) ) 
        playbackOffset = 0;
    memcpy( stream, &audioDecodeBuffer[ playbackOffset ], len );
    playbackOffset += len/2;
    
    //printf( "** PLAYBACK POS: %ld  CHUNK SIZE: %d \n", playbackOffset, len ); // <-- DEBUG!!
}



//////////////////////////////////////////////////////////////////////////////////////////
void MCAudio::start()
{
    int channels = 0;
    int sampleRate = 0;
    std::string audioFilenameWithPath = stdprintf( "%smedia/audio/%s", SDL_GetBasePath(), "music2.ogg" );
    printf( "** OGG FILENAME: %s \n", audioFilenameWithPath.c_str() );
    audioFileLength = stb_vorbis_decode_filename( audioFilenameWithPath.c_str(), &channels, &sampleRate, &audioDecodeBuffer );
    if( audioFileLength > 0 )
    {
        printf( "** OGG FILE DECODED!!  CHAN: %d  RATE: %d   LEN: %ld \n", channels, sampleRate, audioFileLength );
    }
    else
    {
        printf( "** ERROR DECODING OGG: %ld  \n", audioFileLength );
    }
    
    // -=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    
    /* setup audio */
    SDL_AudioSpec *desired, *obtained;
    
    /* Allocate a desired SDL_AudioSpec */
    desired = (SDL_AudioSpec *) malloc(sizeof(SDL_AudioSpec));
    
    /* Allocate space for the obtained SDL_AudioSpec */
    obtained = (SDL_AudioSpec *) malloc(sizeof(SDL_AudioSpec));
    
    /* choose a samplerate and audio-format */
    desired->freq = 22050;
    desired->format = AUDIO_S16SYS;
    
    //desired->samples = 4096;
    desired->samples = 4096*4;
    
    /* Our callback function */
    desired->callback = callback_c;
    desired->userdata = this;
    
    desired->channels = 2;
    
    /* Open the audio device and start playing sound! */
    if ( SDL_OpenAudio(desired, obtained) < 0 ) {
        fprintf(stderr, "AudioMixer, Unable to open audio: %s\n", SDL_GetError());
        exit(1);
    }
    
    // MAKE SURE WE GOT THE 22K SAMPLE FREQUENCY...
    if( obtained->freq != desired->freq )
    {
        printf( "ERROR: COULD NOT OBTAIN SAMPLE FREQ OF %d \n", desired->freq );
        exit( 1 );
    }

    // I ASSUME THIS *UN*PAUSES THE AUDIO??
    SDL_PauseAudio(0);
}
