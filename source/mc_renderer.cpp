// mc_renderer.cpp
////////////////////////////////////////////////////////////////////////

#include "SDL.h"

#include "mc_renderer.hpp"
#include "mc_application.hpp"

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
    // CLEAR THE SCREEN
    SDL_RenderClear( app->SDLRenderer );
    
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
    SDL_RenderCopyEx( app->SDLRenderer, app->texture, &srcRect, &dstRect, angle, NULL, SDL_FLIP_NONE );
    /*int SDL_RenderCopyEx(SDL_Renderer*          renderer,
     SDL_Texture*           texture,
     const SDL_Rect*        srcrect,
     const SDL_Rect*        dstrect,
     const double           angle,
     const SDL_Point*       center,
     const SDL_RendererFlip flip) //*/
    
    // RENDER!
    SDL_RenderPresent( app->SDLRenderer );
}
