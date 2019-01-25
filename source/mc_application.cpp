// mc_application.cpp
/////////////////////////////////////////////////////////////////////////////////

#include "SDL.h"
#include <string>
#include "mc_application.hpp"
#include "mc_renderer.hpp"
#include "mc_util.hpp"
#include "mc_game.hpp"


//////////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
MCApplication::MCApplication()
{
    // SEED RANDOM NUMBERS
    srand( (unsigned int) time(NULL) );
    
    renderer = new MCRenderer( this );
    gameController = new MCGame( this );
}




//////////////////////////////////////////////////////////////////////////////////////
// DESTRUCTOR
MCApplication::~MCApplication()
{
    delete gameController;
    delete renderer;
}



/////////////////////////////////////////////////////////////////////////////////////
// NOTE: THIS FUNCTION BLOCKS UNTIL THE APPLICATION CLOSES OR stop() IS CALLED.
void MCApplication::start()
{
    if( appStarted == false )
    {
        appStarted = true;
     
        // INITIALIZE SDL
        if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0 ) 
        {
            SDL_Log( "Unable to initialize SDL: %s", SDL_GetError() );
        }

        // HIDE MOUSE CURSOR
        SDL_ShowCursor( false );

        // SET IOS ALLOWED ORIENTATIONS
        SDL_SetHint( SDL_HINT_ORIENTATIONS, "LandscapeLeft LandscapeRight" );

        // START AUDIO SYSTEM
        renderer->start();
        
        gameController->start();
        
#ifdef PLATFORM_RPI
        vsyncEnabled = false;
#else
        vsyncEnabled = true;
#endif    
        
        // RUN LOOP BLOCKS UNTIL PROGRAM IS FINISHED...
        runLoop();
        
        // QUIT SDL
        SDL_Quit();
        gameController->stop();
        appStarted = false;
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

    renderer->loadTextures();

    // MAIN LOOP...
    while( isQuitting == false )
    {
        // PROCESS ALL EVENTS IN QUEUE...
        while( SDL_PollEvent( &event ) ) 
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
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    gameController->processEvent( event );
                    break;
            }
        }
        
        // LOAD TEXTURES / DRAW SCREEN...
	const int EARLY_OFFSET_MSEC = 7;
        if( (vsyncEnabled == true)  ||  (timeOfNextFrameMSec <= getCurrentTimeMSec() + EARLY_OFFSET_MSEC) )
        {
            gameController->updateFrame();

            renderer->render();
            timeOfNextFrameMSec = getCurrentTimeMSec() + 1000.0/FRAMES_PER_SECOND;
        }

        SDL_Delay(1);
    }
}


