// mc_application.hpp
//////////////////////////////////////////////////////////////////////////////

#ifndef MC_APPLICATION_HPP
#define MC_APPLICATION_HPP

#include <map>
#include "mc_spinner.hpp"

// ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ 
// NEW CONSTANTS
// ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ 

// ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^ 
#define FRAMES_PER_SECOND 60.0
// ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^  ~ ^ 

#define MAX_MAIN_SPINNERS 8 
#define MAX_ACTIVE_SPINNERS 7

// ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ 
// ORIGINAL CONSTANTS
// ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ 

// force OpenGL 1.1
//const bool ForceES1 = true;

// * CONSTANTS *
/*#define kMaxMainSpinners 8
 #define kMaxActiveSpinners 7
 #define kMaxTouchSpinners 5
 #define kMaxSpinnerTextures 256
 
 #define kRandomTextureButtonHeightTop 0.00
 #define kRandomTextureButtonHeightBottom 0.65
 #define kRandomTextureButtonHorizontalLeft -1.0
 #define kRandomTextureButtonHorizontalRight 0
 
 
 #define kNumberOfRugs 113
 
 #define kDefaultSpinnerModeAdvanceRate 6000
 
 #define kMenuButtonHoldTime 40
 #define kMaxTouches 20
 
 #define kEchoOffset 40000
 
 // Audio System
 #define kMaxLoops 32 // number of loop channels, each channel can play one loop
 
 // Display
 #define kScreenWidth 480.0
 #define kScreenHeight 320.0
 
 #ifndef kLITE_VERSION
 #define kNumberOfPresets 7
 #else
 #define kNumberOfPresets 3
 #endif
 
 #define kAppModeMenu 0
 #define kAppModeRunning 1
 
 #define kNoPendingSoundModeTouch 0
 #define kAppSoundModeiPod 1
 #define kAppSoundModeInstrumentA 2
 #define kAppSoundModeBinaural 3
 
 #define kEnableSpinnerButtons
 
 // This is now permanently disabled because screen mirroring is better
 #define kDisableExternalScreen_Debug //*/

// ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ 


class MCRenderer;
class MCGame;
class MCInput;
class MCAudio;
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
    // ~  ~  ~  ~  ~  ~  ~  ~    
    std::map<int,MCSpinner> spinnerArray;
    // ~  ~  ~  ~  ~  ~  ~  ~    
    float menuWheelPosition = 0.5;
    float menuFadeIn = 1.0;
    float runningFadeIn = 1.0;
    // ~  ~  ~  ~  ~  ~  ~  ~    
    MCSpinner muteButton;
    MCSpinner normalButton;
    MCSpinner instrumentButton;
    MCSpinner background;
    WheelPanMode wheelPan = WheelPanMode::STOPPED;
    // ~  ~  ~  ~  ~  ~  ~  ~    
    int32_t presetIndex = 0;
    int32_t visualPreset = 0;
    // ~  ~  ~  ~  ~  ~  ~  ~    
    long spinnerModeAdvanceRate = 0;
    float creep = 0.0;
    bool dualSpinners = 0;
    int spinPolarity = 1;
    float spinnerSizeOffset = 0.0;
    float spinnerScaleX = 0.0;
    float spinnerScaleY = 0.0;
    // ~  ~  ~  ~  ~  ~  ~  ~    
    long audioLoopPosition = 0;
    float pitchBend = 0.0;
};



//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
class MCApplication
{
public:
    MCApplication();
    ~MCApplication();
    void start();
    void stop();
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
    MCAudio* audioController;
    SDL_Window *window;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    //MCAudio* audioController;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    bool vsyncEnabled = false;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    bool isQuitting = false;
};


#endif
