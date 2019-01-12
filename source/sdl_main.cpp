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

#include "jpeg_decoder.h"
#include "mc_util.hpp"


#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480


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
    SDL_RenderFillRect(renderer, &rect);

    /* update screen */
    SDL_RenderPresent(renderer);
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
    
    
    std::string imageFilename = stdprintf( "%s%s", SDL_GetBasePath(), "media/images/pattern0.jpg" );
    printf( "FILE PATH: %s\n", imageFilename.c_str() );
    SDL_RWops *imageFile = SDL_RWFromFile( imageFilename.c_str(),"r");
    if (imageFile != NULL) 
    {
        printf( "OPENED FILE\n" );

        SDL_RWseek( imageFile, 0, SEEK_END );
        size_t imageFileLength = SDL_RWtell( imageFile );
        Uint8 *imageFileBuffer = (unsigned char*)malloc( imageFileLength );
        SDL_RWseek( imageFile, 0, SEEK_SET );
        size_t bytesRead = SDL_RWread( imageFile, imageFileBuffer, 1, imageFileLength );
        printf( "FILE SIZE: %ld   BYTES READ: %ld\n", imageFileLength, bytesRead );
        
        //Uint8 buf[256];
        //extern Uint8 buf[256];
        //SDL_RWread( imageFile, buf, sizeof (buf), 1 );
        SDL_RWclose( imageFile);
        
        //-----------------------------------------------------------
        
        Jpeg::Decoder decoder( imageFileBuffer, imageFileLength );
        if( decoder.GetResult() != Jpeg::Decoder::OK )
        {
            printf("JPEG DECODING FAILED\n");
            //return 1;
        }
        else
        {
            printf("JPEG DECODED!!!!\n");
            //return 1;
        }
        
        /*f = fopen((argc > 2) ? argv[2] : (decoder.IsColor() ? "jpeg_out.ppm" : "jpeg_out.pgm"), "wb");
        if (!f) {
            printf("Error opening the output file.\n");
            return 1;
        }
        fprintf(f, "P%d\n%d %d\n255\n", decoder.IsColor() ? 6 : 5, decoder.GetWidth(), decoder.GetHeight());
        fwrite(decoder.GetImage(), 1, decoder.GetImageSize(), f);
        fclose(f);
        return 0; //*/

        
    }//*/
    else 
    {
        printf( "DID NOT OPEN FILE\n" );
    }
    
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
