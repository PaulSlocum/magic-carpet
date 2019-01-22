// mc_application.hpp
//////////////////////////////////////////////////////////////////////////////

#ifndef MC_APPLICATION_HPP
#define MC_APPLICATION_HPP

#include <map>
#include "mc_spinner.hpp"

// ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^ 
#define FRAMES_PER_SECOND 60.0
// ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^ 


class MCRenderer;
class MCGame;
class MCInput;
class SDL_Renderer;
class SDL_Window;


enum class AppMode { STOPPED, LOADING, MENU, RUNNING };
enum class SoundMode { NORMAL, MUTE, INSTRUMENT };
enum class WheelPanMode { STOPPED, LEFT, RIGHT };



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
struct MCAppState 
{
    AppMode mode = AppMode::STOPPED;
    AppMode previousMode = AppMode::STOPPED;
    SoundMode soundMode = SoundMode::NORMAL;
    std::map<int,MCSpinner> spinnerArray;
    float menuWheelPosition = 0.5;
    float menuFadeIn = 1.0;
    MCSpinner muteButton;
    MCSpinner normalButton;
    MCSpinner instrumentButton;
    MCSpinner background;
    WheelPanMode wheelPan = WheelPanMode::STOPPED;
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
    int screenWidth = 0;
    int screenHeight = 0;
    // ~  ~  ~  ~  ~  ~  ~  ~
    MCAppState state;
    
private:
    void runLoop();
    // ~  ~  ~  ~  ~  ~  ~  ~  
    MCRenderer* renderer;
    MCGame* gameController;
    MCInput* inputHandler;
    SDL_Window *window;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    //MCAudio* audioController;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    bool vsyncEnabled = false;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    bool isQuitting = false;
};


#endif
