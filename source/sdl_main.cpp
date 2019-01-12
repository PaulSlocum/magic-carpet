/*
 *  rectangles.c
 *  written by Holmes Futrell
 *  use however you want
 */

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"

//#include "jpeg_decoder.h"
#include "mc_util.hpp"


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480


static SDL_Texture *texture = NULL;

//=======================================================================
int randomInt(int min, int max)
{
    return min + rand() % (max - min + 1);
}


//=======================================================================
void render(SDL_Renderer *renderer)
{

    SDL_Rect rect;
    Uint8 r, g, b;

    /* Clear the screen */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    /*  Come up with a random rectangle */
    rect.w = randomInt(64, 128);
    rect.h = randomInt(64, 128);
    rect.x = randomInt(0, SCREEN_WIDTH);
    rect.y = randomInt(0, SCREEN_HEIGHT);

    /* Come up with a random color */
    r = randomInt(50, 255);
    g = randomInt(50, 255);
    b = randomInt(50, 255);
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    /*  Fill the rectangle in the color */
    //SDL_RenderFillRect(renderer, &rect);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int HAPPY_FACE_SIZE = 512;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    /* setup rects for drawing */
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = HAPPY_FACE_SIZE;
    srcRect.h = HAPPY_FACE_SIZE;
    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.w = HAPPY_FACE_SIZE;
    dstRect.h = HAPPY_FACE_SIZE;
    SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    /* update screen */
    SDL_RenderPresent(renderer);
}


extern "C" {
#define _NJ_INCLUDE_HEADER_ONLY
#include "nanojpeg13.c"
}

