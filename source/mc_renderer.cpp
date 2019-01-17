// mc_renderer.cpp
////////////////////////////////////////////////////////////////////////

#include "SDL.h"

#include "ujpeg.h"

#include "mc_renderer.hpp"
#include "mc_application.hpp"
#include "mc_util.hpp"



//////////////////////////////////////////////////////////////////////////////////////
MCRenderer::MCRenderer( MCApplication* newApp )
{
    app = newApp;
}



//////////////////////////////////////////////////////////////////////////////////////
MCRenderer::~MCRenderer()
{
}




/////////////////////////////////////////////////////////////////////////////////////
void MCRenderer::render()
{
    frameCount++;

    // CLEAR THE SCREEN
    SDL_RenderClear( app->SDLRenderer );
    
    // DRAW RUG IMAGE ON SCREEN ROTATED
    static float angle;
    angle = frameCount * 10.1;
    const int IMAGE_SIZE = 512;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    /* setup rects for drawing */
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = IMAGE_SIZE;
    srcRect.h = IMAGE_SIZE;
    dstRect.x = (frameCount % app->screenSize.w) - IMAGE_SIZE/2;
    dstRect.y = 0;
    dstRect.w = IMAGE_SIZE;
    dstRect.h = IMAGE_SIZE;
    SDL_RenderCopyEx( app->SDLRenderer, spinnerTextureArray[0], &srcRect, &dstRect, angle, NULL, SDL_FLIP_NONE );
    dstRect.w = IMAGE_SIZE/2;
    dstRect.h = IMAGE_SIZE/2;
    SDL_RenderCopyEx( app->SDLRenderer, spinnerTextureArray[1], &srcRect, &dstRect, angle*3, NULL, SDL_FLIP_NONE );
    /*int SDL_RenderCopyEx(SDL_Renderer*          renderer,
     SDL_Texture*           texture,
     const SDL_Rect*        srcrect,
     const SDL_Rect*        dstrect,
     const double           angle,
     const SDL_Point*       center,
     const SDL_RendererFlip flip) //*/
    
    // RENDER! -- THIS FUNCTION BLOCKS UNTIL VSYNC IF VSYNC IS ENABLED / WORKS ON THE SYSTEM
    SDL_RenderPresent( app->SDLRenderer );
    
    //-------------------------------------------------------
    if( startTimeMSec == 0 )
       startTimeMSec = getCurrentTimeMSec();
    if( frameCount % 60 == 0 )
        printf( "FPS: %f\n",  frameCount * 1000.0 / ( getCurrentTimeMSec() - startTimeMSec )  );
    
}


///////////////////////////////////////////////////////////////////
void MCRenderer::loadTextures()
{
    loadTexture( "media/images/pattern0.jpg", 0 );
    loadTexture( "media/images/pattern1.jpg", 1 );
}


//////////////////////////////////////////////////////////////////////////////////////////
void MCRenderer::loadTexture( const std::string imageFilename, int arrayPosition )
{
    //---------------------
    // LOAD JPEG
    uJPEG jpeg;
    std::string imageFilenameWithPath = stdprintf( "%s%s", SDL_GetBasePath(), imageFilename.c_str() );
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
