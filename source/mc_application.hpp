// mc_application.hpp
//
// THE TOP LEVEL CLASS FOR THE MAGIC CARPET APPLICATION
//////////////////////////////////////////////////////////////////////////////

#ifndef MC_APPLICATION_HPP
#define MC_APPLICATION_HPP

#include <map>
#include "SDL.h"

class MCRenderer;

#define FRAMES_PER_SECOND 60.0


enum class AppMode { STOPPED, LOADING, MENU, RUNNING };


// SPINNER STRUCT -----------------------------
// Structure to track of spinning patterns
struct spinnerStruct {
    bool active;
    int texture;
    int xPosition;
    int yPosition;
    float rotationPosition;
    float rotationRate;
    float size;
};


// TOUCH STRUCT -----------------------------
// structure to track multiple touches
struct touchStruct {
    long frameCountOfLastRefresh;
    //UITouch* touch;
    float x;
    float y;
    float xStartingPoint;
    float yStartingPoint;
    float fade;
};



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
    SDL_Rect screenSize;
    bool vsyncEnabled = false;
    // ~  ~  ~  ~  ~  ~  ~  ~
    std::map<int, spinnerStruct> spinnerArray;
    std::map<int, touchStruct> touchArray;

private:
    void runLoop();
    // ~  ~  ~  ~  ~  ~  ~  ~  
    MCRenderer* renderer;
    SDL_Window *window;
    bool isQuitting = false;
    AppMode mode = AppMode::STOPPED;
};


#endif
