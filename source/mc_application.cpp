// mc_application.cpp
/////////////////////////////////////////////////////////////////////////////////

#include "SDL.h"

#include <string>

#include "mc_application.hpp"
#include "mc_renderer.hpp"
#include "mc_util.hpp"
#include "mc_game.hpp"
#include "mc_input.hpp"




//////////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
MCApplication::MCApplication()
{
    // SEED RANDOM NUMBERS
    srand( (unsigned int) time(NULL) );
    
    renderer = new MCRenderer( this );
    gameController = new MCGame( &state );
    inputHandler = new MCInput( &state );
}




//////////////////////////////////////////////////////////////////////////////////////
// DESTRUCTOR
MCApplication::~MCApplication()
{
    delete renderer;
    delete gameController;
}


unsigned int sampleFrequency = 0;
unsigned int audioBufferSize = 0;
unsigned int outputAudioBufferSize = 0;

unsigned int freq1 = 1000;
unsigned int fase1 = 0;
//unsigned int freq2 = 5000;
unsigned int freq2 = 1010;
unsigned int fase2 = 0;


//=======================================================================================
void example_mixaudio(void *unused, Uint8 *stream, int len) {
    
    unsigned int bytesPerPeriod1 = sampleFrequency / freq1;
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
    }
}


//==============================================================================
void startAudio()
{
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
    desired->freq = 44100;
    desired->format = AUDIO_S8;
    
    /* Large audio buffers reduces risk of dropouts but increases response time.
     *
     * You should always check if you actually GOT the audiobuffer size you wanted,
     * note that not hardware supports all buffer sizes (< 2048 bytes gives problems with some
     * hardware). Older versions of SDL had a bug that caused many configuration to use a
     * buffersize of 11025 bytes, if your sdl.dll is approx. 1 Mb in stead of 220 Kb, download
     * v1.2.8 of SDL or better...)
     */
    desired->samples = 4096;
    
    /* Our callback function */
    desired->callback=example_mixaudio;
    desired->userdata=NULL;
    
    desired->channels = 1;
    
    /* Open the audio device and start playing sound! */
    if ( SDL_OpenAudio(desired, obtained) < 0 ) {
        fprintf(stderr, "AudioMixer, Unable to open audio: %s\n", SDL_GetError());
        exit(1);
    }
    
    audioBufferSize = obtained->samples;
    sampleFrequency = obtained->freq;
    
    /* if the format is 16 bit, two bytes are written for every sample */
    if (obtained->format==AUDIO_U16 || obtained->format==AUDIO_S16) {
        outputAudioBufferSize = 2*audioBufferSize;
    } else {
        outputAudioBufferSize = audioBufferSize;
    }
    
    //SDL_Surface *screen = SDL_SetVideoMode(200,200, 16, SDL_SWSURFACE);
    //SDL_WM_SetCaption("Audio Example",0);
    
    SDL_PauseAudio(0);

}


/////////////////////////////////////////////////////////////////////////////////////
// NOTE: THIS FUNCTION BLOCKS UNTIL THE APPLICATION CLOSES OR stop() IS CALLED.
void MCApplication::start()
{
    if( state.mode == AppMode::STOPPED )
    {
        state.mode = AppMode::LOADING;
     
        // INITIALIZE SDL
        //if( SDL_Init(SDL_INIT_VIDEO) != 0 ) 
        if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0 ) 
        {
            SDL_Log( "Unable to initialize SDL: %s", SDL_GetError() );
        }

        // HIDE MOUSE CURSOR
        SDL_ShowCursor( false );

        // SET IOS ALLOWED ORIENTATIONS
        SDL_SetHint( SDL_HINT_ORIENTATIONS, "LandscapeLeft LandscapeRight" );

        SDL_Rect screenSize;
        SDL_GetDisplayBounds( 0, &screenSize );
        printf( "DISPLAY BOUNDS: %d x %d \n", screenSize.w, screenSize.h );

        // CREATE SDL WINDOW
        window = SDL_CreateWindow( NULL, 0, 0, screenSize.w, screenSize.h, SDL_WINDOW_FULLSCREEN );
        //window = SDL_CreateWindow( NULL, 0, 0, screenSize.w, screenSize.h, SDL_WINDOW_OPENGL );
        
        if( !window ) 
        {
            printf("Could not initialize Window\n");
            return;
        }

        // DEBUG! - SET WINDOW SIZE?
        //SDL_SetWindowSize( window, 500, 250 ); 

        // DEBUG -- AUDIO SYSTEM TEST
        startAudio();
        
        // CREATE SDL RENDERED IN WINDOW
        SDLRenderer = SDL_CreateRenderer( window, -1, 0 );
        if( !SDLRenderer ) 
        {
            printf("Could not create renderer\n");
            return;
        }

        SDL_GetWindowSize( window, &screenWidth, &screenHeight );
        printf( "WINDOW SIZE: %d x %d \n", screenWidth, screenHeight );
        
        // DEBUG! - SET RENDER WINDOW SIZE? SCALE?
        // NOTE: THE PROBLEM IS THAT THESE ALWAYS LETTERBOX AND THERE DOESN'T SEEM TO BE A WAY TO CHANGE THAT
        //SDL_RenderSetLogicalSize( SDLRenderer, 500, 1000 );
        //SDL_RenderSetScale( SDLRenderer, 1.0, 0.2 ); 
        
    #ifdef PLATFORM_RPI
        vsyncEnabled = false;
    #else
        vsyncEnabled = true;
    #endif    
        
        gameController->init();
        
        // RUN LOOP BLOCKS UNTIL PROGRAM IS FINISHED...
        runLoop();
        
        // QUIT SDL
        SDL_Quit();
        state.mode = AppMode::STOPPED;
    }
}




/////////////////////////////////////////////////////////////////////////////////////
void MCApplication::stop()
{
    isQuitting = true;
}





/////////////////////////////////////////////////////////////////////////////////////
void MCApplication::runLoop()
{
    SDL_Event event;
    isQuitting = false;
    long long timeOfNextFrameMSec = getCurrentTimeMSec() + 1000.0/FRAMES_PER_SECOND;

    // MAIN LOOP...
    while( isQuitting == false )
    {
        // PROCESS ALL EVENTS IN QUEUE...
        while( SDL_PollEvent(&event) ) 
        {
            printf( "RECEIVED EVENT\n" );
            switch( event.type )
            {
                case SDL_QUIT: 
                    stop(); 
                    break;
                    
                case SDL_FINGERDOWN: 
                case SDL_FINGERUP:
                case SDL_FINGERMOTION:
                    inputHandler->processTouchEvent( event.tfinger );
                    break;

                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    inputHandler->processKeyboardEvent( event.key );
                    break;
            }
            if (event.type == SDL_QUIT) 
            {
                stop();
            }
        }
        
        // LOAD TEXTURES / DRAW SCREEN...
        if( (vsyncEnabled == true)  ||  (timeOfNextFrameMSec <= getCurrentTimeMSec() + 0) )
        {
            if( state.mode == AppMode::LOADING )
            {
                renderer->loadTextures();
                state.mode = AppMode::MENU;
                state.menuFadeIn = 0.0;
            }
            if( state.mode == AppMode::MENU || state.mode == AppMode::RUNNING )
            {
                gameController->updateFrame();
                renderer->render();
            }
            timeOfNextFrameMSec = getCurrentTimeMSec() + 1000.0/FRAMES_PER_SECOND;
        }

        SDL_Delay(2);
    }
}


