// mc_audio.cpp
//////////////////////////////////////////////////////////////////////

#include "SDL.h"
#include <string>
#include "math.h"
#include "stb_vorbis.hpp"
#include "mc_audio.hpp"
#include "mc_util.hpp"


///////////////////////////////////////////////////////////////
MCAudio::MCAudio( MCAppState* newState )
{
    state = newState;
}


///////////////////////////////////////////////////////////////
MCAudio::~MCAudio()
{
}



unsigned int sampleFrequency = 0;
unsigned int audioBufferSize = 0;
unsigned int outputAudioBufferSize = 0;

unsigned int freq1 = 1000;
unsigned int fase1 = 0;
unsigned int freq2 = 1010;
unsigned int fase2 = 0;



//=======================================================================================
// AUDIO CALLBACK
void example_mixaudio( void *audioObject, Uint8 *stream, int len ) 
{
    ((MCAudio*)audioObject)->callback( stream, len );
    
    
    
    
    /*unsigned int bytesPerPeriod1 = sampleFrequency / freq1;
    unsigned int bytesPerPeriod2 = sampleFrequency / freq2;
    
    for (int i=0;i<len;i++) {
        int channel1 = int(10*sin(fase1*16.28/bytesPerPeriod1));
        int channel2 = int(10*sin(fase2*16.28/bytesPerPeriod2));
        
        int outputValue = channel1 + channel2;           // just add the channels
        if (outputValue > 127) outputValue = 127;        // and clip the result
        if (outputValue < -128) outputValue = -128;      // this seems a crude method, but works very well
        
        stream[i] = outputValue;
        
        fase1++;
        fase1 %= bytesPerPeriod1;
        fase2++;
        fase2 %= bytesPerPeriod2;
    }//*/
}

/////////////////////////////////////////////////////////////////////////////////////////
void MCAudio::callback( Uint8* stream, int len )
{
    if( (playbackOffset + len) > (audioFileLength*2) ) 
        playbackOffset = 0;
    memcpy( stream, &audioDecodeBuffer[ playbackOffset ], len );
    playbackOffset += len/2;
    printf( "** PLAYBACK POS: %ld  CHUNK SIZE: %d \n", playbackOffset, len );
}


//////////////////////////////////////////////////////////////////////////////////////////
void MCAudio::start()
{
    int channels = 0;
    int sampleRate = 0;
    std::string audioFilenameWithPath = stdprintf( "%smedia/audio/%s", SDL_GetBasePath(), "instrument1.ogg" );
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
    //exit(1);
    //stb_vorbis_decode_filename(const char *filename, int *channels, int *sample_rate, short **output)
    
    // -=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    
    /*if( SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO ) <0 ) {
     cout << "Unable to init SDL: " << SDL_GetError() << endl;
     return 1;
     } //*/

    /* setup audio */
    SDL_AudioSpec *desired, *obtained;
    
    /* Allocate a desired SDL_AudioSpec */
    desired = (SDL_AudioSpec *) malloc(sizeof(SDL_AudioSpec));
    
    /* Allocate space for the obtained SDL_AudioSpec */
    obtained = (SDL_AudioSpec *) malloc(sizeof(SDL_AudioSpec));
    
    /* choose a samplerate and audio-format */
    //desired->freq = 44100;
    //desired->format = AUDIO_S8;

    desired->freq = 22050;
    desired->format = AUDIO_S16SYS;
    
    /* Large audio buffers reduces risk of dropouts but increases response time.
     *
     * You should always check if you actually GOT the audiobuffer size you wanted,
     * note that not hardware supports all buffer sizes (< 2048 bytes gives problems with some
     * hardware). Older versions of SDL had a bug that caused many configuration to use a
     * buffersize of 11025 bytes, if your sdl.dll is approx. 1 Mb in stead of 220 Kb, download
     * v1.2.8 of SDL or better...)
     */
    
    //desired->samples = 4096;
    desired->samples = 4096*4;
    
    /* Our callback function */
    desired->callback = example_mixaudio;
    desired->userdata = this;
    //desired->userdata = NULL;
    
    desired->channels = 2;
    
    /* Open the audio device and start playing sound! */
    if ( SDL_OpenAudio(desired, obtained) < 0 ) {
        fprintf(stderr, "AudioMixer, Unable to open audio: %s\n", SDL_GetError());
        exit(1);
    }
    
    audioBufferSize = obtained->samples;
    sampleFrequency = obtained->freq;
    
    /* if the format is 16 bit, two bytes are written for every sample */
    /*if (obtained->format==AUDIO_U16 || obtained->format==AUDIO_S16) {
        outputAudioBufferSize = 2*audioBufferSize;
    } else {
        outputAudioBufferSize = audioBufferSize;
    }//*/
    
    //SDL_Surface *screen = SDL_SetVideoMode(200,200, 16, SDL_SWSURFACE);
    //SDL_WM_SetCaption("Audio Example",0);
    
    SDL_PauseAudio(0);
    
}
