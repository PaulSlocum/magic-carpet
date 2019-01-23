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
MCRenderer::MCRenderer( MCApplication* newApp )
{
    app = newApp;
    
    // DEBUG - TRYING TO SET UP RENDER TARGET
    /*int nWidth = 800;
    int nHeight = 400;
    softSurface = SDL_CreateRGBSurface( 0, nWidth, nHeight, 32, 0, 0, 0, 0 );
    softRenderer = SDL_CreateSoftwareRenderer( softSurface ); //*/
}



//////////////////////////////////////////////////////////////////////////////////////
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
    //window = SDL_CreateWindow( NULL, 0, 0, screenSize.w, screenSize.h, SDL_WINDOW_OPENGL );
    
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
void MCRenderer::drawSpinner( const MCSpinner spinner )
{
    if( spinner.active == true )
    {
        SDL_Texture* spinnerTexture;
        switch( spinner.type )
        {
            case SpinnerType::SPINNER: spinnerTexture = spinnerTextureArray[ spinner.texture ]; break; 
            case SpinnerType::BUTTON: spinnerTexture = buttonTextureArray[ spinner.texture ]; break; 
            case SpinnerType::BACKGROUND: spinnerTexture = backgroundTexture; break; 
        }
        
        // GET TEXTURE SIZE
        int textureHeight;
        int textureWidth;
        SDL_QueryTexture( spinnerTexture, NULL, NULL, &textureHeight, &textureWidth ); 
        
        // SETUP SOURCE/DECT RECTS FOR COPY
        SDL_Rect srcRect = { 0, 0, textureWidth, textureHeight };
        SDL_Rect dstRect;
        dstRect.w = screenWidth * spinner.size * app->state.menuFadeIn;
        dstRect.h = screenWidth * spinner.size * app->state.menuFadeIn;
        dstRect.x = (screenWidth - dstRect.w) / 2 + ( (spinner.xPosition-0.5) * 2 * screenWidth);
        dstRect.y = (screenHeight - dstRect.h) / 2 + ( (spinner.yPosition-0.5) * 2 * screenHeight);

        SDL_RenderCopyEx( SDLRenderer, spinnerTexture, &srcRect, &dstRect, spinner.rotationPosition, NULL, SDL_FLIP_NONE );

        // DEBUG - EVENTUALLY PROBABLY WANT TO CONVERT THIS RENDERER TO A RENGER TARGET
        //SDL_RenderCopyEx( softRenderer, spinnerTextureArray[0], &srcRect, &dstRect, angle, NULL, SDL_FLIP_NONE );
    }
}



/////////////////////////////////////////////////////////////////////////////////////
void MCRenderer::render()
{
    // DEBUG! - THIS IS ONLY USED FOR THE FRAME COUNTER
    //frameCount++;

    // CLEAR THE SCREEN
    SDL_RenderClear( SDLRenderer );
    
    // DRAW EVERYTHING
    drawSpinner( app->state.background );
    drawSpinner( app->state.normalButton );
    drawSpinner( app->state.muteButton );
    drawSpinner( app->state.instrumentButton );
    for( int spinnerNumber=0; spinnerNumber<MAX_ACTIVE_SPINNERS; spinnerNumber++ )
        drawSpinner( app->state.spinnerArray[ spinnerNumber ] );
    
    // RENDER! -- THIS FUNCTION BLOCKS UNTIL VSYNC IF VSYNC IS ENABLED/SUPPORTED ON THE PLATFORM (CURRENTLY DOES NOT WORK ON RPI)
    SDL_RenderPresent( SDLRenderer );
    
    // UPDATE FRAME TIMER
    if( startTimeMSec == 0 )
       startTimeMSec = getCurrentTimeMSec();
    
    // DEBUG!!!  SHOW FPS...
    //if( frameCount % 60 == 0 )
    //    printf( "FPS: %f\n",  frameCount * 1000.0 / ( getCurrentTimeMSec() - startTimeMSec )  );
}




