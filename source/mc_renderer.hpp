// mc_renderer.hpp
///////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <map>
#include "SDL.h"
#include "mc_spinner.hpp"

// ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ 
// NEW CONSTANTS
// ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ ' ^ 

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


class MCApplication;

class MCRenderer
{
public:
    MCRenderer( MCApplication* newApp );
    ~MCRenderer();
    void render();
    void loadTextures();
    
private:
    MCApplication* app;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    int frameCount = 0;
    long long startTimeMSec = 0;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    std::map<int, SDL_Texture*> spinnerTextureArray;
    std::map<int, SDL_Texture*> buttonTextureArray;
    SDL_Texture* backgroundTexture;
    std::map<int, bool> spinnerTextureArrayLoaded;
    // ~  ~  ~  ~  ~  ~  ~  ~  
    SDL_Texture* loadJpegTexture( const std::string imageFilename );
    void drawSpinner( const MCSpinner spinner );
    // ~  ~  ~  ~  ~  ~  ~  ~  
    // DEBUG - TRYING TO IMPLEMENT RENDER TARGET
    //SDL_Surface *softSurface;
    //SDL_Renderer *softRenderer;
};
