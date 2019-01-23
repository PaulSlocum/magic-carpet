// mc_application.cpp
/////////////////////////////////////////////////////////////////////////////////

#include "SDL.h"

#include <string>

#include "mc_application.hpp"
#include "mc_renderer.hpp"
#include "mc_util.hpp"
#include "mc_game.hpp"
#include "mc_input.hpp"
#include "mc_audio.hpp"




//////////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
MCApplication::MCApplication()
{
    // SEED RANDOM NUMBERS
    srand( (unsigned int) time(NULL) );
    
    renderer = new MCRenderer( &state );
    audioController = new MCAudio( &state );
    gameController = new MCGame( &state );
    inputHandler = new MCInput( &state );
    
}




//////////////////////////////////////////////////////////////////////////////////////
// DESTRUCTOR
MCApplication::~MCApplication()
{
    delete inputHandler;
    delete gameController;
    delete audioController;
    delete renderer;
}



/////////////////////////////////////////////////////////////////////////////////////
// NOTE: THIS FUNCTION BLOCKS UNTIL THE APPLICATION CLOSES OR stop() IS CALLED.
void MCApplication::start()
{
    if( state.mode == AppMode::STOPPED )
    {
        state.mode = AppMode::LOADING;
     
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
        audioController->start();
        renderer->start();
        
        gameController->init();
        
#ifdef PLATFORM_RPI
        vsyncEnabled = false;
#else
        vsyncEnabled = true;
#endif    
        
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


