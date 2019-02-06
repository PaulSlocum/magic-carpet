// mc_application.cpp
/////////////////////////////////////////////////////////////////////////////////

#include <string>
#include "mc_application.hpp"
#include "mc_renderer.hpp"
#include "mc_util.hpp"


//////////////////////////////////////////////////////////////////////////////////////
MCApplication::MCApplication()
{
    unsigned int randomSeed = (unsigned int) getCurrentTimeMSec(); 
    srand( randomSeed  );
    
#ifdef PLATFORM_RPI
    vsyncEnabled = false;
#else
    vsyncEnabled = true;
#endif    

    renderer = new MCRenderer( this );
    gameController = new MCGame( this );
}




//////////////////////////////////////////////////////////////////////////////////////
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
        // INITIALIZE SDL
        if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0 ) 
        {
            logerr( "Unable to initialize SDL: %s", SDL_GetError() );
        }
        else
        {
            appStarted = true;
            
            // HIDE MOUSE CURSOR
            SDL_ShowCursor( false );

            // SET IOS ALLOWED ORIENTATIONS
            SDL_SetHint( SDL_HINT_ORIENTATIONS, "LandscapeLeft LandscapeRight" );

            // START RENDERER AND GAME CONTROLLER
            renderer->start();
            gameController->start();
            
            // THE RUNLOOP BLOCKS UNTIL PROGRAM IS FINISHED...
            runLoop();
            
            // STOP AND QUIT SDL
            gameController->stop();
            renderer->stop();
            SDL_Quit();
            appStarted = false;
        }
    }
}




/////////////////////////////////////////////////////////////////////////////////////
void MCApplication::stop()
{
    isQuitting = true;
}



////////////////////////////////////////////////////////////////////////////////////
void MCApplication::loadJpegTexture( const std::string filename, const int textureNumber )
{
    renderer->loadJpegTexture( filename, textureNumber );
}




/////////////////////////////////////////////////////////////////////////////////////
void MCApplication::runLoop()
{
    isQuitting = false;
    bool readyToPresent = false;
    long long timeOfNextFrameMSec = getCurrentTimeMSec() + 1000.0/FRAMES_PER_SECOND;
    SDL_Event incomingEvent;

    // MAIN LOOP...
    while( isQuitting == false )
    {
        if( readyToPresent == false )
        {
            // PROCESS ALL EVENTS IN QUEUE...
            while( SDL_PollEvent( &incomingEvent ) ) 
            {
                switch( incomingEvent.type )
                {
                    case SDL_QUIT: 
                        stop(); 
                        break;
                        
                    case SDL_FINGERDOWN: 
                    case SDL_FINGERUP:
                    case SDL_FINGERMOTION:
                    case SDL_KEYDOWN:
                    case SDL_KEYUP:
                        gameController->processEvent( incomingEvent );
                        break;
                }
            }

            // UPDATE FRAME/RENDER
            gameController->updateFrame();
            renderer->render();

            readyToPresent = true;
        }

        if( readyToPresent == true )
        {
            const int EARLY_OFFSET_MSEC = 0;
            if( (vsyncEnabled == true)  ||  (timeOfNextFrameMSec <= getCurrentTimeMSec() + EARLY_OFFSET_MSEC) )
            {
                renderer->presentBuffer();
                timeOfNextFrameMSec = getCurrentTimeMSec() + 1000.0/FRAMES_PER_SECOND;
                readyToPresent = false;
            }
        }
        
        SDL_Delay(1);
    }
}


