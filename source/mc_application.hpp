// mc_application.hpp
//
// THE TOP LEVEL CLASS FOR THE MAGIC CARPET APPLICATION
//////////////////////////////////////////////////////////////////////////////

#ifndef MC_APPLICATION_HPP
#define MC_APPLICATION_HPP

#include "SDL.h"

class MCRenderer;


class MCApplication
{
public:
    void start();
    void stop();
    MCApplication();
    ~MCApplication();
    // ~  ~  ~  ~  ~  ~  ~  ~  
    SDL_Renderer *SDLRenderer = NULL;
    SDL_Texture *texture = NULL;

private:
    void runLoop();
    // ~  ~  ~  ~  ~  ~  ~  ~  
    MCRenderer* renderer;
    SDL_Window *window;
    int isQuitting;
};


#endif
