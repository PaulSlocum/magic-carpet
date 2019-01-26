// mc_audio.cpp
//////////////////////////////////////////////////////////////////////

#include "SDL.h"
#include <string>
#include "math.h"
#include "stb_vorbis.hpp"
#include "mc_audio.hpp"
#include "mc_util.hpp"
#include "mc_game.hpp"


void callback_c( void *audioObject, Uint8 *stream, int len ); 
static int fileLoaderThread_c( void *ptr );



///////////////////////////////////////////////////////////////
// CONSTRUCTOR
MCAudio::MCAudio( MCGame* newGame )
{
    game = newGame;

    keepFileThreadRunning = true;
    fileThread = SDL_CreateThread( fileLoaderThread_c, "TestThread", (void*)this );
}


///////////////////////////////////////////////////////////////
// DESTRUCTOR
MCAudio::~MCAudio()
{
    keepFileThreadRunning = false;
    SDL_WaitThread( fileThread, NULL );
}




//////////////////////////////////////////////////////////////////////////////////////////
void MCAudio::start()
{
    
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
    desired->samples = 4096/2;
    
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
    
    // UNPAUSE AUDIO
    SDL_PauseAudio(0);
}




//==============================================================================================
static int fileLoaderThread_c( void *ptr )
{
    // CALL CORRESPONDING THREAD METHOD IN CLASS...
    MCAudio* threadObject = (MCAudio*) ptr;
    threadObject->fileLoaderThread();
    
    return 0; // <-- RETURN VALUE IS UNUSED, 'SDL_CreatThread' REQUIRES FUNCTION THAT RETURNS AN INT
}



//////////////////////////////////////////////////////////////////////////
short* MCAudio::loadAudioFile( std::string filename, int* fileLength )
{
    int channels = 0;
    int sampleRate = 0;
    int length = 0;
    short* decodeOutput = NULL;
    std::string audioFilenameWithPath = stdprintf( "%smedia/audio/%s", SDL_GetBasePath(), filename.c_str() );
    printf( "** OGG FILENAME: %s \n", audioFilenameWithPath.c_str() );
    length = stb_vorbis_decode_filename( audioFilenameWithPath.c_str(), &channels, &sampleRate, &decodeOutput );
    if( length > 0 )
    {
        printf( "** OGG FILE DECODED!!  CHAN: %d  RATE: %d   LEN: %d \n", channels, sampleRate, length );
    }
    else
    {
        printf( "** ERROR DECODING OGG: %d  \n", length );
    } //*/
    
    *fileLength = length;
    return decodeOutput;
}




///////////////////////////////////////////////////////////////////////
// BACKGROUND THREAD TO LOAD AUDIO FILES AS NEEDED
void MCAudio::fileLoaderThread()
{
    std::string musicFileList[] = { "music1.ogg", "music2.ogg", "music3.ogg", "music4.ogg", "music5.ogg", "music6.ogg", "music7.ogg" };
    
    if( binuaralFileLoaded == false )
    {
        binuaralAudioBuffer = loadAudioFile( "binaural1.ogg", &binuaralAudioBufferLength );
        binuaralFileLoaded = true;
        printf( "BINAURAL FILE LOADED. \n" );
    }

    printf( "STARTING THREAD ********************** \n" );
    while( keepFileThreadRunning == true )
    {
        if( game->selectedPreset != loadedMusicPreset )
        {
            if( musicAudioBuffer != NULL )
            {
                free( musicAudioBuffer );
                musicAudioBuffer = NULL;
            }
            
            printf( "MUSIC FILE LOADING.... \n" );
            musicFileLoaded = false;
            musicAudioBuffer = loadAudioFile( musicFileList[ game->selectedPreset ], &musicAudioBufferLength );
            loadedMusicPreset = game->selectedPreset;
            musicFileLoaded = true;
            printf( "MUSIC FILE LOADED. \n" );
        }
        SDL_Delay( 10 );
    }
    printf( "QUITING THREAD_____________________ \n " );
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
    /*if( binuaralFileLoaded == true )
    {
        if( (playbackOffset + len) > (binuaralAudioBufferLength*2) ) 
            playbackOffset = 0;
        memcpy( stream, &binuaralAudioBuffer[ playbackOffset ], len );
        playbackOffset += len/2;
    } //*/
    
    if( musicFileLoaded == true )
    {
        if( (playbackOffset + len) > (musicAudioBufferLength*2) ) 
            playbackOffset = 0;
        memcpy( stream, &musicAudioBuffer[ playbackOffset ], len );
        playbackOffset += len/2;
    } //*/

    //printf( "** PLAYBACK POS: %ld  CHUNK SIZE: %d \n", playbackOffset, len ); // <-- DEBUG!!
}



