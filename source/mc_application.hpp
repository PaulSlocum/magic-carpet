// mc_application.hpp
//////////////////////////////////////////////////////////////////////////////

#ifndef MC_APPLICATION_HPP
#define MC_APPLICATION_HPP

#include <map>
#include "mc_sprite.hpp"
#include "mc_touch.hpp"

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


enum class AppMode { STOPPED, MENU, RUNNING };
enum class SoundMode { NORMAL, MUTE, INSTRUMENT };
enum class WheelPanMode { STOPPED, LEFT, RIGHT };



//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
struct RGBColor 
{
    float red = 1.0;
    float green = 1.0;
    float blue = 1.0;
};




//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
struct MCAppState 
{
    AppMode mode = AppMode::STOPPED;
    AppMode previousMode = AppMode::STOPPED;
    SoundMode soundMode = SoundMode::NORMAL;
    // ~  ~  ~  ~  ~  ~  ~  ~    
    std::map<int,MCSprite> spinnerArray;
    std::map<int,MCTouch> touchArray;
    // ~  ~  ~  ~  ~  ~  ~  ~    
    float menuWheelPosition = 0.5;
    float menuFadeIn = 1.0;
    float runningFadeIn = 1.0;
    // ~  ~  ~  ~  ~  ~  ~  ~    
    MCSprite muteButton;
    MCSprite normalButton;
    MCSprite instrumentButton;
    MCSprite background;
    // ~  ~  ~  ~  ~  ~  ~  ~    
    WheelPanMode wheelPan = WheelPanMode::STOPPED;
    RGBColor backgroundColor;
    // ~  ~  ~  ~  ~  ~  ~  ~    
    int presetIndex = 0; // <-- THIS SHOULD PROBABLY BE REMOVED, ONLY NEED TO KEEP "selectedPreset"
    int selectedPreset = 0;
    // ~  ~  ~  ~  ~  ~  ~  ~    
    long spinnerModeAdvanceRate = 0;
    float creep = 0.0;
    int spinPolarity = 1;
    float spinnerSizeOffset = 0.0;
    float spinnerScaleX = 0.0;
    float spinnerScaleY = 0.0;
    bool manualTextureSelection = false;
    // ~  ~  ~  ~  ~  ~  ~  ~    
    long audioLoopPosition = 0;
    float pitchBend = 0.7;
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
    MCAppState state;
    
private:
    void runLoop();
    // ~  ~  ~  ~  ~  ~  ~  ~  
    MCRenderer* renderer;
    MCGame* gameController;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    bool vsyncEnabled = false;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    bool isQuitting = false;
    bool appStarted = false;
};


#endif
