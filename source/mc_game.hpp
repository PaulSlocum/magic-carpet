// mc_game.hpp
////////////////////////////////////////////////////////////////////////

#ifndef MC_GAME_HPP
#define MC_GAME_HPP

#include <map>
#include "mc_sprite.hpp"
#include "mc_touch.hpp"

class MCAppState;
class MCInput;
class MCAudio;
class MCApplication;
union SDL_Event;


#define NUMBER_OF_PRESETS 7


enum class AppMode { STOPPED, MENU, RUNNING };
enum class SoundMode { NORMAL, MUTE, INSTRUMENT };
enum class WheelPanMode { STOPPED, LEFT, RIGHT };



//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
struct RGBColor 
{
    float red = 1.0;
    float green = 1.0;
    float blue = 1.0;
};//*/



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



//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
class MCGame
{
public:
    MCGame( MCApplication* newApp );
    ~MCGame();
    void start();
    void stop();
    void processEvent( SDL_Event event );
    void updateFrame();
    
private:
    MCApplication* app;
    MCAppState state;
    // ~  ~  ~  ~  ~  ~  ~  
    int frameCount = 0;    
    long long startTimeMSec = 0;
    // ~  ~  ~  ~  ~  ~  ~  
    void loadPreset( const int presetNumber );
    // ~  ~  ~  ~  ~  ~  ~
    MCInput* inputHandler;
    MCAudio* audioController;
    // ~  ~  ~  ~  ~  ~  ~
    void initMenuMode();
    void updateMenuModeFrame();
    void initRunningMode();
    void updateRunningModeFrame();
    void updateSpinnerMode();
};


#endif
