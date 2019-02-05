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
            
#ifdef PLATFORM_RPI
            vsyncEnabled = false;
#else
            vsyncEnabled = true;
#endif    
            
            // THIS BLOCKS UNTIL PROGRAM IS FINISHED...
            runLoop();
            
            // QUIT SDL
            SDL_Quit();
            gameController->stop();
            appStarted = false;
        }
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
    enum class LoopState {POLL, DRAW, PRESENT};
    LoopState loopState = LoopState::POLL;
    renderer->loadTextures();
    while( isQuitting == false )
    {
        switch( loopState )
        {
            case LoopState::POLL:
            {
                // PROCESS ALL EVENTS IN QUEUE...
                while( SDL_PollEvent( &event ) ) 
                {
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
                loopState = LoopState::DRAW;
                break;
            }

            case LoopState::DRAW:
            {
                gameController->updateFrame();
                renderer->render();
                loopState = LoopState::PRESENT;
                break;
            }

            case LoopState::PRESENT:
            {
                const int EARLY_OFFSET_MSEC = 0;
                if( (vsyncEnabled == true)  ||  (timeOfNextFrameMSec <= getCurrentTimeMSec() + EARLY_OFFSET_MSEC) )
                {
                    renderer->presentBuffer();
                    loopState = LoopState::POLL;
                    timeOfNextFrameMSec = getCurrentTimeMSec() + 1000.0/FRAMES_PER_SECOND;
                }
                break;
            }
                
        } // SWITCH
        
        SDL_Delay(1);
    }
}


