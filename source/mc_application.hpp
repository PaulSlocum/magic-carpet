// mc_application.hpp
//////////////////////////////////////////////////////////////////////////////

#ifndef MC_APPLICATION_HPP
#define MC_APPLICATION_HPP

#include <map>
#include <vector>
#include "mc_sprite.hpp"
#include "mc_game.hpp"

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
//class MCInput;
class MCAudio;
class SDL_Renderer;
class SDL_Window;


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
class MCApplication
{
public:
    MCApplication();
    ~MCApplication();
    void start();
    void stop();
    // ~  ~  ~  ~  ~  ~  ~  ~
    RGBColor backgroundColor;
    std::map<int,MCSprite> spriteRenderList;
    
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
