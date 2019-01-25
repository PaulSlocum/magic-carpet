// mc_game.hpp
////////////////////////////////////////////////////////////////////////

#ifndef MC_GAME_HPP
#define MC_GAME_HPP

#include <map>
#include "mc_sprite.hpp"
#include "mc_touch.hpp"

class MCInput;
class MCAudio;
class MCApplication;
class MCMenuScreen;
class MCGameScreen;
union SDL_Event;


// TODO: THESE SHOULD MAYBE BE MOVED?
#define MAX_MAIN_SPINNERS 8 
#define MAX_ACTIVE_SPINNERS 7

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
    // ~  ~  ~  ~  ~  ~  ~  ~    
    void loadPreset( const int presetNumber );
    // ~  ~  ~  ~  ~  ~  ~
    AppMode mode = AppMode::STOPPED;
    AppMode previousMode = AppMode::STOPPED;
    SoundMode soundMode = SoundMode::NORMAL;
    // ~  ~  ~  ~  ~  ~  ~  ~    
    std::map<int,MCSprite> spinnerArray;
    std::map<int,MCTouch> touchArray;
    // ~  ~  ~  ~  ~  ~  ~  ~    
    int frameCount = 0; // <- RESET WHEN PRESET IS LOADED
    int totalFrameCount = 0;
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
    
    
private:
    MCApplication* app;
    // ~  ~  ~  ~  ~  ~  ~  
    long long startTimeMSec = 0;
    // ~  ~  ~  ~  ~  ~  ~  
    MCInput* inputHandler;
    MCAudio* audioController;
    MCMenuScreen* menuScreen;
    MCGameScreen* gameScreen;
    // ~  ~  ~  ~  ~  ~  ~
    //void initRunningMode();
    //void updateRunningModeFrame();
    //void updateSpinnerMode();
};


#endif
