// mc_audio.cpp
//////////////////////////////////////////////////////////////////////

#include "SDL.h"
#include <string>
#include "math.h"
#include "stb_vorbis.hpp"
#include "mc_audio.hpp"
#include "mc_util.hpp"
#include "mc_game.hpp"


void audioCallback_c( void *audioObject, Uint8 *stream, int len ); 
static int fileLoaderThread_c( void *audioObject );



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
    if( musicAudioBuffer != NULL )
    {
        free( musicAudioBuffer );
        musicAudioBuffer = NULL;
    }
    if( binauralAudioBuffer != NULL )
    {
        free( binauralAudioBuffer );
        binauralAudioBuffer = NULL;
    }
}




//////////////////////////////////////////////////////////////////////////////////////////
void MCAudio::start()
{
    // ALLOCATE SPACE FOR DESIRED AND OBTAINED AUDIO SPECS
    SDL_AudioSpec* desired = (SDL_AudioSpec *) malloc(sizeof(SDL_AudioSpec));
    SDL_AudioSpec* obtained = (SDL_AudioSpec *) malloc(sizeof(SDL_AudioSpec));
    
    // SET UP PARAMETERS FOR AUDIO DEVICE AND CALLBACK 
    desired->freq = 22050;
    desired->format = AUDIO_S16SYS;
    desired->samples = 4096/2;
    desired->callback = audioCallback_c;
    desired->userdata = this;
    desired->channels = 2;
    
    // OPEN THE AUDIO DEVICE...
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




//////////////////////////////////////////////////////////////////////////
short* MCAudio::loadAudioFile( std::string filename, int* fileLength )
{
    int channels = 0;
    int sampleRate = 0;
    int length = 0;
    short* decodeOutput = NULL;
    std::string audioFilenameWithPath = stdprintf( "%smedia/audio/%s", SDL_GetBasePath(), filename.c_str() );
    printf( "** OGG FILENAME: %s \n", audioFilenameWithPath.c_str() );
    
    // DECODE AUDIO FILE TO BUFFER
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






//==============================================================================================
static int fileLoaderThread_c( void *audioObject )
{
    // CALL CORRESPONDING THREAD METHOD IN CLASS...
    ((MCAudio*) audioObject)->fileLoaderThread();
    
    return 0; // <-- RETURN VALUE IS UNUSED ('SDL_CreatThread' REQUIRES FUNCTION THAT RETURNS AN INT)
}



///////////////////////////////////////////////////////////////////////
// BACKGROUND THREAD TO LOAD AUDIO FILES AS NEEDED, RUNS UNTIL AUDIO OBJECT IS DESTROYED
void MCAudio::fileLoaderThread()
{
    const std::string MUSIC_FILENAME_LIST[] = { "music1.ogg", "music2.ogg", "music3.ogg", "music4.ogg", "music5.ogg", "music6.ogg", "music7.ogg" };
    const std::string BINAURAL_FILENAME = "binaural1.ogg";
    
    // BINAURAL FILE IS ALWAYS LOADED
    if( binauralFileLoaded == false )
    {
        binauralAudioBuffer = loadAudioFile( BINAURAL_FILENAME, &binauralAudioBufferLength );
        binauralFileLoaded = true;
        printf( "BINAURAL FILE LOADED. \n" );
    }

    printf( "STARTING THREAD_____________________ \n" );
    while( keepFileThreadRunning == true )
    {
        // LOAD THE MUSIC FILE CORRESPONDING TO THE CURRENTLY SELECTED PRESET (LOADS IN BACKGROUND WHILE MENU IS RUNNING)
        fileThreadMutex.lock();
        if( internalAudioPreset != loadedMusicPreset )
        {
            musicFileLoaded = false;
            fileThreadMutex.unlock();

            short* newMusicBuffer = NULL;
            int newMusicBufferLength = 0;
            printf( "MUSIC FILE LOADING %d.... \n", internalAudioPreset );
            newMusicBuffer = loadAudioFile( MUSIC_FILENAME_LIST[ internalAudioPreset ], &newMusicBufferLength );
            printf( "MUSIC FILE LOADED %d \n", internalAudioPreset );

            fileThreadMutex.lock();
            if( musicAudioBuffer != NULL )
                free( musicAudioBuffer );
            musicAudioBuffer = newMusicBuffer;
            musicAudioBufferLength = newMusicBufferLength;
            loadedMusicPreset = internalAudioPreset;
            musicFileLoaded = true;
            fileThreadMutex.unlock();
        }
        else
            fileThreadMutex.unlock();

        SDL_Delay( 10 );
    }
    printf( "QUITING THREAD_____________________ \n " );
}


/////////////////////////////////////////////////////////////////////////////////
void MCAudio::updateFrame()
{
    // THIS IS TO LOCALIZE THREAD MUTEX TO THIS CLASS
    internalAudioPreset = game->audioPreset;
}



//=======================================================================================
// C AUDIO CALLBACK
void audioCallback_c( void *audioObject, Uint8 *stream, int len ) 
{
    ((MCAudio*)audioObject)->audioCallback( stream, len );
}



/////////////////////////////////////////////////////////////////////////////////////////
// C++ AUDIO CALLBACK
void MCAudio::audioCallback( Uint8* stream, int len )
{
    fileThreadMutex.lock();
    if( game->mode == AppMode::RUNNING )
    {
        // PLAY MUSIC AUDIO WHILE RUNNING
        if( musicFileLoaded == true )
        {
            if( (playbackOffset + len) > (musicAudioBufferLength*2) ) 
                playbackOffset = 0;
            memcpy( stream, &musicAudioBuffer[ playbackOffset ], len );
            playbackOffset += len/2;
        } //*/
    }
    else
    {
        // PLAY BINAURAL AUDIO IN MENU
        if( binauralFileLoaded == true )
        {
            if( (playbackOffset + len) > (binauralAudioBufferLength*2) ) 
                playbackOffset = 0;
            memcpy( stream, &binauralAudioBuffer[ playbackOffset ], len );
            playbackOffset += len/2;
        } //*/
        else
        {
            // FILES NOT LOADED YET, SO COPY SILENCE
            memset( stream, 0, len );
        }
    }
    fileThreadMutex.unlock();

    //printf( "** PLAYBACK POS: %ld  CHUNK SIZE: %d \n", playbackOffset, len ); // <-- DEBUG!!
}



