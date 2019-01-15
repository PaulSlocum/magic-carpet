// mc_application.cpp
/////////////////////////////////////////////////////////////////////////////////

#include <string>

#include "ujpeg.h"

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
    // SEED RANDOM NUMBER GENERATOR
    srand( (unsigned int) time(NULL) );
    
    // INITIALIZE SDL
    if( SDL_Init(SDL_INIT_VIDEO) != 0 ) 
    {
        SDL_Log( "Unable to initialize SDL: %s", SDL_GetError() );
    }

    // CREATE SDL WINDOW
    window = SDL_CreateWindow(NULL, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if( !window ) 
    {
        printf("Could not initialize Window\n");
        return;
    }
    
    // CREATE SDL RENDERED IN WINDOW
    SDLRenderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        printf("Could not create renderer\n");
        return;
    }
    
    //---------------------
    // LOAD JPEG
    uJPEG uj;
    std::string imageFilename = stdprintf( "%s%s", SDL_GetBasePath(), "media/images/pattern0.jpg" );
    printf( "FILE PATH: %s\n", imageFilename.c_str() );
    SDL_Surface *bmp_surface = NULL;
    uj.decodeFile( imageFilename.c_str() );
    if( uj.bad() ) 
    {
        printf("JPEG DECODING FAILED\n");
    }
    else
    {
        printf("JPEG DECODED!!!!\n");
        printf("W: %d   H: %d   COLOR:%d  SIZE:%d\n", uj.getWidth(), uj.getHeight(), uj.isColor(), uj.getImageSize() );  
        
        // CREATE SURFACE FROM JPEG
        bmp_surface = SDL_CreateRGBSurfaceFrom( (unsigned char*) uj.getImage(), 
                                               uj.getWidth(), uj.getHeight(), 24, uj.getWidth()*3, 0xFF, 0xFF00, 0xFF0000, 0 );
    }
    
    // CREATE TEXTURE FROM JPEG SURFACE
    texture = SDL_CreateTextureFromSurface( SDLRenderer, bmp_surface );
    if( texture == 0 ) 
    {
        printf( "TEXTURE CREATION FAILED\n" );
    }
    else
    {
        printf( "TEXTURE CREATED!!!!\n" );
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);  
    }
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    printf( "SURFACE --> W:%d H:%d DEPTH:%d PITCH:%d\n", bmp_surface->w, bmp_surface->h, bmp_surface->format->BitsPerPixel, bmp_surface->pitch ); 
    printf( "FORMAT:%d RMASK:%x GMASK:%x BMASK:%x AMASK:%x\n", 
           bmp_surface->format->format, bmp_surface->format->Rmask, bmp_surface->format->Gmask, bmp_surface->format->Bmask, bmp_surface->format->Amask );
    
    // FREE SURFACE MEMORY
    SDL_FreeSurface(bmp_surface); //*/
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    runLoop();
    
    // QUIT SDL
    SDL_Quit();
}


/////////////////////////////////////////////////////////////////////////////////////
void MCApplication::stop()
{
    isQuitting = true;
}


#pragma mark RUN LOOP

/////////////////////////////////////////////////////////////////////////////////////
void MCApplication::runLoop()
{
    SDL_Event event;
    isQuitting = 0;
    while( !isQuitting )
    {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) 
            {
                isQuitting = 1;
            }
        }
        renderer->render();
        //render( SDLRenderer );
        SDL_Delay(1);
    }
}


