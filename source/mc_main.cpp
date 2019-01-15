////////////////////////////////////////////////////////////////////////////////////////
// mc_main.cpp
////////////////////////////////////////////////////////////////////////////////////////


#include <string>
#include "SDL.h"
#include "ujpeg.h"
#include "mc_util.hpp"
#include "mc_application.hpp"


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480


static SDL_Texture *texture = NULL;

//=======================================================================
void render(SDL_Renderer *renderer)
{
    // CLEAR THE SCREEN
    SDL_RenderClear(renderer);

    // DRAW RUG IMAGE ON SCREEN ROTATED
    static float angle;
    angle += 10.1;
    const int IMAGE_SIZE = 512;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    /* setup rects for drawing */
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = IMAGE_SIZE;
    srcRect.h = IMAGE_SIZE;
    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = IMAGE_SIZE;
    dstRect.h = IMAGE_SIZE;
    SDL_RenderCopyEx( renderer, texture, &srcRect, &dstRect, angle, NULL, SDL_FLIP_NONE );
    /*int SDL_RenderCopyEx(SDL_Renderer*          renderer,
                         SDL_Texture*           texture,
                         const SDL_Rect*        srcrect,
                         const SDL_Rect*        dstrect,
                         const double           angle,
                         const SDL_Point*       center,
                         const SDL_RendererFlip flip) //*/

    // RENDER!
    SDL_RenderPresent(renderer);
}



//=======================================================================
int main(int argc, char *argv[])
{
    MCApplication magicCarpetApp;
    magicCarpetApp.start();
    
    
    SDL_Window *window;
    SDL_Renderer *renderer;
    int isQuitting;
    SDL_Event event;

    // INITIALIZE SDL
    if( SDL_Init(SDL_INIT_VIDEO) < 0 ) 
    {
        printf("Could not initialize SDL\n");
        return 1;
    }

    printf( "---------------------------------------\n" );

    //---------------------
    // JPEG LOADER
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

        // CREATE SURFACE
        bmp_surface = SDL_CreateRGBSurfaceFrom( (unsigned char*) uj.getImage(), 
                                               uj.getWidth(), uj.getHeight(), 24, uj.getWidth()*3, 0xFF, 0xFF00, 0xFF0000, 0 );
    }
    
    // SEED RANDOM NUMBER GENERATOR
    srand(time(NULL));

    // CREATE SDL WINDOW
    window = SDL_CreateWindow(NULL, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if( !window ) 
    {
        printf("Could not initialize Window\n");
        return 1;
    }

    // CREATE SDL RENDERED IN WINDOW
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        printf("Could not create renderer\n");
        return 1;
    }
    
    // CREATE TEXTURE FROM JPEG SURFACE
    texture = SDL_CreateTextureFromSurface( renderer, bmp_surface );
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
    
    //*************************************************************************
    // RUN LOOP
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
        render(renderer);
        SDL_Delay(1);
    }
    //*************************************************************************

    // QUIT SDL
    SDL_Quit();

    return 0;
}
