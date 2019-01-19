// mc_application.cpp
/////////////////////////////////////////////////////////////////////////////////

#include <string>

#include "mc_application.hpp"
#include "mc_renderer.hpp"
#include "mc_util.hpp"
#include "mc_game.hpp"







//////////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
MCApplication::MCApplication()
{
    // SEED RANDOM NUMBER GENERATOR
    srand( (unsigned int) time(NULL) );
    
    renderer = new MCRenderer( this );
    game = new MCGame( this );
}


//////////////////////////////////////////////////////////////////////////////////////
// DESTRUCTOR
MCApplication::~MCApplication()
{
    delete renderer;
}






/////////////////////////////////////////////////////////////////////////////////////
// THIS FUNCTION BLOCKS UNTIL THE APPLICATION CLOSES OR stop() IS CALLED.
// SINCE CURRENTLY THERE IS NO COMMAND INTERNALLY TO CLOSE THE PROGRAM, stop() SHOULD PROBABLY BE IMPLEMENTED WITHIN MAIN
// ...ALTHOUGH -- DOES SDL ALREADY IMPLEMENT THE CTRL-C INTERRUPT AND GENERATE A "QUIT" COMMAND?
void MCApplication::start()
{
    mode = AppMode::LOADING;
    
    // INITIALIZE SDL
    if( SDL_Init(SDL_INIT_VIDEO) != 0 ) 
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
    
    // RUN LOOP BLOCKS UNTIL PROGRAM IS FINISHED...
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
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                isQuitting = true;
            }
        }
        
        // DRAW SCREEN...
        if( (vsyncEnabled == true)  ||  (timeOfNextFrameMSec <= getCurrentTimeMSec() + 0) )
        {
            if( mode == AppMode::LOADING )
            {
                renderer->loadTextures();
                mode = AppMode::MENU;
            }
            if( mode == AppMode::MENU || mode == AppMode::RUNNING )
            {
                game->updateFrame();
                renderer->render();
            }
            timeOfNextFrameMSec = getCurrentTimeMSec() + 1000.0/FRAMES_PER_SECOND;
        }

        SDL_Delay(2);
    }
}


