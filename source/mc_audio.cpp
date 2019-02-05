// mc_audio.cpp
//////////////////////////////////////////////////////////////////////

#include <string>
#include "math.h"
#include "SDL.h"
#include "stb_vorbis.hpp"
#include "mc_audio.hpp"
#include "mc_util.hpp"
#include "mc_game.hpp"


void audioCallback_c( void* audioObject, unsigned char* stream, int len ); 
static int fileLoaderThread_c( void* audioObject );



///////////////////////////////////////////////////////////////
MCAudio::MCAudio( MCGame* newGame )
{
    game = newGame;

    keepFileThreadRunning = true;
    fileThread = SDL_CreateThread( fileLoaderThread_c, "TestThread", (void*)this );
}


///////////////////////////////////////////////////////////////
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
    if( audioStarted == false )
    {
        SDL_AudioSpec desired;
        SDL_AudioSpec obtained;
        
        // SET UP PARAMETERS FOR AUDIO DEVICE AND CALLBACK 
        desired.freq = 22050;
        desired.format = AUDIO_S16SYS;
        desired.samples = 4096/2;
        desired.callback = audioCallback_c;
        desired.userdata = this;
        desired.channels = 2;
        
        // OPEN THE AUDIO DEVICE...
        if( SDL_OpenAudio(&desired, &obtained) < 0 ) 
        {
            logerr( "Unable to open SDL audio: %s\n", SDL_GetError() );
        }
        else
        {
            audioStarted = true;

            // MAKE SURE WE GOT THE 22K SAMPLE FREQUENCY...
            if( obtained.freq != desired.freq )
                logerr( "Audio: Could not obtain sample frequency of %d \n", desired.freq );
            
            // UNPAUSE AUDIO
            SDL_PauseAudio(0);
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////
void MCAudio::stop()
{
    if( audioStarted == true )
    {
        SDL_CloseAudio();
        audioStarted = false;
    }
}



//////////////////////////////////////////////////////////////////////////
// RETURNS NEW BUFFER WITH DECODED FILE
short* MCAudio::loadOggAudioFile( const std::string filename, int* fileLength )
{
    int channels = 0;
    int sampleRate = 0;
    int length = 0;
    short* decodeOutput = NULL;
    std::string audioFilenameWithPath = stdprintf( "%smedia/audio/%s", SDL_GetBasePath(), filename.c_str() );
    
    // DECODE AUDIO FILE TO BUFFER
    length = stb_vorbis_decode_filename( audioFilenameWithPath.c_str(), &channels, &sampleRate, &decodeOutput );
    if( length > 0 )
    {
        logmsg( "** OGG FILE DECODED: CHAN: %d  RATE: %d   LEN: %d \n", channels, sampleRate, length );
    }
    else
    {
        logerr( "** ERROR DECODING OGG: %d  \n", length );
    } 
    
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
        binauralAudioBuffer = loadOggAudioFile( BINAURAL_FILENAME, &binauralAudioBufferLength );
        binauralFileLoaded = true;
        logmsg( "BINAURAL FILE LOADED. \n" );
    }

    logmsg( "STARTING AUDIO LOADER THREAD_____________________ \n" );
    while( keepFileThreadRunning == true )
    {
        // IF THE PRESET NUMBER HAS CHANGED...
        fileThreadMutex.lock();
        if( internalAudioPreset != loadedMusicPreset )
        {
            int presetToLoad = internalAudioPreset; // <-- NECESSARY TO STORE THIS LOCALLY SO WE CAN UNLOCK MUTEX WHILE DECODING THE FILE
            musicFileLoaded = false;
            fileThreadMutex.unlock();

            // LOAD NEW MUSIC FILE...
            short* newMusicBuffer = NULL;
            int newMusicBufferLength = 0;
            newMusicBuffer = loadOggAudioFile( MUSIC_FILENAME_LIST[ presetToLoad ], &newMusicBufferLength );

            fileThreadMutex.lock();
            if( musicAudioBuffer != NULL )
                free( musicAudioBuffer );
            musicAudioBuffer = newMusicBuffer;
            musicAudioBufferLength = newMusicBufferLength;
            loadedMusicPreset = presetToLoad;
            playbackOffset = 0;
            musicFileLoaded = true;
            fileThreadMutex.unlock();
        }
        else
            fileThreadMutex.unlock();

        SDL_Delay( 100 );
    }
    logmsg( "QUITING AUDIO LOADER THREAD_____________________ \n " );
}


/////////////////////////////////////////////////////////////////////////////////
void MCAudio::updateFrame()
{
    // THIS IS TO LOCALIZE THREAD MUTEX TO THIS CLASS
    fileThreadMutex.lock();
    internalAudioPreset = game->audioPreset;
    fileThreadMutex.unlock();
}



//=======================================================================================
// C AUDIO CALLBACK
void audioCallback_c( void* audioObject, unsigned char* stream, int len ) 
{
    ((MCAudio*)audioObject)->audioCallback( stream, len );
}



/////////////////////////////////////////////////////////////////////////////////////////
// C++ AUDIO CALLBACK
void MCAudio::audioCallback( unsigned char* stream, const int len )
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

    // DEBUG - SHOW PLAYBACK STATUS
    //logmsg( "** PLAYBACK POS: %ld  CHUNK SIZE: %d \n", playbackOffset, len ); // <-- DEBUG!!
}



