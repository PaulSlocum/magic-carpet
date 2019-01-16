// mc_application.cpp
/////////////////////////////////////////////////////////////////////////////////

#include <string>

#include "mc_application.hpp"
#include "mc_renderer.hpp"
#include "mc_util.hpp"


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480




#pragma mark CONSTRUCTOR / DESTRUCTOR


//////////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
MCApplication::MCApplication()
{
    // SEED RANDOM NUMBER GENERATOR
    srand( (unsigned int) time(NULL) );
    
    renderer = new MCRenderer( this );
}


//////////////////////////////////////////////////////////////////////////////////////
// DESTRUCTOR
MCApplication::~MCApplication()
{
    delete renderer;
}



#pragma mark START / STOP 




/////////////////////////////////////////////////////////////////////////////////////
// THIS FUNCTION BLOCKS UNTIL THE APPLICATION CLOSES OR stop() IS CALLED.
// SINCE CURRENTLY THERE IS NO COMMAND INTERNALLY TO CLOSE THE PROGRAM, stop() SHOULD PROBABLY BE IMPLEMENTED WITHIN MAIN
void MCApplication::start()
{
    mode = AppMode::LOADING;
    
    // INITIALIZE SDL
    if( SDL_Init(SDL_INIT_VIDEO) != 0 ) 
    {
        SDL_Log( "Unable to initialize SDL: %s", SDL_GetError() );
    }

    // SET IOS ALLOWED ORIENTATIONS
    SDL_SetHint( SDL_HINT_ORIENTATIONS, "LandscapeLeft LandscapeRight" );
    
    SDL_Rect screenSize;
    SDL_GetDisplayBounds( 0, &screenSize );
    printf( "SCREEN SIZE: %d x %d \n", screenSize.w, screenSize.h );
    
    // CREATE SDL WINDOW
    window = SDL_CreateWindow( NULL, 0, 0, screenSize.w, screenSize.h, SDL_WINDOW_OPENGL );
    if( !window ) 
    {
        printf("Could not initialize Window\n");
        return;
    }
    
    // CREATE SDL RENDERED IN WINDOW
    SDLRenderer = SDL_CreateRenderer( window, -1, 0 );
    if( !renderer ) 
    {
        printf("Could not create renderer\n");
        return;
    }
    

    runLoop();
    
    // QUIT SDL
    SDL_Quit();
}


/////////////////////////////////////////////////////////////////////////////////////
void MCApplication::stop()
{
    isQuitting = true;
    mode = AppMode::STOPPED;
}


#pragma mark RUN LOOP

/////////////////////////////////////////////////////////////////////////////////////
void MCApplication::runLoop()
{
    SDL_Event event;
    isQuitting = 0;
    long long timeOfNextFrameMSec = getCurrentTimeMSec() + 1000.0/FRAMES_PER_SECOND;
    while( !isQuitting )
    {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                isQuitting = 1;
            }
        }
        
        if( timeOfNextFrameMSec <= getCurrentTimeMSec() + 10 )
        {
            if( mode == AppMode::LOADING )
            {
                renderer->loadTextures();
                mode = AppMode::MENU;
            }
            if( mode == AppMode::MENU || mode == AppMode::RUNNING )
                renderer->render();
            timeOfNextFrameMSec = getCurrentTimeMSec() + 1000.0/FRAMES_PER_SECOND;
        }
        //render( SDLRenderer );
        SDL_Delay(1);
    }
}


