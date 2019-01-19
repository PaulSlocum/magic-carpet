// mc_renderer.cpp
////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "SDL.h"
#include "ujpeg.h"
#include "mc_renderer.hpp"
#include "mc_application.hpp"
#include "mc_util.hpp"
#include "mc_texture_list.hpp"


//////////////////////////////////////////////////////////////////////////////////////
MCRenderer::MCRenderer( MCApplication* newApp )
{
    app = newApp;
    
    int nWidth = 800;
    int nHeight = 400;
    softSurface = SDL_CreateRGBSurface( 0, nWidth, nHeight, 32, 0, 0, 0, 0 );
    softRenderer = SDL_CreateSoftwareRenderer( softSurface );
}



//////////////////////////////////////////////////////////////////////////////////////
MCRenderer::~MCRenderer()
{
}




////////////////////////////////////////////////////////////////////////////////////////////////
void MCRenderer::drawSpinner( MCSpinner spinner )
{
    //float angle = spinnerToDraw.rotationPosition;
    const int IMAGE_WIDTH = 512; // <-- TODO: THESE SHOULD GET THE ACTUAL IMAGE SIZE PROGAMATICALLY
    const int IMAGE_HEIGHT = 512;
    SDL_Rect srcRect;
    SDL_Rect dstRect;

    srcRect.w = IMAGE_WIDTH;
    srcRect.h = IMAGE_HEIGHT;
    srcRect.x = 0;
    srcRect.y = 0;
    // ~~  -  ~~  -  ~~  -  ~~  -  
    dstRect.w = app->screenWidth * spinner.size;
    dstRect.h = app->screenWidth * spinner.size;
    dstRect.x = (app->screenWidth - dstRect.w) / 2 + ( (spinner.xPosition-0.5) * 2 * app->screenWidth);
    dstRect.y = (app->screenHeight - dstRect.h) / 2 + ( (spinner.yPosition-0.5) * 2 * app->screenHeight);

    //SDL_RenderCopyEx( softRenderer, spinnerTextureArray[0], &srcRect, &dstRect, angle, NULL, SDL_FLIP_NONE );
    SDL_RenderCopyEx( app->SDLRenderer, spinnerTextureArray[ spinner.texture ], &srcRect, &dstRect, spinner.rotationPosition, NULL, SDL_FLIP_NONE );
}



/////////////////////////////////////////////////////////////////////////////////////
void MCRenderer::render()
{
    frameCount++;

    // CLEAR THE SCREEN
    SDL_RenderClear( app->SDLRenderer );
    
    // DRAW SPINNERS
    for( int spinnerNumber=0; spinnerNumber<MAX_ACTIVE_SPINNERS; spinnerNumber++ )
    {
        if( app->spinnerArray[spinnerNumber].active == true )
            drawSpinner( app->spinnerArray[ spinnerNumber ] );
    }
    
    // RENDER! -- THIS FUNCTION BLOCKS UNTIL VSYNC IF VSYNC IS ENABLED AND WORKS ON THE PLATFORM (CURRENTLY DOES NOT WORK ON RPI)
    SDL_RenderPresent( app->SDLRenderer );
    
    // UPDATE TIMER
    if( startTimeMSec == 0 )
       startTimeMSec = getCurrentTimeMSec();
    
    // DEBUG!!!  SHOW FPS
    if( frameCount % 60 == 0 )
        printf( "FPS: %f\n",  frameCount * 1000.0 / ( getCurrentTimeMSec() - startTimeMSec )  );
}


///////////////////////////////////////////////////////////////////
void MCRenderer::loadTextures()
{
    for( int i=0; i<TEXTURE_LOAD_LIST_LENGTH; i++ )
    {
        if( TEXTURE_LOAD_LIST[i].isUsed == true )
            loadTexture( TEXTURE_LOAD_LIST[i].filename, TEXTURE_LOAD_LIST[i].textureSlot );
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
void MCRenderer::loadTexture( const std::string imageFilename, int arrayPosition )
{
    //---------------------
    // LOAD JPEG
    uJPEG jpeg;
    std::string imageFilenameWithPath = stdprintf( "%smedia/images/%s", SDL_GetBasePath(), imageFilename.c_str() );
    printf( "FILE PATH: %s\n", imageFilenameWithPath.c_str() );
    SDL_Surface *bmp_surface = NULL;
    jpeg.decodeFile( imageFilenameWithPath.c_str() );
    if( jpeg.bad() ) 
    {
        printf("JPEG DECODING FAILED\n");
    }
    else
    {
        printf("JPEG DECODED!!!!\n");
        printf("W: %d   H: %d   COLOR:%d  SIZE:%d\n", jpeg.getWidth(), jpeg.getHeight(), jpeg.isColor(), jpeg.getImageSize() );  
        
        // CREATE SURFACE FROM JPEG
        bmp_surface = SDL_CreateRGBSurfaceFrom( (unsigned char*) jpeg.getImage(), 
                                               jpeg.getWidth(), jpeg.getHeight(), 24, jpeg.getWidth()*3, 0xFF, 0xFF00, 0xFF0000, 0 );
    }
    
    // CREATE TEXTURE FROM JPEG SURFACE
    spinnerTextureArray[arrayPosition] = SDL_CreateTextureFromSurface( app->SDLRenderer, bmp_surface );
    if( spinnerTextureArray[arrayPosition] == 0 ) 
    {
        printf( "TEXTURE CREATION FAILED\n" );
    }
    else
    {
        printf( "TEXTURE CREATED!!!!\n" );
        SDL_SetTextureBlendMode( spinnerTextureArray[arrayPosition], SDL_BLENDMODE_BLEND );  
    }
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    printf( "SURFACE --> W:%d H:%d DEPTH:%d PITCH:%d\n", bmp_surface->w, bmp_surface->h, bmp_surface->format->BitsPerPixel, bmp_surface->pitch ); 
    printf( "FORMAT:%d RMASK:%x GMASK:%x BMASK:%x AMASK:%x\n", 
           bmp_surface->format->format, bmp_surface->format->Rmask, bmp_surface->format->Gmask, bmp_surface->format->Bmask, bmp_surface->format->Amask );
    
    // FREE SURFACE MEMORY
    SDL_FreeSurface(bmp_surface); //*/
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
}
