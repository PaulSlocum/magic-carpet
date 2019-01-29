// mc_renderer.cpp
////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <stdlib.h>
#include "SDL.h"
#include "ujpeg.h"
#include "mc_renderer.hpp"
#include "mc_application.hpp"
#include "mc_util.hpp"
#include "mc_texture_list.hpp"


//////////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
MCRenderer::MCRenderer( MCApplication* newApp )
{
    app = newApp;
}



//////////////////////////////////////////////////////////////////////////////////////
// DESTRUCTOR
MCRenderer::~MCRenderer()
{
}



/////////////////////////////////////////////////////////////////////////////////////
void MCRenderer::start()
{
    SDL_Rect screenSize;
    SDL_GetDisplayBounds( 0, &screenSize );
    printf( "DISPLAY BOUNDS: %d x %d \n", screenSize.w, screenSize.h );
    
    // CREATE SDL WINDOW
    window = SDL_CreateWindow( NULL, 0, 0, screenSize.w, screenSize.h, SDL_WINDOW_FULLSCREEN );
    
    if( !window ) 
    {
        printf("Could not initialize Window\n");
        return;
    }
    
    // CREATE SDL RENDERED IN WINDOW
    SDLRenderer = SDL_CreateRenderer( window, -1, 0 );
    if( !SDLRenderer ) 
    {
        printf("Could not create renderer\n");
        return;
    }
    
    SDL_GetWindowSize( window, &screenWidth, &screenHeight );
    printf( "WINDOW SIZE: %d x %d \n", screenWidth, screenHeight );
}




///////////////////////////////////////////////////////////////////////////////////
void MCRenderer::drawSprite( const MCSprite sprite )
{
    if( sprite.active == true )
    {
        SDL_Texture* spinnerTexture;
        spinnerTexture = spinnerTextureArray[ sprite.texture ]; 
        
        // GET TEXTURE SIZE
        int textureHeight;
        int textureWidth;
        SDL_QueryTexture( spinnerTexture, NULL, NULL, &textureHeight, &textureWidth ); 
        
        // SETUP SOURCE/DECT RECTS FOR COPY
        SDL_Rect srcRect = { 0, 0, textureWidth, textureHeight };
        SDL_Rect dstRect;
        dstRect.w = screenWidth * sprite.size;
        //dstRect.h = screenWidth * sprite.size;
        dstRect.h = screenHeight * sprite.size;
        dstRect.x = (screenWidth - dstRect.w) / 2 + ( (sprite.xPosition-0.5) * 2 * screenWidth);
        dstRect.y = (screenHeight - dstRect.h) / 2 + ( (sprite.yPosition-0.5) * 2 * screenHeight);

        SDL_RenderCopyEx( SDLRenderer, spinnerTexture, &srcRect, &dstRect, sprite.rotationPosition, NULL, SDL_FLIP_NONE );

        // DEBUG - EVENTUALLY PROBABLY WANT TO CONVERT THIS RENDERER TO A RENGER TARGET
        //SDL_RenderCopyEx( softRenderer, spinnerTextureArray[0], &srcRect, &dstRect, angle, NULL, SDL_FLIP_NONE );
    }
}



/////////////////////////////////////////////////////////////////////////////////////
void MCRenderer::render()
{
    // THE DRAW COLOR IS USED AS THE BACKGROUND COLOR WHEN CLEARNING THE SCREEN
    SDL_SetRenderDrawColor( SDLRenderer, app->backgroundColor.red * 255.0, 
                           app->backgroundColor.green * 255.0, 
                           app->backgroundColor.blue * 255.0, 
                           255 );
    
    // CLEAR THE SCREEN
    SDL_RenderClear( SDLRenderer );
    
    // DRAW EVERYTHING FROM THE SPRITE RENDER LIST
    for( unsigned i=0; i < app->spriteRenderList.size(); i++ )
        drawSprite( app->spriteRenderList[i] );
}


/////////////////////////////////////////////////////////////////////////////////////
void MCRenderer::presentBuffer()
{
    // !!! THIS FUNCTION BLOCKS UNTIL VSYNC IF VSYNC IS ENABLED/SUPPORTED ON THE PLATFORM (CURRENTLY DOES NOT WORK ON RPI)
    SDL_RenderPresent( SDLRenderer );
}



///////////////////////////////////////////////////////////////////
void MCRenderer::loadTextures()
{
    // LOAD ALL TEXTURES FROM TEXTURE LIST ARRAY IN HEADER...
    bool loadingTextures = true;
    int spriteListIndex = 0;
    for( int i=0; loadingTextures == true; i++ )
    {
        // QUIT WHEN A BLANK FILENAME IS ENCOUNTERED
        if( TEXTURE_LOAD_LIST[i].filename[0] == 0 )
            loadingTextures = false;
        else
        {
            if( TEXTURE_LOAD_LIST[i].type != TextureType::UNUSED )
            {
                // LOAD TEXTURE FROM JPEG FILE
                spinnerTextureArray[ TEXTURE_LOAD_LIST[i].textureSlot ] = loadJpegTexture( TEXTURE_LOAD_LIST[i].filename );

                // SHOW TEXTURES AS THEY'RE LOADING..
                MCSprite tempSpinner;
                tempSpinner.size = i/150.0;
                tempSpinner.yPosition = 0.40;
                tempSpinner.active = true;
                tempSpinner.texture = TEXTURE_LOAD_LIST[i].textureSlot;
                tempSpinner.rotationPosition = i*15.0;
                if( TEXTURE_LOAD_LIST[i].type == TextureType::BACKGROUND )
                {
                    tempSpinner.size = 1.0;
                    tempSpinner.rotationPosition = 0;
                    tempSpinner.yPosition = 0.50;
                }
                app->spriteRenderList[ spriteListIndex ] = tempSpinner;
                spriteListIndex++;
                render();
                presentBuffer();
            }
        }
    }
}




//////////////////////////////////////////////////////////////////////////////////////////
SDL_Texture* MCRenderer::loadJpegTexture( const std::string imageFilename )
{
    // LOAD JPEG
    uJPEG jpeg;
    std::string imageFilenameWithPath = stdprintf( "%smedia/images/%s", SDL_GetBasePath(), imageFilename.c_str() );
    SDL_Surface *bmp_surface = NULL;
    jpeg.decodeFile( imageFilenameWithPath.c_str() );
    if( jpeg.bad() ) 
    {
        printf("JPEG DECODING FAILED\n");
    }
    else
    {
        // CREATE SURFACE FROM JPEG
        bmp_surface = SDL_CreateRGBSurfaceFrom( (unsigned char*) jpeg.getImage(), 
                                               jpeg.getWidth(), jpeg.getHeight(), 24, jpeg.getWidth()*3, 0xFF, 0xFF00, 0xFF0000, 0 );
    }
    
    // CREATE TEXTURE FROM JPEG SURFACE
    SDL_Texture* texture = SDL_CreateTextureFromSurface( SDLRenderer, bmp_surface );
    if( texture == 0 ) 
    {
        printf( "TEXTURE CREATION FAILED\n" );
    }
    else
    {   
        // NOT TOTALLY SURE WHAT THIS DOES (COPIED FROM ORIGINAL CODE)
        SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );  
    }
    
    // FREE SURFACE MEMORY
    SDL_FreeSurface(bmp_surface); //*/
    
    return( texture );
}









