// mc_application.hpp
//////////////////////////////////////////////////////////////////////////////

#ifndef MC_APPLICATION_HPP
#define MC_APPLICATION_HPP

#include <map>
#include "SDL.h"
#include "mc_spinner.hpp"

class MCRenderer;
class MCGame;

#define FRAMES_PER_SECOND 60.0


enum class AppMode { STOPPED, LOADING, MENU, RUNNING };





// TOUCH STRUCT -----------------------------
// structure to track multiple touches
/*struct TouchStruct {
    long frameCountOfLastRefresh;
    //UITouch* touch;
    float x;
    float y;
    float xStartingPoint;
    float yStartingPoint;
    float fade;
}; //*/



//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
class MCApplication
{
public:
    void start();
    void stop();
    MCApplication();
    ~MCApplication();
    // ~  ~  ~  ~  ~  ~  ~  ~  
    SDL_Renderer *SDLRenderer = NULL;
    int screenWidth = 0;
    int screenHeight = 0;
    bool vsyncEnabled = false;
    // ~  ~  ~  ~  ~  ~  ~  ~
    std::map<int,MCSpinner> spinnerArray;
    //std::map<int,TouchStruct> touchArray;

private:
    void runLoop();
    // ~  ~  ~  ~  ~  ~  ~  ~  
    MCRenderer* renderer;
    MCGame* game;
    SDL_Window *window;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    bool isQuitting = false;
    AppMode mode = AppMode::STOPPED;
};


#endif