//=======================================================================
int main(int argc, char *argv[])
{

    SDL_Window *window;
    SDL_Renderer *renderer;
    int done;
    SDL_Event event;

    /* initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL\n");
        return 1;
    }

    //Jpeg::Decoder decoder();
    printf( "---------------------------------------\n" );
    //printf( "PREF PATH: %s\n", SDL_GetBasePath() );
    
    
    //SDL_RWops *rw = SDL_RWFromFile("resources/images/pattern0.jpg","r");
    
    
    //std::string imageFilename = stdprintf( "%s%s", SDL_GetBasePath(), "media/images/menuBG2c.jpg" );
    
    //---------------------
    // BMP LOADER
    // load the bmp
    /*std::string imageFilename = stdprintf( "%s%s", SDL_GetBasePath(), "media/images/pattern0.bmp" );
    SDL_Surface *bmp_surface = SDL_LoadBMP( imageFilename.c_str() );
    if( bmp_surface == NULL ) 
    {
        printf( "ERROR LOADING BMP\n" );
    }
    else
    {
        printf( "BMP LOADED!! \n" );
    }
    // set white to transparent on the happyface 
    //SDL_SetColorKey(bmp_surface, 1,
    //SDL_MapRGB(bmp_surface->format, 255, 255, 255)); //*/

    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    
    //---------------------
    // JPEG LOADER
    std::string imageFilename = stdprintf( "%s%s", SDL_GetBasePath(), "media/images/pattern0.jpg" );
    printf( "FILE PATH: %s\n", imageFilename.c_str() );
    SDL_Surface *bmp_surface = NULL;
    SDL_RWops *imageFile = SDL_RWFromFile( imageFilename.c_str(), "r" );
    if (imageFile != NULL) 
    {
        printf( "OPENED FILE\n" );

        size_t imageFileLength = SDL_RWsize( imageFile );
        //SDL_RWseek( imageFile, 0, SEEK_END );
        //size_t imageFileLength = SDL_RWtell( imageFile );
        Uint8 *imageFileBuffer = (unsigned char*)malloc( imageFileLength );
        //SDL_RWseek( imageFile, 0, SEEK_SET );
        size_t bytesRead = SDL_RWread( imageFile, imageFileBuffer, 1, imageFileLength ); 
        printf( "FILE SIZE: %ld   BYTES READ: %ld\n", imageFileLength, bytesRead );
        
        //Uint8 buf[256];
        //extern Uint8 buf[256];
        //SDL_RWread( imageFile, buf, sizeof (buf), 1 );
        SDL_RWclose( imageFile);
        
        //-----------------------------------------------------------
        
        //Jpeg::Decoder decoder( imageFileBuffer, imageFileLength );
        //if( decoder.GetResult() != Jpeg::Decoder::OK )
        njInit();
        if( njDecode( imageFileBuffer, (int)imageFileLength ) ) 
        {
            printf("JPEG DECODING FAILED\n");
            //return 1;
        }
        else
        {
            printf("JPEG DECODED!!!!\n");
            //printf("W: %d   H: %d   COLOR:%d  SIZE:%ld\n", decoder.GetWidth(), decoder.GetHeight(), decoder.IsColor(), decoder.GetImageSize() );  
            printf("W: %d   H: %d   COLOR:%d  SIZE:%d\n", njGetWidth(), njGetHeight(), njIsColor(), njGetImageSize() );  
            
            //return 1;
        }
        
        //njDone();
        
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //bmp_surface = SDL_CreateRGBSurfaceFrom( decoder.GetImage(), decoder.GetWidth(), decoder.GetHeight(), 24, decoder.GetWidth()*3, 0xFF0000, 0xFF00, 0xFF, 0 );
        //bmp_surface = SDL_CreateRGBSurfaceFrom( njGetImage(), njGetWidth(), njGetHeight(), 24, njGetWidth()*3, 0xFF0000, 0xFF00, 0xFF, 0 );
        bmp_surface = SDL_CreateRGBSurfaceFrom( njGetImage(), njGetWidth(), njGetHeight(), 24, njGetWidth()*3, 0xFF, 0xFF00, 0xFF0000, 0 );
                                                                //decoder.GetHeight(), 24, decoder.GetWidth()*3, 0, 0, 0, 0 );
                                                            
        //SDL_Surface* SDL_CreateRGBSurfaceFrom(void*  pixels,
        // int    width,
        // int    height,
        // int    depth,
        // int    pitch,
        // Uint32 Rmask,
        // Uint32 Gmask,
        // Uint32 Bmask,
        // Uint32 Amask) 
        
    }
    else 
    {
        printf( "DID NOT OPEN FILE\n" );
    } //*/
    
    ////////////////////////////////////////////////
    // JPEG LIBRARY SAMPLE CODE
    //fseek(f, 0, SEEK_END);
    //size = ftell(f);
    //buf = (unsigned char*)malloc(size);
    //fseek(f, 0, SEEK_SET);
    //size_t read = fread(buf, 1, size, f);
    //fclose(f);
    /////////////////////////////////////////

    
    /* seed random number generator */
    srand(time(NULL));

    /* create window and renderer */
    window =
        SDL_CreateWindow(NULL, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                         SDL_WINDOW_OPENGL);
    if (!window) {
        printf("Could not initialize Window\n");
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        printf("Could not create renderer\n");
        return 1;
    }

    
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // convert RGBA surface to texture 
    printf( "SURFACE --> W:%d H:%d DEPTH:%d PITCH:%d\n", bmp_surface->w, bmp_surface->h, bmp_surface->format->BitsPerPixel, bmp_surface->pitch ); 
    printf( "FORMAT:%d RMASK:%x GMASK:%x BMASK:%x AMASK:%x\n", 
           bmp_surface->format->format, bmp_surface->format->Rmask, bmp_surface->format->Gmask, bmp_surface->format->Bmask, bmp_surface->format->Amask ); 
    texture = SDL_CreateTextureFromSurface(renderer, bmp_surface);
    if (texture == 0) 
    {
        printf( "TEXTURE CREATION FAILED\n" );
    }
    else
    {
        printf( "TEXTURE CREATED!!!!\n" );
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);  
    }
    
    // free up allocated memory 
    SDL_FreeSurface(bmp_surface); //*/
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    
    /* Enter render loop, waiting for user to quit */
    done = 0;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = 1;
            }
        }
        render(renderer);
        SDL_Delay(1);
    }

    /* shutdown SDL */
    SDL_Quit();

    return 0;
}