///////////////////////////////////////////////////////////////////
void MCRenderer::loadTextures()
{
    // LOAD MENU BACKGROUND TEXTURE (RANDOMLY SELECT ONE OF TWO IMAGES)...
    if( (rand() %2)==0 )
        backgroundTexture = loadJpegTexture( "menuBG2d.jpg" );
    else
        backgroundTexture = loadJpegTexture( "menuBG2c.jpg" );
    drawSpinner( app->state.background );
    SDL_RenderPresent( SDLRenderer );
    
    // LOAD BUTTON TEXTURES
    buttonTextureArray[ 0 ] = loadJpegTexture( "bnChalice.jpg" );
    buttonTextureArray[ 1 ] = loadJpegTexture( "bnGrid.jpg" );
    buttonTextureArray[ 2 ] = loadJpegTexture( "bnBird.jpg" );

    //std::map<int, MCSpinner> tempSpinnerArray;
    MCSpinner tempSpinner;
    
    // LOAD SPINNER TEXTURES FROM TEXTURE LIST ARRAY IN HEADER...
    for( int i=0; i<TEXTURE_LOAD_LIST_LENGTH; i++ )
    {
        if( TEXTURE_LOAD_LIST[i].isUsed == true )
        {
            spinnerTextureArray[ TEXTURE_LOAD_LIST[i].textureSlot ] = loadJpegTexture( TEXTURE_LOAD_LIST[i].filename );
            //tempSpinnerArray[i].texture = TEXTURE_LOAD_LIST[i].textureSlot;
            //tempSpinnerArray[i].size = i/20.0;
            //drawSpinner( tempSpinnerArray[i] );

            tempSpinner.size = i/150.0;
            tempSpinner.active = true;
            tempSpinner.texture = TEXTURE_LOAD_LIST[i].textureSlot;
            tempSpinner.rotationPosition = i*15.0;
            drawSpinner( tempSpinner );
            
            // RENDER (SHOW LOADED TEXTURE) -- THIS FUNCTION BLOCKS UNTIL VSYNC IF VSYNC IS ENABLED/SUPPORTED ON THE PLATFORM (CURRENTLY DOES NOT WORK ON RPI)
            //if( i%2 == 0 )
                SDL_RenderPresent( SDLRenderer );
        }
    }
}




//////////////////////////////////////////////////////////////////////////////////////////
SDL_Texture* MCRenderer::loadJpegTexture( const std::string imageFilename )
{
    //---------------------
    // LOAD JPEG
    uJPEG jpeg;
    std::string imageFilenameWithPath = stdprintf( "%smedia/images/%s", SDL_GetBasePath(), imageFilename.c_str() );
    //printf( "FILE PATH: %s\n", imageFilenameWithPath.c_str() );
    SDL_Surface *bmp_surface = NULL;
    jpeg.decodeFile( imageFilenameWithPath.c_str() );
    if( jpeg.bad() ) 
    {
        printf("JPEG DECODING FAILED\n");
    }
    else
    {
        //printf("JPEG DECODED!!!!\n");
        //printf("W: %d   H: %d   COLOR:%d  SIZE:%d\n", jpeg.getWidth(), jpeg.getHeight(), jpeg.isColor(), jpeg.getImageSize() );  
        
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
        // IS THIS NECESSARY?
        SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );  
    }
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //printf( "SURFACE --> W:%d H:%d DEPTH:%d PITCH:%d\n", bmp_surface->w, bmp_surface->h, bmp_surface->format->BitsPerPixel, bmp_surface->pitch ); 
    //printf( "FORMAT:%d RMASK:%x GMASK:%x BMASK:%x AMASK:%x\n", 
    //       bmp_surface->format->format, bmp_surface->format->Rmask, bmp_surface->format->Gmask, bmp_surface->format->Bmask, bmp_surface->format->Amask );
    
    // FREE SURFACE MEMORY
    SDL_FreeSurface(bmp_surface); //*/
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    return( texture );
}









