// mc_application.hpp
//
// THE TOP LEVEL CLASS FOR THE MAGIC CARPET APPLICATION
//////////////////////////////////////////////////////////////////////////////

#ifndef MC_APPLICATION_HPP
#define MC_APPLICATION_HPP

#include "SDL.h"

class MCRenderer;

#define FRAMES_PER_SECOND 60.0


enum class AppMode { STOPPED, LOADING, MENU, RUNNING };


class MCApplication
{
public:
    void start();
    void stop();
    MCApplication();
    ~MCApplication();
    // ~  ~  ~  ~  ~  ~  ~  ~  
    SDL_Renderer *SDLRenderer = NULL;
    SDL_Rect screenSize;
    bool vsyncEnabled = false;

private:
    void runLoop();
    // ~  ~  ~  ~  ~  ~  ~  ~  
    MCRenderer* renderer;
    SDL_Window *window;
    int isQuitting;
    AppMode mode = AppMode::STOPPED;
};


#endif
